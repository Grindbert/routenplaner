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
#include <QLabel>
#include <string>
#include <QGraphicsEllipseItem>

#include "meineView.h"
#include "meineSzene.h"

class Widgets : public QWidget
	{
	Q_OBJECT

	private:
	//QDial *qdial;
	//QSpinBox *qspinbox;
	//QPushButton *test;

	QGridLayout *gridLayout;
	MeineView *graphicsView;
	//enum button {N=0, S, O, W, In, Out};

	QPushButton *nord;
	QPushButton *sued;
	QPushButton *ost;
	QPushButton *west;
	QPushButton *zoomInButton;
	QPushButton *zoomOutButton;
	QPushButton *goButton;

	QLabel *mausKoordLabel;
	QLabel *startKoordLabel;
	QLabel *zielKoordLabel;

	public:
	explicit Widgets(QMainWindow *parent = 0);
	QGraphicsEllipseItem* punktMalen(QPointF,QPointF,int,int,int);
	void mausKoordSetzen(QPointF);
	void startKoordSetzen(QPointF);
	void zielKoordSetzen(QPointF);

	MeineView* getView();
	QPushButton* getButton(int /*enum button*/);
	};

#endif // WIDGETS_H
