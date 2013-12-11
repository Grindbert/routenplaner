#include <QApplication>

#include "widgets.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
	{
	QApplication a(argc, argv);
	MainWindow* win = new MainWindow;
	win -> show();

	return a.exec();
	}
