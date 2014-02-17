#include "hilfefenster.h"

Hilfefenster::Hilfefenster(QWidget *parent) : QMainWindow(parent)
	{
	setGeometry(200, 200, 430, 400);
	setWindowTitle("Hilfe");

	widget = new Hilfewidget(this);

	setCentralWidget(widget);

	connect(widget->getOK(), SIGNAL(clicked()), this, SLOT(hide()));
	}
