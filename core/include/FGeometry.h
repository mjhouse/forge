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

#include "Defines.h"

class Bounds {
public:

	QVector3D max = QVector3D(0.0, 0.0, 0.0);
	QVector3D min = QVector3D(0.0, 0.0, 0.0);

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

class FGeometry : public QtGeometry {
public:
	QtBuffer* buffer;

	QtBuffer* normals;

	QtBuffer* indices;

	QtAttribute* posAttribute;

	QtAttribute* normAttribute;

	QtAttribute* idxAttribute;

	std::vector<uint> tessellate(std::vector<QVector3D> points);

public:
	FGeometry();

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

	bool isPlanar() {
		auto v = getVertices();
		if (v.size() <= 3) return true;

		auto normal = QVector3D::crossProduct(
			v[1] - v[0], v[2] - v[0]).normalized();

		for (auto it = v.begin() + 3; it != v.end(); ++it) {
			if (QVector3D::dotProduct(*it - v[0], normal) != 0) 
				return false;
		}

		return true;
	}

};
