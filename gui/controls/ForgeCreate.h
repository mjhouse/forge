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

	QLineEdit* m_lengthInput;	/*!< A text input used for length input */

	BulkLoader m_loader;

	FSymbol* m_symbol;

	PlacementType m_mode;

	QVector3D m_current;

	void updateView();

	void onParentMouseMove(QMouseEvent* t_event);

	void onParentMouseRelease(QMouseEvent* t_event);

public:
	ForgeCreate(ForgeWindow* t_parent);
	
	void deleteModel();
	
	void updateModel();

	void moveModel(QPoint t_point);

	void extrudeModel(QPoint t_point);

	void positionModel(QPoint t_point);
	
	void lengthChanged(QString t_input);

	void selectionChanged(const QString& t_input);
};

#endif