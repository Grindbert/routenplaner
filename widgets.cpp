#include "widgets.h"

#include <iostream>
#include "funktionen.h"

Widgets::Widgets(QMainWindow *parent) : QWidget(parent)
	{
	//Button und Zeug links im Fenster anlegen:
	xKoordLabel=new QLabel("lon: \nundefiniert");
	yKoordLabel=new QLabel("lat: \nundefiniert");

	nord=new QPushButton("N");
	sued=new QPushButton("S");
	ost=new QPushButton("O");
	west=new QPushButton("W");
	zoomInButton=new QPushButton("+");
	zoomOutButton=new QPushButton("-");

	//Buttongröße beschränken:
	int max=30;
	nord->setMaximumWidth(max);
	sued->setMaximumWidth(max);
	ost->setMaximumWidth(max);
	west->setMaximumWidth(max);

	nord->setFont(QFont("Helvetica", 16, QFont::Normal));
	sued->setFont(QFont("Helvetica", 16, QFont::Normal));
	ost->setFont(QFont("Helvetica", 16, QFont::Normal));
	west->setFont(QFont("Helvetica", 16, QFont::Normal));
	zoomInButton->setFont(QFont("Helvetica", 16, QFont::Normal));
	zoomOutButton->setFont(QFont("Helvetica", 16, QFont::Normal));

	//Buttons ins Grid-Layout packen:
	gridLayout = new QGridLayout(this);
	gridLayout->addWidget(nord, 0, 1);
	gridLayout->addWidget(sued, 2, 1);
	gridLayout->addWidget(ost, 1, 2);
	gridLayout->addWidget(west, 1, 0);
	gridLayout->addWidget(zoomInButton, 3, 0, 1, 3);
	gridLayout->addWidget(zoomOutButton, 4, 0, 1, 3);
	gridLayout->addWidget(xKoordLabel, 5, 0, 1, 3);
	gridLayout->addWidget(yKoordLabel, 6, 0, 1, 3);

	//Graphics-Scene anlegen und dem Grid-Layout hinzufügen:
	MeineSzene *meineSzene = new MeineSzene;
	graphicsView = new MeineView(meineSzene);

	//Scrollbars der GraphicsView ausschalten:
	graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//Dragmode setzen:
	graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

	//GraphicsView ins GridLayout packen:
	gridLayout->addWidget(graphicsView, 0,3,7,1);

	//Spalten schön hinziehen, damit Buttons schmal und Karte groß:
	//gridLayout->setColumnStretch(3, 20);

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


/*QGraphicsEllipseItem* Widgets::koordSetzen(QPointF punkt,int x, int y, int z)
	{
	xKoordLabel->setText("lon: "+QString::number(punkt.x()));
	yKoordLabel->setText("lat: "+QString::number(punkt.y()));

	//double tilex=long2tile(punkt.x(),z);
	//double tiley=lat2tile(punkt.y(),z);

	//return(graphicsView->scene()->addEllipse((tilex-x)*256,(tiley-y)*256,4.5,4.5,QPen(Qt::blue),QBrush(Qt::blue)));
	}*/


void Widgets::koordSetzen(QPointF punkt)
	{
	xKoordLabel->setText("lon: \n"+QString::number(punkt.x()));
	yKoordLabel->setText("lat: \n"+QString::number(punkt.y()));
	}
