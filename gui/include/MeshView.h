#pragma once

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>

class MeshView : public Qt3DExtras::Qt3DWindow {
private:
	Qt3DCore::QEntity* root;

public:
	MeshView(int color);

	void setRootEntity(Qt3DCore::QEntity* t_root);
	Qt3DCore::QEntity* rootEntity();

	void resizeEvent(QResizeEvent* event);

};