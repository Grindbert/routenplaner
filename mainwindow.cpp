#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	{
	//Hilfsvariablen setzen:
	zaehler=0;
	hilfe=true;
	hilfszaehler=0;

	//Fenster anlegen:
	setAttribute(Qt::WA_DeleteOnClose);
	setGeometry(100, 100, 800, 600);	//Größe und Ort des "aufpoppens" festlegen
	setWindowTitle("Bastis fantastischer Routenplaner");

	//Widgets anlegen und im Fenster zentrieren:
	widget = new Widgets(this);	//Widgetcontainer anlegen
	setCentralWidget(widget);

	menuAnlegen();
	statuszeileAnlegen();

	//alle Vektoren, die für die Kacheln sind, auf Länge 9 setzen:
	kacheln.resize(9);
	pixmaps.resize(9);
	downl.resize(9);
	for(int i = 0; i<9; i++)		//die 9 Downloader (einer für jede
		{							//Kachel einen) anlegen
		downl[i]=new Downloader;
		}

	//Punkt, auf den die Karte beim Starten gesetzt wird, definieren:
	zoom=12;
	xkoord=2200;
	ykoord=1313;

	//Karte vom Startpunkt laden:
	starteKarte(zoom, xkoord, ykoord);

	//Buttons und Zeug aus dem Widgetcontainer mit Funktionen connecten:
	connect(widget->getButton(0), SIGNAL(clicked()), this, SLOT(geheNorden()));
	connect(widget->getButton(1), SIGNAL(clicked()), this, SLOT(geheSueden()));
	connect(widget->getButton(2), SIGNAL(clicked()), this, SLOT(geheOsten()));
	connect(widget->getButton(3), SIGNAL(clicked()), this, SLOT(geheWesten()));
	connect(widget->getButton(4), SIGNAL(clicked()), this, SLOT(zoomIn()));
	connect(widget->getButton(5), SIGNAL(clicked()), this, SLOT(zoomOut()));

	connect(widget->getView(), SIGNAL(zoomInSignal()), this, SLOT(zoomIn()));
	connect(widget->getView(), SIGNAL(zoomOutSignal()), this, SLOT(zoomOut()));

	connect(widget->getView()->scene(), SIGNAL(rechteMaustaste(QPointF)), this, SLOT(rechteMaustasteGeklickt(QPointF)));

	connect(widget->getView()->scene(), SIGNAL(linkeMaustasteGedruckt(bool,QPointF)), this, SLOT(bewegungTesten(bool,QPointF)));
	connect(widget->getView()->scene(), SIGNAL(linkeMaustasteLoslassen(bool,QPointF)), this, SLOT(bewegungTesten(bool,QPointF)));

	//anderes Hilfszeug:

	}


MainWindow::~MainWindow()
	{}


//Karte am Startpunkt laden, und Downloader so connecten, dass Kachel gleich in
//die Szene getan werden:
void MainWindow::starteKarte(int z, int x, int y)
	{
	for(int i=0; i<9; i++)
		{
		connect(downl[i], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));
		}
	setzeKarteNeu(z, x, y);
	}


//alle 9 Kacheln werden um das Zentrum geladen:
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

	qDebug()<<"Das ist die Ausgabe: "<<downl[1]->zwischenablage;
	qDebug()<<"bla ist: "<<downl[1]->bla->error();
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
	connect(ladeGraph, SIGNAL(triggered()), this, SLOT(graphLaden()));

	//Beenden-Button:
	QAction *beenden = new QAction(tr("&Beenden"), this);
	beenden->setShortcut(tr("Ctrl+T"));
	beenden->setStatusTip(tr("Programm beenden"));
	fileMenu->addAction(beenden);
	// qApp ist globale Variable der Applikation
	connect(beenden, SIGNAL(triggered()), qApp, SLOT(quit()));
	}


void MainWindow::statuszeileAnlegen()
	{
	statusLabel = new QLabel("Solange du das hier noch lesen kannst, ist alles in Ordnung! ;-)");
	statusBar()->addWidget(statusLabel);
	}


void MainWindow::pixmapAdden(QPixmap meinePix, int index)
	{
	pixmaps[index]=meinePix;
	if(hilfe)
		{
		kacheln[index]=widget->getView()->scene()->addPixmap(meinePix);
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
		kacheln[index]->setPixmap(meinePix);
		}
	}


void MainWindow::geheNorden()
	{
	//if(zaehler==0)
		//{
		ykoord=ykoord-1;

		setzeKarteNeu(zoom, xkoord, ykoord);

		/*for(int i = 0; i<punktvkt.size();i++)
			{
			if((punktvkt[i])->pos().y()>256)
				{
				widget->getView()->scene()->removeItem(punktvkt[i]);
				//delete punktvkt[i];
				//punktvkt.erase(i);
				std::cout<<"jetzt sollte er löschen...\n";
				}
			else
				{
				punktvkt[i]->moveBy(0, 256);
				}
			}*/

		//(kacheln[0])->setOffset(QPoint(0, 2));
		//(kacheln[1])->setOffset(QPoint(0, 2));
		//(kacheln[2])->setOffset(QPoint(0, 2));

		/*pixmaps[6]=pixmaps[3];
		pixmaps[7]=pixmaps[4];
		pixmaps[8]=pixmaps[5];

		pixmaps[3]=pixmaps[0];
		pixmaps[4]=pixmaps[1];
		pixmaps[5]=pixmaps[2];

		//std::cout<<"\n";
		for(int i=3; i<=8; i++)
			{
			kacheln[i]->setPixmap(pixmaps[i]);
			//kacheln[i]= new QGraphicsPixmapItem(pixmaps[i]);
			}

		downl[0]->ladeKachel(zoom,xkoord-1,ykoord-1,0);
		downl[1]->ladeKachel(zoom,xkoord,ykoord-1,1);
		downl[2]->ladeKachel(zoom,xkoord+1,ykoord-1,2);
		zaehler++;*/

	//	}
	//if(zaehler==1)
		//{
		/*kacheln[6]->setPixmap(kacheln[6]->pixmap());
		kacheln[7]->setPixmap(kacheln[7]->pixmap());
		kacheln[8]->setPixmap(kacheln[8]->pixmap());
		kacheln[0]->setPixmap(kacheln[0]->pixmap());
		kacheln[1]->setPixmap(kacheln[1]->pixmap());
		kacheln[2]->setPixmap(kacheln[2]->pixmap());
		kacheln[3]->setPixmap(kacheln[3]->pixmap());
		kacheln[4]->setPixmap(kacheln[4]->pixmap());
		kacheln[5]->setPixmap(kacheln[5]->pixmap());*/
		//}

	}


void MainWindow::geheSueden()
	{
	ykoord=ykoord+1;

	setzeKarteNeu(zoom, xkoord, ykoord);

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

	setzeKarteNeu(zoom, xkoord, ykoord);

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

	setzeKarteNeu(zoom, xkoord, ykoord);

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
		xkoord=xkoord*2;
		ykoord=ykoord*2;
		setzeKarteNeu(zoom, xkoord, ykoord);
		}
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


void MainWindow::rechteMaustasteGeklickt(QPointF punkt)
	{
	punktvkt.push_back(widget->koordSetzen(punkt));
	}


void MainWindow::bewegungTesten(bool jaOderNein, QPointF punkt)
	{
	if(jaOderNein)
		{
		mausDrag=punkt;
		qDebug()<<"Geklickt\n"<<mausDrag;
		}
	else
		{
		mausDrag=mausDrag-punkt;
		qDebug()<<"Losgelassen\n"<<mausDrag;
		}
	}




void MainWindow::graphLaden()
	{
	QString infile = QFileDialog::getOpenFileName(this, tr("Open Image"), "~", tr("All Files (*)"));
	//QFile inputFile(fileName);
	//inputFile.open(QIODevice::ReadOnly);
	//qDebug()<<fileName;

	//öffne InputFile:
	std::ifstream meineDatei(infile.toStdString().c_str());

	if(!meineDatei)
		{
		statusLabel->setText("Fehler: Konnte Datei nicht einlesen! Schreibfehler?");
		}

	else
		{
		unsigned int knotenzahl=0;
		unsigned int kantenzahl=0;

		//zum Einlesen der Knoten:
		std::string x;		//x- und y-Koordinaten werden zunächst in string
		std::string y;		//eingelesen und dann in float umgewandelt (geht
								//schneller als direktes Einlesen in float)

		//zum einlesen der Kanten:
		unsigned int start=0;	//Index vom Startknoten
		unsigned int ziel=0;	//Index vom Zielknoten
		std::string laenge;		//speichert Kantenlaene (siehe oben x- und
								//y-Koordinaten, warum als string)

		//Einlesen:
		meineDatei>>knotenzahl;
		std::vector<Knoten> *knoten = new std::vector<Knoten>(knotenzahl);

		meineDatei>>kantenzahl;

		//Knoten:
		for(unsigned int i = 0; i<knotenzahl; i++)
			{
			meineDatei>>x>>y;
			(*knoten)[i].setzeKoord(atof(x.c_str()),atof(y.c_str()),i);
			}

		//Kanten:
		for(unsigned int i = 0; i<kantenzahl; i++)
			{
			meineDatei>>start>>ziel>>laenge;
			(*knoten)[start].kanteHinzufuegen(&((*knoten)[ziel]),atof(laenge.c_str()));
			}


		/*for(int i = 0; i<(*knoten).size(); i++)
			{
			(*knoten)[i].print();
			}*/
		}
	}


void MainWindow::wegBerechnen()
	{
	statusLabel->setText("Klicken erfolgreich, Sir!");
	/*
	#include<iostream>	//cin und cout

	#include"Queue.h"
	*/

	//Timer zeit;
	//zeit.start();

	/*

	//Variablen, um Argumente aufzufangen:
	int st,zi;	//start- und zielnummer speichern

	*/

	/*
	//===============================================================
	//Wegfindung starten:
	bool *gibtWeg = new bool(false);	//um zu prüfen, ob ein Weg zwischen Start und Ziel existiert
	//zeit.start();
	std::vector<int> weg = Wegfindung(knoten, st, zi, gibtWeg);
	//zeit.stop();
	//Wenn es einen Weg gibt, printe ihn aus:
	if(*gibtWeg)
		{
		std::cout<<"Pfad von Knoten "<<weg[weg.size() -1]<<" zum Knoten "<<weg[0]<<" ist:\n"<<weg[weg.size() -1];
		for(int i = (weg.size()) -2; i>=0; i--)
			{
			std::cout<<" -> "<<weg[i];
			}
		std::cout<<"\n\n";
		}
	//zeit.stop();
	std::cout<<zeit.secs()<<std::endl;
	*/

	}


