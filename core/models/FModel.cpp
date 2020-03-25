#include "FModel.h"

#include "FCrossSection.h"
#include "ForgeApplication.h"

/*! \brief Constructor for model.
 */
FModel::FModel(FGeometry* t_section, QtTransform* t_transform, FMaterial* t_material)
	: m_geometry(t_section)
	, m_transform(t_transform)
	, m_material(t_material)
	, m_renderer(nullptr)
	, m_selectable(true)
	, m_picker(new QtObjectPicker(this))
{
	if (m_geometry != nullptr) {
		m_renderer = m_geometry->getRenderer(
			QtRenderType::Points);

		this->addComponent(m_renderer);
	}

	if(m_transform != nullptr) 
		this->addComponent(m_transform);
	if(m_material != nullptr)
		this->addComponent(m_material);

	this->addComponent(m_picker);

	(void)this->connect(m_picker, &QtObjectPicker::pressed,
		this, &FModel::onClick);
}

/*! \brief Secondary constructor for the FModel.
 */
FModel::FModel(FGeometry* t_section, QColor t_color)
	: FModel(t_section, new QtTransform(), new FMaterial(t_color))
{}

/*! \brief Secondary constructor for the FModel.
 */
FModel::FModel(FGeometry* t_section)
	: FModel(t_section, new QtTransform(), new FMaterial(RED))
{}

/*! \brief Default constructor for the FModel.
 */
FModel::FModel()
	: FModel(nullptr, new QtTransform(), nullptr)
{
}

void FModel::onClick(Qt3DRender::QPickEvent* t_event) {
	ForgeApplication::instance()->setSelected(this);
}

/*! \brief Get the QTransform for this entity.
 */
QtTransform* FModel::transform() {
	return m_transform;
}

/*! \brief Get the FGeometry of the model.
 */
FGeometry* FModel::geometry() {
	return m_geometry;
}

/*! \brief Get the FGeometry of the model.
 */
FMaterial* FModel::material() {
	return m_material;
}

/*! \brief Get the geometry renderer.
 */
QtRenderer* FModel::renderer() {
	return m_renderer;
}

/*! \brief Set this model as selectable.
 */
void FModel::setSelectable(bool t_selectable)
{
	m_selectable = t_selectable;
}

/*! \brief Get the "selectable" flag. True if the user
 *		   can interact with this model.
 */
bool FModel::selectable()
{
	return m_selectable;
}

/*! \brief Stop highlighting the model.
 */
void FModel::unHighlight()
{
	if (m_material != nullptr) {
		m_material->resetColor();
	}
}

/*! \brief Highlight the model.
 */
void FModel::highlight() {
	if (m_material != nullptr) {
		auto color = m_material->color();
		m_material->setColor(color.lighter());
	}
}

/*! \brief If true, this entity/model is not visible
 *		   in the 3D view.
 */
bool FModel::hidden() {
	return this->isEnabled();
}

/*! \brief Hide the model. (make NOT visible 
 *		   in the 3D view)
 */
void FModel::hide() {
	this->setEnabled(false);
}

/*! \brief Show the model. (make VISIBLE in the 
 *		   3D view)
 */
void FModel::show() {
	this->setEnabled(true);
}

