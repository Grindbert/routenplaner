#ifndef WARTEWIDGET_H
#define WARTEWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QGridLayout>

class Wartewidget : public QWidget
	{
	Q_OBJECT

	QLabel *label;
	QProgressBar *balken;
	QGridLayout *grid;

	public:
	explicit Wartewidget(QWidget *parent = 0);
	QLabel* getLabel();
	QProgressBar* getBalken();

	signals:

	public slots:

	};

#endif // WARTEWIDGET_H
