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
	
	QPushButton* m_button;		/*!< A button that triggers a create-model action */

	bool m_placing;

	void updateView(FModel* t_model);

public:
	ForgeCreate();
	
	void startCreate();

	void lengthChanged(QString t_input);

	void onParentMouseMove(QPoint t_point) override;

	void onParentMouseClick(QPoint t_point) override;

};

#endif