#pragma once

#include <QtWidgets/QApplication>

class ForgeApplication : public QApplication {
private:
	
	QDir rootPath;

	QDir resourcesPath;

public:

	ForgeApplication(int argc, char* argv[])
		: QApplication(argc, argv) {

		rootPath = applicationDirPath();
		resourcesPath = QDir(rootPath.filePath("resources"));
	}

	static ForgeApplication* instance() {
		return (ForgeApplication*)QApplication::instance();
	}

	QDir root() {
		return this->rootPath;
	}

	QDir resources() {
		return this->resourcesPath;
	}

};