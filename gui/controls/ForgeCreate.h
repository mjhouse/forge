#ifndef __FORGECREATE_H__
#define 

#include "ForgeControl.h"

class ForgeCreate : public ForgeControl {
private:
	QPushButton* button;

	FModel* active = nullptr;

	float length = 0.5;
};

#endif