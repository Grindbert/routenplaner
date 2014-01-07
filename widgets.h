#ifndef WIDGETS_H
#define WIDGETS_H

#include <QWidget>
#include <QMainWindow>
#include <QDial>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPoint>
#include <QFont>


class Widgets : public QWidget
	{
	Q_OBJECT

	QDial *qdial;
	QSpinBox *qspinbox;
	QGridLayout *gridLayout;
	QGraphicsView *graphicsView;

	public:
	QPushButton *nord;
	QPushButton *sued;
	QPushButton *ost;
	QPushButton *west;
	QPushButton *zoomInButton;
	QPushButton *zoomOutButton;



	public:
	explicit Widgets(QMainWindow *parent = 0);

	QGraphicsScene* getSzene();
	QGraphicsView* getView();
	};

#endif // WIDGETS_H
