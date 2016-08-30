#include "qtapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qtApp w;
	w.show();
	return a.exec();
}
