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
#include <string>

#include "meineView.h"

class Widgets : public QWidget
	{
	Q_OBJECT

	private:
	QDial *qdial;
	//QSpinBox *qspinbox;
	QPushButton *test;

	QGridLayout *gridLayout;
	MeineView *graphicsView;
	//enum button {N=0, S, O, W, In, Out};

	QPushButton *nord;
	QPushButton *sued;
	QPushButton *ost;
	QPushButton *west;
	QPushButton *zoomInButton;
	QPushButton *zoomOutButton;

	public:
	explicit Widgets(QMainWindow *parent = 0);

	QGraphicsScene* getSzene();
	MeineView* getView();
	QPushButton* getButton(int /*enum button*/);
	};

#endif // WIDGETS_H
