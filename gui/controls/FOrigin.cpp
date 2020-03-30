#include "FOrigin.h"

/*! \brief Construct the three FModel objects that make up the
 *		   origin display (x, y and z axis lines).
 */
FOrigin::FOrigin() 
	: FModel()
{
	zAxis = new FModel(
		new FLine(QVector3D(0, 0, 0), QVector3D(0, 0, 1)), QColor::fromRgbF(0, 0, 1));
	zAxis->setParent(this);
;
	yAxis = new FModel(
		new FLine(QVector3D(0, 0, 0), QVector3D(0, 1, 0)), QColor::fromRgbF(0, 1, 0));
	yAxis->setParent(this);

	xAxis = new FModel(
		new FLine(QVector3D(0, 0, 0), QVector3D(1, 0, 0)), QColor::fromRgbF(1, 0, 0));
	xAxis->setParent(this);

}