#ifndef WARTEFENSTER_H
#define WARTEFENSTER_H

#include <QMainWindow>

#include "wartewidget.h"

class Wartefenster : public QMainWindow
	{
	Q_OBJECT

	Wartewidget *widget;

	public:
	explicit Wartefenster(QWidget *parent = 0);
	void setText(QString);
	void setStatusBalken(int);

	signals:

	public slots:

	};

#endif // WARTEFENSTER_H
