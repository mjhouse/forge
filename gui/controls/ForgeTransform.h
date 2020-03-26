#ifndef __FORGETRANSFORM_H__
#define __FORGETRANSFORM_H__

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "ForgeWindow.h"
#include "ForgeControl.h"
#include "FModel.h"

class ForgeTransform : public ForgeControl {
	Q_OBJECT

private:

	QLineEdit* m_posX;		/*!< Translation X double input */

	QLineEdit* m_posY;		/*!< Translation Y double input */

	QLineEdit* m_posZ;		/*!< Translation Z double input */

	QLineEdit* m_rotX;		/*!< Rotation X double input */

	QLineEdit* m_rotY;		/*!< Rotation Y double input */

	QLineEdit* m_rotZ;		/*!< Rotation Z double input */

public:
	ForgeTransform(ForgeWindow* t_parent);

	void updateView(FModel* t_model);

	void updateModel();

};

#endif // __FORGETRANSFORM_H__