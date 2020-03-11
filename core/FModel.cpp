#include "FModel.h"
#include "ForgeApplication.h"

FModel::FModel(FGeometry* t_section, QtTransform* t_transform, FMaterial* t_material)
	: geometry(t_section)
	, transform(t_transform)
	, material(t_material)
	, selectable(true)
{
	if (geometry) {
		renderer = geometry->getRenderer(
			QtRenderType::LineLoop);

		this->addComponent(renderer);
		this->addComponent(material);
	}
	this->addComponent(transform);
}

FModel::FModel(FGeometry* t_section, QColor t_color)
	: FModel(t_section, new QtTransform(), new FMaterial(t_color))
{}

FModel::FModel(FGeometry* t_section)
	: FModel(t_section, new QtTransform(), new FMaterial(RED))
{}

FModel::FModel()
	: geometry(nullptr)
	, transform(new QtTransform())
	, material(nullptr)
	, selectable(false) {
	this->addComponent(transform);
}

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
	if (geometry) {
		auto points = geometry->getVertices();
		return getCentroid(points);
	}
	return QVector3D(0,0,0);
}

QtTransform* FModel::getTransform() {
	return transform;
}

bool FModel::isVisible() {
	return this->isEnabled();
}

FGeometry* FModel::getGeometry() {
	return geometry;
}

QtRenderer* FModel::getRenderer() {
	return renderer;
}

void FModel::setSelectable(bool t_selectable)
{
	selectable = t_selectable;
}

bool FModel::getSelectable()
{
	return selectable;
}

void FModel::unSelect()
{
	if(material != nullptr) material->resetColor();
}

void FModel::select()
{
	if (material != nullptr) {
		auto color = material->color();
		material->setColor(color.lighter());
	}
}

void FModel::hide() {
	this->setEnabled(false);
}

void FModel::show() {
	this->setEnabled(true);
}

