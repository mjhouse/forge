#pragma once 

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QGeometryRenderer> 
#include <Qt3DExtras/Qt3DWindow>

#include <Qt3DCore/QNode>               
#include <Qt3DCore/QEntity>             
#include <Qt3DCore/QComponent>          
#include <Qt3DCore/QTransform>   
       

#include <Qt3DRender/QBuffer>           
#include <Qt3DRender/QAttribute>        
#include <Qt3DRender/QGeometry>         
#include <Qt3DRender/QGeometryRenderer> 
#include <Qt3DRender/QMaterial>         
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QObjectPicker>


#include <Qt3DInput/QMouseHandler>

typedef Qt3DRender::QGeometryRenderer::PrimitiveType QtRenderType;

typedef Qt3DRender::QBuffer					QtBuffer;
typedef Qt3DRender::QAttribute				QtAttribute;
typedef Qt3DRender::QGeometry				QtGeometry;
typedef Qt3DRender::QGeometryRenderer		QtRenderer;
typedef Qt3DRender::QMaterial				QtMaterial;
typedef Qt3DRender::QParameter				QtParameter;
typedef Qt3DRender::QEffect					QtEffect;
typedef Qt3DRender::QObjectPicker			QtObjectPicker;
typedef Qt3DRender::QFrameGraphNode			QtFrameGraphNode;
typedef Qt3DRender::QRenderSettings			QtRenderSettings;
typedef Qt3DRender::QRenderAspect			QtRenderAspect;

typedef Qt3DInput::QMouseHandler			QtMouseHandler;
typedef Qt3DInput::QInputSettings			QtInputSettings;
typedef Qt3DInput::QInputAspect				QtInputAspect;

typedef Qt3DCore::QNode						QtNode;
typedef Qt3DCore::QEntity					QtEntity;
typedef Qt3DCore::QComponent				QtComponent;
typedef Qt3DCore::QTransform				QtTransform;
typedef Qt3DCore::QAspectEngine				QtAspectEngine;
typedef Qt3DCore::QEntityPtr				QtEntityPtr;

typedef Qt3DExtras::Qt3DWindow				Qt3DWindow;
typedef Qt3DExtras::QOrbitCameraController	QtOrbitController;

typedef Qt3DLogic::QLogicAspect				QtLogicAspect;
