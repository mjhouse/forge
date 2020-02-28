#pragma once

#include <QtCore/QByteArray>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QEffect>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QGraphicsApiFilter>

class FModelEffect : public Qt3DRender::QEffect {
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
	FModelEffect(Qt3DRender::QMaterial* parent, QDir t_resources) 
		: Qt3DRender::QEffect(parent)
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

class FDefaultMaterial : public Qt3DRender::QMaterial {
public:
	FDefaultMaterial( QDir resources ) {
		this->setEffect(new FModelEffect(this, resources));
		
	}
};