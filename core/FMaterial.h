#ifndef __FMATERIAL_H__
#define __FMATERIAL_H__

#include <QtCore/QByteArray>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QGraphicsApiFilter>

#include "Defines.h"

class FSymbol;

class FMaterial : public QtMaterial {
private:
	QColor m_original;				/*!< The original color of the material */

	QColor m_current;				/*!< The current color of the material */

	QtParameter* m_surfaceColor;	/*!< The QtParameter object for the current color*/

	void initialize(const char* t_vshader, const char* t_fshader);

public:
	FMaterial(QColor t_color, const char* t_vshader, const char* t_fshader);

	FMaterial(FSymbol* t_symbol, QColor t_color);

	void setColor(QColor t_color);

	void setColor(float t_r, float t_g, float t_b);

	QColor color();

	void resetColor();
};

#endif // __FMATERIAL_H__