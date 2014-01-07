#include "mainwindow.h"
//#include "widgets.h"
//#include "downloader.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	{
	zaehler=0;

	//Fenster anlegen:
	setAttribute(Qt::WA_DeleteOnClose);
	setGeometry(100, 100, 800, 600);

	//Widgets anlegen und im Fenster zentrieren:
	widget = new Widgets(this);
	setCentralWidget(widget);
	szene=widget->getSzene();	//Zeiger auf die graphicsScene holen

	//szene->setDragMode(QGraphicsView::ScrollHandDrag);

	menuAnlegen();
	statuszeileAnlegen();

	downl.resize(9);
	for(int i = 0; i<9; i++)
		{
		downl[i]=new Downloader;
		}

	//Karte vom Startpunkt laden:
	hilfe=true;
	hilfszaehler=0;
	zoom=12;
	xkoord=2200;
	ykoord=1313;
	kacheln.resize(9);
	starteKarte(zoom, xkoord, ykoord);


	connect(widget->nord, SIGNAL(clicked()), this, SLOT(geheNorden()));
	connect(widget->sued, SIGNAL(clicked()), this, SLOT(geheSueden()));
	connect(widget->ost, SIGNAL(clicked()), this, SLOT(geheOsten()));
	connect(widget->west, SIGNAL(clicked()), this, SLOT(geheWesten()));
	connect(widget->zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
	connect(widget->zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));
	}


MainWindow::~MainWindow()
	{}


void MainWindow::starteKarte(int z, int x, int y)
	{
	downl[0]->ladeKachel(z, x-1, y-1, 0);
	connect(downl[0], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[1]->ladeKachel(z, x, y-1, 1);
	connect(downl[1], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[2]->ladeKachel(z, x+1, y-1, 2);
	connect(downl[2], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[3]->ladeKachel(z, x-1, y, 3);
	connect(downl[3], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[4]->ladeKachel(z, x, y, 4);
	connect(downl[4], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[5]->ladeKachel(z, x+1, y, 5);
	connect(downl[5], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[6]->ladeKachel(z, x-1, y+1, 6);
	connect(downl[6], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[7]->ladeKachel(z, x, y+1, 7);
	connect(downl[7], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[8]->ladeKachel(z, x+1, y+1, 8);
	connect(downl[8], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));


	}


void MainWindow::setzeKarteNeu(int z, int x, int y)
	{
	downl[0]->ladeKachel(z, x-1, y-1, 0);
	downl[1]->ladeKachel(z, x, y-1, 1);
	downl[2]->ladeKachel(z, x+1, y-1, 2);
	downl[3]->ladeKachel(z, x-1, y, 3);
	downl[4]->ladeKachel(z, x, y, 4);
	downl[5]->ladeKachel(z, x+1, y, 5);
	downl[6]->ladeKachel(z, x-1, y+1, 6);
	downl[7]->ladeKachel(z, x, y+1, 7);
	downl[8]->ladeKachel(z, x+1, y+1, 8);
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
	if(hilfe)
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
		hilfszaehler++;
		if(hilfszaehler==9){hilfe=false;}
		}
	else
		{
		//std::cout<<"else-Zweig\n";
		kacheln[index]->setPixmap(meinePix);
		}
	}


void MainWindow::geheNorden()
	{
	//if(zaehler==0)
		//{
		ykoord=ykoord-1;

		//starteKarte(zoom, xkoord, ykoord);

		//(kacheln[0])->setOffset(QPoint(0, 2));
		//(kacheln[1])->setOffset(QPoint(0, 2));
		//(kacheln[2])->setOffset(QPoint(0, 2));

		/*for(int i=3; i<=8; i++)
			{
			std::cout<<i<<": "<<kacheln[i]<<std::endl;
			}*/

		kacheln[6]->setPixmap(kacheln[3]->pixmap());
		kacheln[7]->setPixmap(kacheln[4]->pixmap());
		kacheln[8]->setPixmap(kacheln[5]->pixmap());

		/*std::cout<<"\n";
		for(int i=6; i<=8; i++)
			{
			std::cout<<i<<": "<<kacheln[i]<<std::endl;
			}*/

		kacheln[3]->setPixmap(kacheln[0]->pixmap());
		kacheln[4]->setPixmap(kacheln[1]->pixmap());
		kacheln[5]->setPixmap(kacheln[2]->pixmap());

		downl[0]->ladeKachel(zoom,xkoord-1,ykoord-1,0);
		downl[1]->ladeKachel(zoom,xkoord,ykoord-1,1);
		downl[2]->ladeKachel(zoom,xkoord+1,ykoord-1,2);
		zaehler++;

	/*	}
	if(zaehler==1)
		{
		kacheln[6]->setPixmap(kacheln[6]->pixmap());
		kacheln[7]->setPixmap(kacheln[7]->pixmap());
		kacheln[8]->setPixmap(kacheln[8]->pixmap());
		kacheln[0]->setPixmap(kacheln[0]->pixmap());
		kacheln[1]->setPixmap(kacheln[1]->pixmap());
		kacheln[2]->setPixmap(kacheln[2]->pixmap());
		kacheln[3]->setPixmap(kacheln[3]->pixmap());
		kacheln[4]->setPixmap(kacheln[4]->pixmap());
		kacheln[5]->setPixmap(kacheln[5]->pixmap());
		}*/

	}


void MainWindow::geheSueden()
	{
	ykoord=ykoord+1;

	starteKarte(zoom, xkoord, ykoord);

	/*kacheln[0]->setPixmap(kacheln[3]->pixmap());
	kacheln[1]->setPixmap(kacheln[4]->pixmap());
	kacheln[2]->setPixmap(kacheln[5]->pixmap());

	kacheln[3]->setPixmap(kacheln[6]->pixmap());
	kacheln[4]->setPixmap(kacheln[7]->pixmap());
	kacheln[5]->setPixmap(kacheln[8]->pixmap());

	downl[6]->ladeKachel(zoom,xkoord-1,ykoord+1,6);
	connect(downl[6], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[7]->ladeKachel(zoom,xkoord,ykoord+1,7);
	connect(downl[7], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[8]->ladeKachel(zoom,xkoord+1,ykoord+1,8);
	connect(downl[8], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));
	*/}


void MainWindow::geheOsten()
	{
	xkoord=xkoord+1;

	starteKarte(zoom, xkoord, ykoord);

	/*kacheln[2]->setPixmap(kacheln[1]->pixmap());
	kacheln[5]->setPixmap(kacheln[4]->pixmap());
	kacheln[8]->setPixmap(kacheln[7]->pixmap());

	kacheln[1]->setPixmap(kacheln[0]->pixmap());
	kacheln[4]->setPixmap(kacheln[3]->pixmap());
	kacheln[7]->setPixmap(kacheln[6]->pixmap());

	downl[0]->ladeKachel(zoom,xkoord-1,ykoord-1,0);
	connect(downl[0], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[3]->ladeKachel(zoom,xkoord-1,ykoord,3);
	connect(downl[3], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[6]->ladeKachel(zoom,xkoord-1,ykoord+1,6);
	connect(downl[6], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));
	*/}


void MainWindow::geheWesten()
	{
	xkoord=xkoord-1;

	starteKarte(zoom, xkoord, ykoord);

	/*kacheln[0]->setPixmap(kacheln[1]->pixmap());
	kacheln[3]->setPixmap(kacheln[4]->pixmap());
	kacheln[6]->setPixmap(kacheln[7]->pixmap());

	kacheln[1]->setPixmap(kacheln[2]->pixmap());
	kacheln[4]->setPixmap(kacheln[5]->pixmap());
	kacheln[7]->setPixmap(kacheln[8]->pixmap());

	downl[2]->ladeKachel(zoom,xkoord+1,ykoord-1,2);
	connect(downl[2], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[5]->ladeKachel(zoom,xkoord+1,ykoord,5);
	connect(downl[5], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));

	downl[8]->ladeKachel(zoom,xkoord+1,ykoord+1,8);
	connect(downl[8], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));
	*/}

void MainWindow::zoomIn()
	{
	if(zoom<=18)
		{
		zoom=zoom+1;
		}
	xkoord=xkoord*2;
	ykoord=ykoord*2;
	setzeKarteNeu(zoom, xkoord, ykoord);
	}

void MainWindow::zoomOut()
	{
	if(zoom>2)
		{
		zoom=zoom-1;
		xkoord=xkoord/2;
		ykoord=ykoord/2;
		setzeKarteNeu(zoom, xkoord, ykoord);
		}
	}


void MainWindow::wheelEvent(QWheelEvent *event)
	{
	if(event->delta()>0)
		{
		//std::cout<<"zoomIn\n";
		zoomIn();
		}
	else if(event->delta()<0)
		{
		//std::cout<<"zoomOut\n";
		zoomOut();
		}
	}


/*bool MainWindow::eventFilter(QObject *object, QEvent *event)
	{
	if(object == widget->getView()->viewport() && event->type() == QEvent::Wheel)
		{
		//qDebug() << "SCroll";
		return true;
		}
	return false;
	}*/

//http://stackoverflow.com/questions/16279003/how-to-disable-scrolling-functionality-on-wheel-event-qgraphicsview-qt-c
