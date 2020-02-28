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

class FModelEffect : public QtEffect {
private:

	QDir resources;

	QByteArray load(const char* name) {
		QFile file(resources.filePath(name));

		if (!file.exists())
			throw -1;

		file.open(QFile::ReadOnly);
		auto data = file.readAll();
		file.close();

		return data;
	}

public:
	FModelEffect(QtMaterial* parent, QDir t_resources) 
		: QtEffect(parent)
		, resources(t_resources) 
	{
		auto shader = new Qt3DRender::QShaderProgram(parent);
		
		shader->setVertexShaderCode(load("vertex_shader.glsl"));
		shader->setFragmentShaderCode(load("fragment_shader.glsl"));

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
};

class FDefaultMaterial : public FMaterial {
private:

	QtParameter* surfaceColor;

public:
	FDefaultMaterial( QDir resources )
		: surfaceColor(new QtParameter())
	{
		this->setEffect(new FModelEffect(this, resources));

		surfaceColor->setName(QStringLiteral("surfaceColor"));
		this->addParameter(surfaceColor);

		this->setColor(1,1,1);
	}

	void setColor(float r, float g, float b) {
		surfaceColor->setValue(QColor::fromRgbF(r,g,b));
	}
};