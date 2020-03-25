#ifndef __FLINE_H__
#define __FLINE_H__
      
#include <QtGui/QVector3D>
#include <QtWidgets/QWidget>

#include "FGeometry.h"
#include "Defines.h"

#include <vector>

#define DEPTH_NORMAL QVector3D(0.0, 0.0, 1.0)
#define DEPTH_LENGTH 0.5

class FLine : public QWidget {
	Q_OBJECT

private:	

	float m_width;
	
	QVector3D m_start;

	QVector3D m_end;

public:
	FLine(QVector3D t_start, QVector3D t_end);

	FGeometry* toGeometry();

	void updateGeometry(FGeometry* t_geometry);

	void setWidth(float t_width);

	float width();

};

#endif // __FLINE_H__