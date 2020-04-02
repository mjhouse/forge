#ifndef __F_ORIGIN_H__
#define __F_ORIGIN_H__

#include "FModel.h"
#include "FLine.h"

class FOrigin : public FModel {
private:

	FModel* xAxis;	/*!< the X-Axis FModel */

	FModel* yAxis;	/*!< the Y-Axis FModel */

	FModel* zAxis;	/*!< the Z-Axis FModel */

public:
	FOrigin();

};

#endif