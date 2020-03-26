#ifndef __FORGECREATE_H__
#define __FORGECREATE_H__

#include "ForgeControl.h"
#include "FModelExtruded.h"
#include "FModel.h"

class ForgeCreate : public ForgeControl {
private:
	
	float m_length;				/*!< The length of the active model */

	FModelExtruded* m_model;	/*!< The active model */

	QLineEdit* m_lengthInput;	/*!< A text input used for length input */

	bool m_placing;

	void updateView(FModel* t_model);

	void onMouseMove(Message<QMouseEvent*>* t_message);
	
	void finishCreate();

	void positionModel(QPoint t_point);

public:
	ForgeCreate(ForgeWindow* t_parent);
	
	void deleteModel();

	void startCreate();

	void lengthChanged(QString t_input);

	void onMessage(Channel t_channel, UnknownMessage& t_message) override;

};

#endif