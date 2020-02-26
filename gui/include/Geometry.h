#pragma once

#include <Qt3DRender/QGeometryFactory>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QMaterial>
#include <Qt3DCore/QComponent>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/poisson_surface_reconstruction.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/compute_average_spacing.h>

#include <fstream>

typedef Qt3DRender::QGeometryRenderer::PrimitiveType QtRenderType;

typedef Qt3DCore::QNode               QtNode;
typedef Qt3DCore::QEntity             QtEntity;
typedef Qt3DCore::QComponent          QtComponent;
typedef Qt3DCore::QTransform          QtTransform;

typedef Qt3DRender::QBuffer           QtBuffer;
typedef Qt3DRender::QAttribute        QtAttribute;
typedef Qt3DRender::QGeometry         QtGeometry;
typedef Qt3DRender::QGeometryRenderer QtRenderer;

#define CGAL_USE_SCIP 1

#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/array.h>
#include <CGAL/disable_warnings.h>

#include <CGAL/SCIP_mixed_integer_program_traits.h>
typedef CGAL::SCIP_mixed_integer_program_traits<double>         MIP_Solver;

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_3  Point_3;
typedef std::array<std::size_t, 3> Facet;

class Bounds {
public:

	QVector3D max = QVector3D(0.0, 0.0, 0.0);
	QVector3D min = QVector3D(0.0, 0.0, 0.0);

	std::vector<QVector3D> max_normals = {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}
	};

	std::vector<QVector3D> min_normals = {
		{-1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, -1.0}
	};

	Bounds(std::vector<QVector3D> points) {
		findBounds(points);
	}

	void findBounds(std::vector<QVector3D> points) {
		bool f = true;
		for (const auto& point : points) {
			float x = point.x();
			float y = point.y();
			float z = point.z();
			max[0] = x > max[0] || f ? x : max[0];
			min[0] = x < min[0] || f ? x : min[0];
			max[1] = y > max[1] || f ? y : max[1];
			min[1] = y < min[1] || f ? y : min[1];
			max[2] = z > max[2] || f ? z : max[2];
			min[2] = z < min[2] || f ? z : min[2];
			if (f) f = false;
		}
	}

};

class Geometry : public QtGeometry {
public:
	QtBuffer* buffer;

	QtBuffer* normals;

	QtBuffer* indices;

	QtAttribute* posAttribute;

	QtAttribute* normAttribute;

	QtAttribute* idxAttribute;

	std::vector<uint> tessellate(std::vector<QVector3D> points);

public:
	Geometry(QNode* parent);

	void polygon();

	QtRenderer* getRenderer(QtRenderType type);

	void setVertices(std::vector<QVector3D> t_vertices);

	void setNormals(std::vector<QVector3D> t_normals);

	void setIndices(std::vector<uint> t_indices);

	std::vector<QVector3D> getVertices();

	std::vector<QVector3D> getNormals();

	std::vector<uint> getIndices();

	void setVertexData(std::vector<QVector3D> vertices);

	void setNormalData(std::vector<QVector3D> normals);

	void setIndexData(std::vector<uint> indices);

	void setVertexBuffer(QtBuffer* buffer, uint count);
	
	void setNormalBuffer(QtBuffer* buffer, uint count);
	
	void setIndexBuffer(QtBuffer* buffer, uint count);

};

class FModel : public QtEntity {
public:

	Geometry* geometry;

	QtTransform* transform;

	QtRenderer* renderer;

public:

	FModel(QtEntity* parent, QtComponent* material)
		: QtEntity(parent)
		, geometry(new Geometry(this))
		, transform(new QtTransform())
	{
		renderer = geometry->getRenderer(QtRenderType::Points);
		
		this->addComponent(renderer);
		this->addComponent(material);
		this->addComponent(transform);
	}

	QVector3D getCentroid() {
		auto points = geometry->getVertices();
		float x = 0; 
		float y = 0;
		float z = 0;
		int c = 0;

		auto r = transform->matrix();
		auto t = transform->translation();

		for (auto point : points) {
			auto p = QVector4D(point, 1) * r + t;
			x += p.x();
			y += p.y();
			z += p.z();
			c++;
		}

		if (c > 0)
			return QVector3D(
				x / c,
				y / c,
				z / c);
		else
			return QVector3D(0, 0, 0);
	}


};

class FPolygon : public FModel {
private:
public:
	FPolygon(QtEntity* parent, QtComponent* material)
		: FModel(parent,material)
	{
		renderer->setPrimitiveType(QtRenderType::Triangles);
	}

	void setPoints(std::vector<QVector3D> points) {
		QVector3D n = QVector3D::normal(points[0],points[1],points[2]);

		std::vector<QVector3D> normals(points.size());
		for (int i = 0; i < points.size(); ++i)
			normals[i] = n;

		std::vector<uint> indices = geometry->tessellate(points);

		geometry->setVertices(points);
		geometry->setNormals(normals);
		geometry->setIndices(indices);
	}
};

class FLine : public FModel {
private:
public:
	FLine(QtEntity* parent, QtComponent* material)
		: FModel(parent, material)
	{
		renderer->setPrimitiveType(QtRenderType::LineStrip);
	}

	void setPoints(std::vector<QVector3D> points) {
		geometry->setVertices(points);
	}

};

struct Perimeter {
	double bound;
	Perimeter(double bound)
		: bound(bound)
	{}
	template <typename AdvancingFront, typename Cell_handle>
	double operator() (const AdvancingFront& adv, Cell_handle& c,
		const int& index) const
	{
		// bound == 0 is better than bound < infinity
		// as it avoids the distance computations
		if (bound == 0) {
			return adv.smallest_radius_delaunay_sphere(c, index);
		}
		// If perimeter > bound, return infinity so that facet is not used
		double d = 0;
		d = sqrt(squared_distance(c->vertex((index + 1) % 4)->point(),
			c->vertex((index + 2) % 4)->point()));
		if (d > bound) return adv.infinity();
		d += sqrt(squared_distance(c->vertex((index + 2) % 4)->point(),
			c->vertex((index + 3) % 4)->point()));
		if (d > bound) return adv.infinity();
		d += sqrt(squared_distance(c->vertex((index + 1) % 4)->point(),
			c->vertex((index + 3) % 4)->point()));
		if (d > bound) return adv.infinity();

		// Otherwise, return usual priority value: smallest radius of
		// delaunay sphere
		return adv.smallest_radius_delaunay_sphere(c, index);
	}
};

class FCube : public FModel {
private:
public:
	FCube(QtEntity* parent, QtComponent* material)
		: FModel(parent, material)
	{
		renderer->setPrimitiveType(QtRenderType::Triangles);
	}

	void setPoints(std::vector<QVector3D> points) {
		if (points.size() != 2) return;

		auto m1 = points[0];
		auto m2 = points[1];

		QVector3D s2(m1.x(), m2.y(), m1.z());
		QVector3D s3(m2.x(), m2.y(), m1.z());
		QVector3D s4(m2.x(), m1.y(), m1.z());
		QVector3D s5(m1.x(), m2.y(), m2.z());
		QVector3D s6(m1.x(), m1.y(), m2.z());
		QVector3D s7(m2.x(), m1.y(), m2.z());
		
		QVector3D n1 = QVector3D::normal(m1, s2, s5);
		QVector3D n2 = QVector3D::normal(s5, s6, m1);
		QVector3D n3 = QVector3D::normal(m1, s4, s3);
		QVector3D n4 = QVector3D::normal(s3, s2, m1);
		QVector3D n5 = QVector3D::normal(m1, s6, s7);
		QVector3D n6 = QVector3D::normal(s7, s4, m1);
		QVector3D n7 = QVector3D::normal(m2, s5, s2);
		QVector3D n8 = QVector3D::normal(s2, s3, m2);
		QVector3D n9 = QVector3D::normal(m2, s3, s4);
		QVector3D n10 = QVector3D::normal(s4, s7, m2);
		QVector3D n11 = QVector3D::normal(m2, s7, s6);
		QVector3D n12 = QVector3D::normal(s6, s5, m2);

		QVector3D n01 = QVector3D(n1 + n2 + n3 + n4 + n5 + n6).normalized();
		QVector3D n02 = QVector3D(n7 + n8 + n9 + n10 + n11 + n12).normalized();
		QVector3D n03 = QVector3D(n1 + n4 + n7 + n8).normalized();
		QVector3D n04 = QVector3D(n3 + n4 + n8 + n9).normalized();
		QVector3D n05 = QVector3D(n3 + n6 + n9 + n10).normalized();
		QVector3D n06 = QVector3D(n1 + n2 + n7 + n12).normalized();
		QVector3D n07 = QVector3D(n2 + n5 + n11 + n12).normalized();
		QVector3D n08 = QVector3D(n5 + n6 + n10 + n11).normalized();

		geometry->setVertices({
		//   0    1   2   3   4   5   6   7
			m1,  m2, s2, s3, s4, s5, s6, s7
		});
		geometry->setNormals({
			n01, n02, n03, n04, n05, n06, n07, n08
		});
		geometry->setIndices({
			0, 2, 5, 5, 6, 0,
			0, 4, 3, 3, 2, 0,
			0, 6, 7, 7, 4, 0,
			1, 5, 2, 2, 3, 1,
			1, 3, 4, 4, 7, 1,
			1, 7, 6, 6, 5, 1
		});
	}

	void test() {
		// duplicate surface geometry
		auto c = getCentroid();
		auto ov = geometry->getVertices();
		auto on = geometry->getNormals();
		auto oi = geometry->getIndices();

		std::vector<Point_3> points;
		std::vector<Facet> facets;

		for (int i = 0; i < ov.size(); ++i) {
			auto v = ov[i];
			
			points.push_back(Point_3(v.x(), v.y(), v.z()));
		}

		Perimeter perimeter(0);
		CGAL::advancing_front_surface_reconstruction(
			points.begin(),
			points.end(),
			std::back_inserter(facets),
			perimeter);

		oi.clear();
		oi.resize(facets.size()*3);
		int i = 0;
		for (auto facet : facets) {
			oi[i++] = facet.at(0);
			oi[i++] = facet.at(1);
			oi[i++] = facet.at(2);
		}

		geometry->setIndices(oi);
	}

};