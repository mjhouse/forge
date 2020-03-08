#pragma once

#include <QtCore/QByteArray>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QEffect>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QGraphicsApiFilter>
#include <QtCore/QDir>

#include "Defines.h"
#include "Resources.h"

class FModelEffect : public QtEffect {
private:


public:
	FModelEffect(QtMaterial* parent) 
		: QtEffect(parent)
	{
		auto shader = new Qt3DRender::QShaderProgram(parent);
		
		shader->setVertexShaderCode(resources::shader("vertex_shader"));
		shader->setFragmentShaderCode(resources::shader("fragment_shader"));

		auto render = new Qt3DRender::QRenderPass(parent);
		render->setShaderProgram(shader);

		auto filterKey = new Qt3DRender::QFilterKey;
		filterKey->setName(QStringLiteral("renderingStyle"));
		filterKey->setValue("forward");

		auto technique = new Qt3DRender::QTechnique();
		technique->addRenderPass(render);
		technique->addFilterKey(filterKey);
		technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::Api::OpenGL);
		technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::OpenGLProfile::CoreProfile);
		technique->graphicsApiFilter()->setMajorVersion(3);
		technique->graphicsApiFilter()->setMinorVersion(3);

		this->addTechnique(technique);
	}
};

class FMaterial : public QtMaterial {
public:
	virtual void setColor(float r, float g, float b) = 0;

	virtual void resetColor() = 0;
};

class FDefaultMaterial : public FMaterial {
private:
	QColor base_color;
	QtParameter* surfaceColor;

public:
	FDefaultMaterial(QColor t_color)
		: surfaceColor(new QtParameter())
	{
		this->setEffect(new FModelEffect(this));

		surfaceColor->setName(QStringLiteral("surfaceColor"));
		this->addParameter(surfaceColor);

		this->setColor(t_color);
		base_color = t_color;
	}

	void setColor(QColor t_color) {
		surfaceColor->setValue(t_color);
	}

	void setColor(float r, float g, float b) {
		setColor(QColor::fromRgbF(r, g, b));
	}

	void resetColor()
	{
		setColor(base_color);
	}
};