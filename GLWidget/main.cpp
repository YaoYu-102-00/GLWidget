#include "GLWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GLWidget w;
	w.resize(600, 600);
	w.setWindowTitle(QObject::tr("Michael's OpenGL Framework"));
	w.show();
	return a.exec();
}
