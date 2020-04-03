#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <QtGui/QWindow>

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DRender/QGeometryRenderer> 
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>

#include <Qt3DCore/QNode>               
#include <Qt3DCore/QEntity>             
#include <Qt3DCore/QComponent>          
#include <Qt3DCore/QTransform>   

#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QBuffer>           
#include <Qt3DRender/QAttribute>        
#include <Qt3DRender/QGeometry>         
#include <Qt3DRender/QGeometryRenderer> 
#include <Qt3DRender/QMaterial>         
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QRenderStateSet>
#include <Qt3DRender/QLineWidth>
#include <Qt3DRender/QPickEvent>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QViewPort>
#include <Qt3DInput/QMouseHandler>

// typedefs for Qt enums
typedef Qt3DRender::QGeometryRenderer::PrimitiveType    QtRenderType;
typedef Qt3DRender::QGraphicsApiFilter::Api             QtRenderApi;
typedef Qt3DRender::QGraphicsApiFilter::OpenGLProfile   QtOpenGLProfile;

// typedefs for Qt classes
typedef Qt3DRender::QBuffer							QtBuffer;
typedef Qt3DRender::QAttribute						QtAttribute;
typedef Qt3DRender::QGeometry						QtGeometry;
typedef Qt3DRender::QGeometryRenderer				QtRenderer;
typedef Qt3DRender::QMaterial						QtMaterial;
typedef Qt3DRender::QParameter						QtParameter;
typedef Qt3DRender::QEffect							QtEffect;
typedef Qt3DRender::QObjectPicker					QtObjectPicker;
typedef Qt3DRender::QFrameGraphNode					QtFrameGraphNode;
typedef Qt3DRender::QRenderSettings					QtRenderSettings;
typedef Qt3DRender::QRenderAspect					QtRenderAspect;
typedef Qt3DRender::QRenderStateSet                 QtRenderStateSet;
typedef Qt3DRender::QLineWidth                      QtLineWidth;
typedef Qt3DRender::QShaderProgram                  QtShaderProgram;
typedef Qt3DRender::QRenderPass                     QtRenderPass;
typedef Qt3DRender::QFilterKey                      QtFilterKey;
typedef Qt3DRender::QTechnique                      QtTechnique;
typedef Qt3DRender::QPickEvent						QtPickEvent;
typedef Qt3DRender::QCamera							QtCamera;
typedef Qt3DRender::QViewport						QtViewport;

typedef Qt3DInput::QMouseHandler					QtMouseHandler;
typedef Qt3DInput::QInputSettings					QtInputSettings;
typedef Qt3DInput::QInputAspect						QtInputAspect;

typedef Qt3DCore::QNode								QtNode;
typedef Qt3DCore::QEntity							QtEntity;
typedef Qt3DCore::QComponent						QtComponent;
typedef Qt3DCore::QTransform						QtTransform;
typedef Qt3DCore::QAspectEngine						QtAspectEngine;
typedef Qt3DCore::QEntityPtr						QtEntityPtr;

typedef Qt3DExtras::Qt3DWindow						Qt3DWindow;
typedef Qt3DExtras::QOrbitCameraController      	QtOrbitController;
typedef Qt3DExtras::QFirstPersonCameraController	QtFpsController;
typedef Qt3DExtras::QAbstractCameraController		QtAbstractController;
typedef Qt3DExtras::QForwardRenderer				QtForwardRenderer;
typedef Qt3DRender::QFrameGraphNode					QtFrameGraphNode;

typedef Qt3DLogic::QLogicAspect						QtLogicAspect;

#endif //__DEFINES_H__