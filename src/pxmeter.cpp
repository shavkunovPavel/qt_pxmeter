#include "qapplication.h"
#include "pxwindow.h"

int main (int argc, char** argv) {
	QApplication app(argc, argv);
	PxWindow mypx;
	mypx.show();
	return app.exec();
}
