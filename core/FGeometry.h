#ifndef __FGEOMETRY_H__
#define __FGEOMETRY_H__

#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>

#include "Defines.h"

class FGeometry : public QtGeometry {
public:
	QtBuffer* m_vertices;			/*!< The vertex buffer */

	QtBuffer* m_normals;			/*!< The normal buffer */

	QtBuffer* m_indices;			/*!< The index buffer */

	QtAttribute* m_vertexAttribute; /*!< An attribute that handles the vertex buffer */

	QtAttribute* m_normalAttribute; /*!< An attribute that handles the normal buffer */

	QtAttribute* m_indexAttribute;  /*!< An attribute that handles the index buffer */
	
	inline QByteArray toData(std::vector<QVector3D>& t_points) {
		QByteArray data;

		// size the output bytearray and get direct access
		data.resize((uint)t_points.size() * 3 * sizeof(float));
		auto raw = reinterpret_cast<float*>(data.data());

		// transfer data from vertices to the raw array
		int idx = 0;
		for (const QVector3D& vertex : t_points) {
			raw[idx++] = vertex.x();
			raw[idx++] = vertex.y();
			raw[idx++] = vertex.z();
		}

		return data;
	}

	void setVertexData(std::vector<QVector3D>& t_vertices);

	void setNormalData(std::vector<QVector3D>& t_normals);

	void setIndexData(std::vector<uint>& t_indices);

	void createVertexAttribute(QtBuffer* t_buffer, uint t_count);

	void createNormalAttribute(QtBuffer* t_buffer, uint t_count);

	void createIndexAttribute(QtBuffer* t_buffer, uint t_count);

public:
	FGeometry();
		
	void setVertices(std::vector<QVector3D> t_vertices);

	void setNormals(std::vector<QVector3D> t_normals);

	void setIndices(std::vector<uint> t_indices);

	std::vector<QVector3D> getVertices();

	std::vector<QVector3D> getNormals();

	std::vector<uint> getIndices();

	QtRenderer* getRenderer(QtRenderType t_type);

	bool isPlanar();

};

#endif // __FGEOMETRY_H__