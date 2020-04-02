#ifndef __FORGECREATE_H__
#define __FORGECREATE_H__

#include "ForgeControl.h"
#include "BulkLoader.h"
#include "FModel.h"

enum class PlacementType {
	None,
	Start,
	End
};

class ForgeCreate : public ForgeControl {
private:
	
	float m_length;				/*!< The length of the active model */

	FModel* m_model;	/*!< The active model */

	QLineEdit* m_lengthInput;	/*!< A text input used for length input */

	BulkLoader m_loader;

	FSymbol* m_symbol;

	PlacementType m_mode;

	QVector3D m_current;

	void updateView(FModel* t_model);

	void onMouseMove(Message<QMouseEvent*>* t_message);

public:
	ForgeCreate(ForgeWindow* t_parent);
	
	void deleteModel();
	
	void updateModel();

	void moveModel(QPoint t_point);

	void extrudeModel(QPoint t_point);

	void positionModel(QPoint t_point);



	void lengthChanged(QString t_input);

	void selectionChanged(const QString& t_input);

	void onMessage(Channel t_channel, UnknownMessage& t_message) override;

};

#endif