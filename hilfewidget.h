#ifndef HILFEWIDGET_H
#define HILFEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

class Hilfewidget : public QWidget
	{
	Q_OBJECT

	QPushButton *ok;
	QLabel *text;
	QGridLayout *grid;

	public:
	explicit Hilfewidget(QWidget *parent = 0);
	QPushButton* getOK();

	signals:

	public slots:

	};

#endif // HILFEWIDGET_H
