#include "widgets.h"

#include <iostream>

Widgets::Widgets(QMainWindow *parent) : QWidget(parent)
	{
	//Button und Zeug links im Fenster anlegen:
	//qdial=new QDial;
	//qspinbox=new QSpinBox;
	//test=new QPushButton("test");

	//qdial->setNotchesVisible(true);
	//qspinbox->setFont(QFont("Helvetica", 12, QFont::StyleNormal));

	xKoordLabel=new QLabel("x: undefiniert");
	yKoordLabel=new QLabel("y: undefiniert");

	//Buttons:
	nord=new QPushButton("/\\\n|");
	sued=new QPushButton("|\nV");
	ost=new QPushButton("-->");
	west=new QPushButton("<--");
	zoomInButton=new QPushButton("+");
	zoomOutButton=new QPushButton("-");

	nord->setFont(QFont("Helvetica", 16, QFont::Normal));
	sued->setFont(QFont("Helvetica", 16, QFont::Normal));
	ost->setFont(QFont("Helvetica", 16, QFont::Normal));
	west->setFont(QFont("Helvetica", 16, QFont::Normal));
	zoomInButton->setFont(QFont("Helvetica", 16, QFont::Normal));
	zoomOutButton->setFont(QFont("Helvetica", 16, QFont::Normal));

	//Buttons ins Grid-Layout packen:
	gridLayout = new QGridLayout(this);
	gridLayout->addWidget(nord, 0, 0);
	gridLayout->addWidget(sued, 1, 0);
	gridLayout->addWidget(ost, 2, 0);
	gridLayout->addWidget(west, 3, 0);
	gridLayout->addWidget(zoomInButton, 4, 0);
	gridLayout->addWidget(zoomOutButton, 5, 0);
	gridLayout->addWidget(xKoordLabel, 6, 0);
	gridLayout->addWidget(yKoordLabel, 7, 0);
	//gridLayout->addWidget(qspinbox, 6, 0);
	//gridLayout->addWidget(test, 6, 0);
	//gridLayout->addWidget(qdial, 7, 0);

	//Graphics-Scene anlegen und dem Grid-Layout hinzufügen:
	MeineSzene *meineSzene = new MeineSzene;
	graphicsView = new MeineView(meineSzene);

	//Scrollbars der GraphicsView ausschalten:
	graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//Dragmode setzen:
	graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

	//GraphicsView ins GridLayout packen:
	gridLayout->addWidget(graphicsView, 0,1,8,1);

	//Spalten schön hinziehen, damit Buttons schmal und Karte groß:
	gridLayout->setColumnStretch(1, 10);
	setLayout(gridLayout);

	}


//soll Zeiger auf die View zurückgeben:
MeineView* Widgets::getView()
	{
	return(graphicsView);
	}


//soll Zeiger auf den gewünschten Button zurückgeben:
QPushButton* Widgets::getButton(int nummer /*enum button*/)
	{
	switch(nummer)
		{
		case 0:
			return(nord);
			break;
		case 1:
			return(sued);
			break;
		case 2:
			return(ost);
			break;
		case 3:
			return(west);
			break;
		case 4:
			return(zoomInButton);
			break;
		case 5:
			return(zoomOutButton);
			break;
		//case 6:
		//	return(test);
		//	break;
		}
	//return(new QPushButton()); //gegen die Warnungen beim Kompilieren
	}


void Widgets::koordSetzen(QPointF punkt)
	{
	xKoordLabel->setText("x: "+QString::number(punkt.x()));
	yKoordLabel->setText("y: "+QString::number(punkt.y()));
	graphicsView->scene()->addEllipse(punkt.x(),punkt.y(),4.5,4.5,QPen(Qt::blue),QBrush(Qt::blue));
	}
