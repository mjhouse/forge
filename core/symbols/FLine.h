#ifndef __FLINE_H__
#define __FLINE_H__
      
#include <QtGui/QVector3D>
#include <QtWidgets/QWidget>

#include "FGeometry.h"
#include "FSymbol.h"
#include "Defines.h"

#include <vector>

#define DEPTH_NORMAL QVector3D(0.0, 0.0, 1.0)
#define DEPTH_LENGTH 0.5

class FLine : public QWidget, public FSymbol {
	Q_OBJECT

private:	

	std::vector<QVector3D> m_vertices;	/*!< The vertices of the line */

public:
	FLine();

	FLine(QVector3D t_start, QVector3D t_end);

	FGeometry* toGeometry();

	void updateGeometry(FGeometry* t_geometry);

	void setGeometry(std::vector<QVector3D>& t_points);

};

#endif // __FLINE_H__