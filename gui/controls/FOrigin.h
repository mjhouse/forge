#ifndef __F_ORIGIN_H__
#define __F_ORIGIN_H__

#include "FModel.h"
#include "FModelLine.h"

class FOrigin : public FModel {
private:

	FModelLine* xAxis;	/*!< the X-Axis FModel */

	FModelLine* yAxis;	/*!< the Y-Axis FModel */

	FModelLine* zAxis;	/*!< the Z-Axis FModel */

public:
	FOrigin();

};

#endif