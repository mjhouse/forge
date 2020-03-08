#ifndef __FORGECREATE_H__
#define __FORGECREATE_H__

#include "ForgeControl.h"
#include "FModel.h"
#include "FModelExtruded.h"

class ForgeCreate : public ForgeControl {
private:
	QPushButton* button;

	float length = 0.5;

	FModelExtruded* m_model;
	
public:
	ForgeCreate();

	void cancelCreate();

	void finishCreate();

	void startCreate();

	void lengthChanged(QString t_input);
};

#endif