#include "testQGL1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testQGL1 w;
	w.show();
	return a.exec();
}
