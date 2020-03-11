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
	std::vector<QVector3D> m_vertices;  /*!< Vertices of the line */

	std::vector<uint> m_indices;		/*!< Indices of the line */

public:
	FLine(std::vector<QVector3D> t_coordinates);

	FGeometry* toGeometry();

	void updateGeometry(FGeometry* t_geometry);
};

#endif // __FLINE_H__