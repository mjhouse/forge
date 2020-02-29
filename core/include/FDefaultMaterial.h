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

	const QByteArray vertex_shader = "  \n\
		#version 330					\n\
		uniform mat4 mvp;				\n\
		uniform mat4 modelView;			\n\
		uniform mat4 modelMatrix;		\n\
		uniform vec3 eyePosition;		\n\
										\n\
		in vec3 vertexPosition;			\n\
		in vec3 vertexNormal;			\n\
										\n\
		out vec3 viewPosition;			\n\
		out vec3 cameraVector;			\n\
										\n\
		void main(void)					\n\
		{								\n\
			gl_Position = mvp * vec4(vertexPosition, 1);				\n\
																		\n\
			viewPosition = (modelView * vec4(vertexPosition, 1)).xyz;	\n\
			cameraVector = normalize(eyePosition - viewPosition);		\n\
		}																\n\
	";

	const QByteArray fragment_shader = "										\n\
		#version 330 core                                                       \n\
																				\n\
		uniform vec3 surfaceColor;                                              \n\
																				\n\
		out vec4 color;                                                         \n\
																				\n\
		// the world-space position of the triggering                           \n\
		// vertex                                                               \n\
		in vec3 viewPosition;                                                   \n\
																				\n\
		// a vector from the triggering vertex to the                           \n\
		// camera position                                                      \n\
		in vec3 cameraVector;                                                   \n\
																				\n\
		void main()                                                             \n\
		{                                                                       \n\
			vec3 xTangent = dFdx( viewPosition );                               \n\
			vec3 yTangent = dFdy( viewPosition );                               \n\
																				\n\
			// normal for this entire face (all fragments                       \n\
			// facing the same direction)                                       \n\
			vec3 faceNormal = normalize( cross( xTangent, yTangent ) );         \n\
																				\n\
			// calculate direction relative to the camera                       \n\
			float direction = dot(faceNormal,cameraVector);                     \n\
			float faceAngle = acos(direction);                                  \n\
																				\n\
			// adjust and constrain the angle so that we get                    \n\
			// varying per-face shading                                         \n\
			float angle = 1/clamp(faceAngle,1,3);                               \n\
			color = vec4(surfaceColor * angle,1);                               \n\
		}                                                                       \n\
	";

public:
	FModelEffect(QtMaterial* parent) 
		: QtEffect(parent)
	{
		auto shader = new Qt3DRender::QShaderProgram(parent);
		
		shader->setVertexShaderCode(vertex_shader);
		shader->setFragmentShaderCode(fragment_shader);

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
	FDefaultMaterial(QColor t_color)
		: surfaceColor(new QtParameter())
	{
		this->setEffect(new FModelEffect(this));

		surfaceColor->setName(QStringLiteral("surfaceColor"));
		this->addParameter(surfaceColor);

		this->setColor(t_color);
	}

	void setColor(QColor t_color) {
		surfaceColor->setValue(t_color);
	}

	void setColor(float r, float g, float b) {
		setColor(QColor::fromRgbF(r, g, b));
	}
};