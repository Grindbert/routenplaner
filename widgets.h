#ifndef WIDGETS_H
#define WIDGETS_H

#include <QWidget>
#include <QMainWindow>
#include <QDial>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsView>

class Widgets : public QWidget
{
	Q_OBJECT

	QDial *qdial;
	QSpinBox *qspinbox;
	QPushButton *maxWertButton;
	QGridLayout *gridLayout;
	QGraphicsView *graphicsView;

	public:
	explicit Widgets(QMainWindow *parent = 0);



	signals:

	public slots:

	};

#endif // WIDGETS_H
