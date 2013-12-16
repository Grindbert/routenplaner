#include "widgets.h"
//#include "downloader.h"

Widgets::Widgets(QMainWindow *parent) : QWidget(parent)
	{
	//Button und Zeug links im Fenster anlegen:
	qdial=new QDial;
	qspinbox=new QSpinBox;

	//Buttons:
	nord=new QPushButton("^\n|");
	sued=new QPushButton("|\nV");
	ost=new QPushButton("-->");
	west=new QPushButton("<--");

	nord->setFont(QFont("Helvetica", 16, QFont::Normal));
	sued->setFont(QFont("Helvetica", 16, QFont::Normal));
	ost->setFont(QFont("Helvetica", 16, QFont::Normal));
	west->setFont(QFont("Helvetica", 16, QFont::Normal));

	qdial->setNotchesVisible(true);
	qspinbox->setFont(QFont("Helvetica", 12, QFont::StyleNormal));

	//Sachen ins Grid-Layout packen:
	gridLayout = new QGridLayout(this);
	gridLayout->addWidget(nord, 0, 0);
	gridLayout->addWidget(sued, 1, 0);
	gridLayout->addWidget(ost, 2, 0);
	gridLayout->addWidget(west, 3, 0);
	gridLayout->addWidget(qspinbox, 4, 0);
	gridLayout->addWidget(qdial, 5, 0);

	//Graphics-Scene anlegen und dem Grid-Layout hinzufügen:
	QGraphicsScene *meineSzene = new QGraphicsScene;
	graphicsView = new QGraphicsView(meineSzene);

	gridLayout->addWidget(graphicsView, 0,1,6,1);

	//Spalten schön hinziehen, damit Buttons schmal und Karte groß:
	gridLayout->setColumnStretch(1, 10);
	setLayout(gridLayout);
	}

QGraphicsScene* Widgets::getSzene()
	{
	return(graphicsView->scene());
	}
