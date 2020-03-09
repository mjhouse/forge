#ifndef __F_ORIGIN_H__
#define __F_ORIGIN_H__

#include "FModel.h"
#include "FModelLine.h"

class FOrigin : public FModel {
private:

	FModelLine* xAxis;

	FModelLine* yAxis;

	FModelLine* zAxis;

public:
	FOrigin();

};

#endif