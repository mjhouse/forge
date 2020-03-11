#include "FMaterial.h"
#include "Resources.h"
#include "Defines.h"

/*! \brief Constructor for material that inits shader program and
 *		   sets the initial color.
 */
FMaterial::FMaterial(QColor t_color)
	: m_original(t_color)
	, m_current(t_color)
	, m_surfaceColor(new QtParameter())
{
	this->initialize();
	this->setColor(t_color);
}

/*! \brief Initialize the shader program and program params.
 */
void FMaterial::initialize() {
	// create the param to pass color to the shaders
	m_surfaceColor->setName(QStringLiteral("surfaceColor"));
	this->addParameter(m_surfaceColor);

	auto effect = new QtEffect(this);
	auto shader = new QtShaderProgram(this);

	// resources::shader loads a shader from the
	// "resources/shaders" directory.
	shader->setVertexShaderCode(
		resources::shader("vertex_shader"));
	shader->setFragmentShaderCode(
		resources::shader("fragment_shader"));

	auto render = new QtRenderPass(this);
	render->setShaderProgram(shader);

	auto filterKey = new QtFilterKey();
	filterKey->setName(QStringLiteral("renderingStyle"));
	filterKey->setValue("forward");

	auto technique = new QtTechnique();
	technique->addRenderPass(render);
	technique->addFilterKey(filterKey);

	technique->graphicsApiFilter()
		->setApi(QtRenderApi::OpenGL);
	technique->graphicsApiFilter()
		->setProfile(QtOpenGLProfile::CoreProfile);
	technique->graphicsApiFilter()
		->setMajorVersion(3);
	technique->graphicsApiFilter()
		->setMinorVersion(3);

	effect->addTechnique(technique);
	this->setEffect(effect);
}

/*! \brief Set the color with a QColor object.
 */
void FMaterial::setColor(QColor t_color) {
	m_surfaceColor->setValue(t_color);
	m_current = t_color;
}

/*! \brief Set the color from r, g and b values.
 */
void FMaterial::setColor(float r, float g, float b) {
	setColor(QColor::fromRgbF(r, g, b));
}

/*! \brief Get the current color
 */
QColor FMaterial::color() {
	return m_current;
}

/*! \brief Reset the original color
 */
void FMaterial::resetColor()
{
	setColor(m_original);
}