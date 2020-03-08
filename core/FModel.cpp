#include "FModel.h"
#include "ForgeApplication.h"

FModel::FModel(FCrossSection* t_section, QtTransform* t_transform, FMaterial* t_material)
	: section(t_section)
	, geometry(t_section->toGeometry())
	, transform(t_transform)
	, material(t_material)
{
	renderer = geometry->getRenderer(
		QtRenderType::Triangles);

	this->addComponent(renderer);
	this->addComponent(material);
	this->addComponent(transform);
}

FModel::FModel(FCrossSection* t_section, QColor t_color)
	: FModel(t_section, new QtTransform(), new FDefaultMaterial(t_color))
{}

FModel::FModel(FCrossSection* t_section)
	: FModel(t_section, new QtTransform(), new FDefaultMaterial(RED))
{}

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

QtTransform* FModel::getTransform() {
	return transform;
}

bool FModel::isVisible() {
	return this->isEnabled();
}

void FModel::unSelect()
{
	material->resetColor();
}

void FModel::select()
{
	material->setColor(100, 100, 100);
}

void FModel::hide() {
	this->setEnabled(false);
}

void FModel::show() {
	this->setEnabled(true);
}

void FModel::setLength(float t_length) {
	section->setLength(t_length);
	section->updateGeometry(geometry);
}
