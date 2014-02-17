#include "wartewidget.h"

Wartewidget::Wartewidget(QWidget *parent) : QWidget(parent)
	{
	label = new QLabel(" ");

	balken = new QProgressBar();
	balken->setValue(42);

	grid = new QGridLayout(this);

	grid->addWidget(label, 0, 0);
	grid->addWidget(balken,1, 0);

	setLayout(grid);
	}


QLabel* Wartewidget::getLabel()
	{
	return(label);
	}


QProgressBar* Wartewidget::getBalken()
	{
	return(balken);
	}
