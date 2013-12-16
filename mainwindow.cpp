#include "mainwindow.h"
#include "widgets.h"
#include "downloader.h"
#include <QAction>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	{
	//Fenster anlegen:
	setAttribute(Qt::WA_DeleteOnClose);
	setGeometry(100, 100, 800, 600);

	//Widgets anlegen und im Fenster zentrieren:
	widget = new Widgets(this);
	setCentralWidget(widget);
	szene=widget->getSzene();	//Zeiger auf die graphicsScene holen

	menuAnlegen();
	statuszeileAnlegen();

	//Karte vom Startpunkt laden:
	kacheln.resize(9);
	starteKarte();
	}


MainWindow::~MainWindow()
	{}


void MainWindow::starteKarte()
	{
	std::vector<Downloader*> downl;
	downl.resize(8);

	for(int i = 0; i<9; i++)
		{
		downl[i]=new Downloader;
		}

	downl[0]->ladeKachel(12,2199,1312,0);
	connect(downl[0], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[1]->ladeKachel(12,2200,1312,1);
	connect(downl[1], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[2]->ladeKachel(12,2201,1312,2);
	connect(downl[2], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[3]->ladeKachel(12,2199,1313,3);
	connect(downl[3], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[4]->ladeKachel(12,2200,1313,4);
	connect(downl[4], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[5]->ladeKachel(12,2201,1313,5);
	connect(downl[5], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[6]->ladeKachel(12,2199,1314,6);
	connect(downl[6], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[7]->ladeKachel(12,2200,1314,7);
	connect(downl[7], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[8]->ladeKachel(12,2201,1314,8);
	connect(downl[8], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	}


void MainWindow::menuAnlegen()
	{
	//Datei-Menü:
	fileMenu = menuBar()->addMenu(tr("&Datei"));

	//Graph-laden-Button:
	QAction *ladeGraph = new QAction(tr("&Graph laden"), this);
	ladeGraph->setShortcut(tr("Ctrl+L"));
	ladeGraph->setStatusTip(tr("lies Graph von Textdatei ein"));
	fileMenu->addAction(ladeGraph);

	//Beenden-Button:
	QAction *quitAction = new QAction(tr("&Beenden"), this);
	quitAction->setShortcut(tr("Ctrl+T"));
	quitAction->setStatusTip(tr("Programm beenden"));
	fileMenu->addAction(quitAction);
	// qApp ist globale Variable der Applikation
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	}


void MainWindow::statuszeileAnlegen()
	{
	statusLabel = new QLabel("Hier entsteht bald ein sinnvoller Text.");
	statusBar()->addWidget(statusLabel);
	}

void MainWindow::pixmapAdden(QPixmap meinePix, int index)
	{
	kacheln[index]=szene->addPixmap(meinePix);

	switch(index)
		{
		case 0:
			(kacheln[0])->setOffset(QPoint(-256, -256));
			break;
		case 1:
			(kacheln[1])->setOffset(QPoint(0, -256));
			break;
		case 2:
			(kacheln[2])->setOffset(QPoint(256, -256));
			break;
		case 3:
			(kacheln[3])->setOffset(QPoint(-256, 0));
			break;
		case 4:
			//(kacheln[4])->setOffset(QPoint(0, 0));
			break;
		case 5:
			(kacheln[5])->setOffset(QPoint(256, 0));
			break;
		case 6:
			(kacheln[6])->setOffset(QPoint(-256, 256));
			break;
		case 7:
			(kacheln[7])->setOffset(QPoint(0, 256));
			break;
		case 8:
			(kacheln[8])->setOffset(QPoint(256, 256));
			break;
		}
	}
