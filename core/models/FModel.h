#ifndef __FMODEL_H__
#define __FMODEL_H__

#include <Qt3DCore/QEntity>
#include <QtWidgets/QWidget>
#include <Qt3DRender/QGeometryRenderer>

#include <HasIdentifier.h>

#include "FMaterial.h"
#include "FGeometry.h"
#include "FSymbol.h"
#include "Defines.h"

#define RED QColor::fromRgbF(1.0,0.3,0.3)

#define PI 3.14159265358979323846
#define ax(r,a) (r * std::cosf(a))
#define ay(r,a) (r * std::sinf(a))

class FModel : public QtEntity, 
			   public HasIdentifier {
private:

	FSymbol* m_symbol;

	FGeometry* m_geometry;		/*!< The geometry of the model */

	QtTransform* m_transform;	/*!< Location and rotation */

	FMaterial* m_material;		/*!< Rendering material */

	QtRenderer* m_renderer;		/*!< Renderer provided by FGeometry */

	bool m_selectable;			/*!< True if user can interact with the model */

	QtObjectPicker* m_picker;

	void onClick(Qt3DRender::QPickEvent* t_event);

public:

	FModel(FSymbol* t_section, QtTransform* t_transform, FMaterial* t_material);

	FModel(FSymbol* t_section, QColor t_color);

	FModel(FSymbol* t_section);

	FModel();

	~FModel();
	
	FSymbol* symbol();

	FGeometry* geometry();

	QtTransform* transform();

	FMaterial* material();

	QtRenderer* renderer();
		
	void setSelectable(bool t_selectable);

	bool selectable();

	void unHighlight();

	void highlight();

	bool hidden();

	void hide();

	void show();

};

#undef PI
#undef ax
#undef ay
#endif // __FMODEL_H__