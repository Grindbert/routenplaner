#ifndef HILFEFENSTER_H
#define HILFEFENSTER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "hilfewidget.h"

class Hilfefenster : public QMainWindow
	{
	Q_OBJECT

	Hilfewidget *widget;

	public:
	Hilfefenster(QWidget *parent = 0);
	};

#endif // HILFEFENSTER_H
