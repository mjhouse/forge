#include "FModel.h"

QVector3D FModel::getCentroid(std::vector<QVector3D> points) {
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

	return QVector3D(
		x / c, y / c, z / c);
}

QVector3D FModel::getCentroid() {
	auto points = geometry->getVertices();
	return getCentroid(points);
}