#include "FOrigin.h"

/*! \brief Construct the three FModel objects that make up the
 *		   origin display (x, y and z axis lines).
 */
FOrigin::FOrigin() 
	: FModel()
{
	FLine* zline = new FLine(QVector3D(0, 0, 0), QVector3D(0, 0, 1));

	zAxis = new FModelLine(zline, QColor::fromRgbF(0, 0, 1));
	zAxis->setParent(this);

	FLine* yline = new FLine(QVector3D(0, 0, 0), QVector3D(0, 1, 0));
	yAxis = new FModelLine(yline, QColor::fromRgbF(0, 1, 0));
	yAxis->setParent(this);

	FLine* xline = new FLine(QVector3D(0, 0, 0), QVector3D(1, 0, 0));
	xAxis = new FModelLine(xline, QColor::fromRgbF(1, 0, 0));
	xAxis->setParent(this);

}