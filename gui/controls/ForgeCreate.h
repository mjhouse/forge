#ifndef __FORGECREATE_H__
#define __FORGECREATE_H__

#include "ForgeControl.h"
#include "FModel.h"
#include "FModelExtruded.h"

class ForgeCreate : public ForgeControl {
private:
	
	float length = 0.5;

	FModelExtruded* m_model;

	QLineEdit* m_lengthInput;
	
	QPushButton* m_button;

	void updateView();

public:
	ForgeCreate();
	
	void startCreate();

	void lengthChanged(QString t_input);

};

#endif