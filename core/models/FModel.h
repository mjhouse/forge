#ifndef __FMODEL_H__
#define __FMODEL_H__

#include <Qt3DCore/QEntity>
#include <QtWidgets/QWidget>
#include <Qt3DRender/QGeometryRenderer>

#include <HasIdentifier.h>

#include "FMaterial.h"
#include "FGeometry.h"
#include "Defines.h"

#define RED QColor::fromRgbF(1.0,0.3,0.3)

class FModel : public QtEntity, 
			   public HasIdentifier {
private:

	FGeometry* m_geometry;		/*!< The geometry of the model */

	QtTransform* m_transform;	/*!< Location and rotation */

	FMaterial* m_material;		/*!< Rendering material */

	QtRenderer* m_renderer;		/*!< Renderer provided by FGeometry */

	bool m_selectable;			/*!< True if user can interact with the model */

public:

	FModel(FGeometry* t_section, QtTransform* t_transform, FMaterial* t_material);

	FModel(FGeometry* t_section, QColor t_color);

	FModel(FGeometry* t_section);

	FModel();
	
	QtTransform* transform();

	FGeometry* geometry();

	QtRenderer* renderer();
	
	void setSelectable(bool t_selectable);

	bool selectable();

	void unHighlight();

	void highlight();

	bool hidden();

	void hide();

	void show();
};

#endif // __FMODEL_H__