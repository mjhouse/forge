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

class FLine : public FSymbol {
private:	

	std::vector<QVector3D> m_vertices;	/*!< The vertices of the line */

	FGeometry* m_geometry;				/*!< The geometry maintained by this symbol */

protected:
	void propertyChanged(std::string t_name, FProperty t_property) {

	}

public:
	FLine();

	FLine(FLine* t_other);

	FLine(QVector3D t_start, QVector3D t_end);

	/* Set the reference points of the crosssection */
	void setGeometry(std::vector<QVector3D>& t_points);

	/* Convert the crosssection to 3D geometry */
	FGeometry* toGeometry();

	/* Update the associated geometry */
	void updateGeometry();

	FSymbol* copy() {
		return new FLine(this);
	}

};

#endif // __FLINE_H__