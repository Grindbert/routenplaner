#include "wartefenster.h"

Wartefenster::Wartefenster(QWidget *parent) : QMainWindow(parent)
	{
	setGeometry(300, 300, 300, 50);
	setWindowTitle("Bitte warten...");

	widget = new Wartewidget();

	setCentralWidget(widget);
	}


void Wartefenster::setText(QString neuerText)
	{
	widget->getLabel()->setText(neuerText);
	}


void Wartefenster::setStatusBalken(int prozent)
	{
	widget->getBalken()->setValue(prozent);
	}
