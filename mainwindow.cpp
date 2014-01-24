#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	{
	//Hilfsvariablen setzen:
	zaehler=0;

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
	sichtbaresFeld=5;
	seitenlaenge=3*sichtbaresFeld;
	anzahlKacheln=seitenlaenge*seitenlaenge;
	mausDrag=QPointF(0,0);
	kacheln.resize(anzahlKacheln);
	perm.resize(anzahlKacheln+seitenlaenge);
	for(unsigned int i=0;i<perm.size();i++)
		{
		perm[i]=i;
		}
	//pixmaps.resize(anzahlKacheln);
	downl.resize(anzahlKacheln);
	for(unsigned int i = 0; i<downl.size(); i++)		//die 9 Downloader (einer für jede
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
	for(int i=0; i<anzahlKacheln; i++)
		{
		connect(downl[i], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));
		}

	for(int i=0;i<seitenlaenge;i++)
		{
		for(int j=0;j<seitenlaenge;j++)
			{
			kacheln[(i*seitenlaenge)+j]=widget->getView()->scene()->addPixmap(QPixmap(256,256));
			kacheln[(i*seitenlaenge)+j]->setOffset(QPoint((j-seitenlaenge/2)*256,(i-seitenlaenge/2)*256));
			}
		}

	setzeKarteNeu(z, x, y);
	}


void MainWindow::setzeKarteNeu(int z, int x, int y)
	{
	int xDazu=-1*sichtbaresFeld/2;
	int yDazu=-1*sichtbaresFeld/2;
	for(int i=sichtbaresFeld;i<2*sichtbaresFeld;i++)
		{
		for(int j=sichtbaresFeld;j<2*sichtbaresFeld;j++)
			{
			downl[perm[(i*seitenlaenge)+j]]->ladeKachel(z,x+xDazu,y+yDazu,perm[(i*seitenlaenge)+j]);
			xDazu++;
			if(xDazu>sichtbaresFeld/2)
				{
				xDazu=-1*sichtbaresFeld/2;
				yDazu++;
				}
			}
		}
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
	kacheln[index]->setPixmap(meinePix);
	}


void MainWindow::geheNorden()
	{
	if(ykoord>1)
		{
		ykoord=ykoord-1;

		for(int i=anzahlKacheln-seitenlaenge;i<anzahlKacheln;i++)
			{
			kacheln[perm[i]]->moveBy(0,seitenlaenge*(-256));
			kacheln[perm[i]]->setPixmap(QPixmap(256,256));

			perm[i+seitenlaenge]=perm[i];
			}

		for(int i=anzahlKacheln-1;i>=seitenlaenge;i--)
			{
			perm[i]=perm[i-seitenlaenge];
			}

		for(int i=0;i<seitenlaenge;i++)
			{
			perm[i]=perm[anzahlKacheln+i];
			}

		int ersteStelleInZeile=((sichtbaresFeld)*seitenlaenge);
		int xDazu=-1*sichtbaresFeld/2;
		for(int i=sichtbaresFeld;i<2*sichtbaresFeld;i++)
			{
			downl[perm[ersteStelleInZeile+i]]->ladeKachel(zoom,xkoord+xDazu,ykoord-(sichtbaresFeld/2),perm[ersteStelleInZeile+i]);
			xDazu++;
			}
		}
	}


void MainWindow::geheSueden()
	{
	if(ykoord<(pow(2,zoom)-3))
		{
		ykoord=ykoord+1;

		for(int i=0;i<seitenlaenge;i++)
			{
			kacheln[perm[i]]->moveBy(0,seitenlaenge*256);
			kacheln[perm[i]]->setPixmap(QPixmap(256,256));

			perm[anzahlKacheln+i]=perm[i];
			}

		for(int i=0;i<anzahlKacheln;i++)
			{
			perm[i]=perm[i+seitenlaenge];
			}

		int ersteStelleInZeile=(((2*sichtbaresFeld)-1)*seitenlaenge);
		int xDazu=-1*sichtbaresFeld/2;
		for(int i=sichtbaresFeld;i<2*sichtbaresFeld;i++)
			{
			downl[perm[ersteStelleInZeile+i]]->ladeKachel(zoom,xkoord+xDazu,ykoord+(sichtbaresFeld/2),perm[ersteStelleInZeile+i]);
			xDazu++;
			}
		}
	}


void MainWindow::geheOsten()
	{
	xkoord=xkoord+1;

	for(int i=0;i<seitenlaenge;i++)
		{
		kacheln[perm[i*seitenlaenge]]->moveBy(seitenlaenge*256,0);
		kacheln[perm[i*seitenlaenge]]->setPixmap(QPixmap(256,256));

		perm[anzahlKacheln+i]=perm[i*seitenlaenge];
		}

	for(int j=0;j<seitenlaenge-1;j++)
		{
		for(int i=0;i<seitenlaenge;i++)
			{
			perm[i*seitenlaenge+j]=perm[i*seitenlaenge+j+1];
			}
		}

	for(int i=1;i<=seitenlaenge;i++)
		{
		perm[i*seitenlaenge-1]=perm[anzahlKacheln+i-1];
		}

	int ersteStelleInZeile=((sichtbaresFeld)*seitenlaenge)+2*sichtbaresFeld-1;
	for(int i=0;i<sichtbaresFeld;i++)
		{
		downl[perm[ersteStelleInZeile+i*seitenlaenge]]->ladeKachel(zoom,xkoord+(sichtbaresFeld/2),ykoord+(i-sichtbaresFeld/2),perm[ersteStelleInZeile+i*seitenlaenge]);
		}
	}


void MainWindow::geheWesten()
	{
	xkoord=xkoord-1;

	for(int i=1;i<=seitenlaenge;i++)
		{
		std::cout<<i*seitenlaenge-1<<std::endl;
		kacheln[perm[i*seitenlaenge-1]]->moveBy(seitenlaenge*(-256),0);
		kacheln[perm[i*seitenlaenge-1]]->setPixmap(QPixmap(256,256));

		perm[anzahlKacheln+i-1]=perm[i*seitenlaenge-1];
		}

	for(int j=seitenlaenge-1;j>0;j--)
		{
		for(int i=0;i<seitenlaenge;i++)
			{
			perm[i*seitenlaenge+j]=perm[i*seitenlaenge+j-1];
			}
		}

	for(int i=0;i<seitenlaenge;i++)
		{
		perm[i*seitenlaenge]=perm[anzahlKacheln+i];
		}

	int ersteStelleInZeile=((sichtbaresFeld)*seitenlaenge)+sichtbaresFeld;
	for(int i=0;i<sichtbaresFeld;i++)
		{
		downl[perm[ersteStelleInZeile+i*seitenlaenge]]->ladeKachel(zoom,xkoord-(sichtbaresFeld/2),ykoord+(i-sichtbaresFeld/2),perm[ersteStelleInZeile+i*seitenlaenge]);
		}
	}


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
	double lo=tilex2long(xkoord,zoom);
	lo=lo+((tilex2long(xkoord+1,zoom)-lo)/256)*punkt.x();
	double la=tiley2lat(ykoord,zoom);
	la=la+((tiley2lat(ykoord+1,zoom)-la)/256)*punkt.y();
	punktvkt.push_back(widget->koordSetzen(QPointF(lo,la),xkoord,ykoord,zoom));
	}


void MainWindow::bewegungTesten(bool jaOderNein, QPointF punkt)
	{
	if(jaOderNein)
		{
		mausDrag=mausDrag+punkt;
		qDebug()<<"Geklickt\n"<<mausDrag;
		}
	else
		{
		mausDrag=mausDrag-punkt;
		qDebug()<<"Losgelassen\n"<<mausDrag;

		if(mausDrag.x()<-256 || mausDrag.x()>256 || mausDrag.y()<-256 || mausDrag.y()>256)
			{
			while(mausDrag.x()<-256 || mausDrag.x()>256)
				{
				if(mausDrag.x()<0)
					{
					geheWesten();
					mausDrag.setX(mausDrag.x()+256);
					}
				else
					{
					geheOsten();
					mausDrag.setX(mausDrag.x()-256);
					}
				}
			while(mausDrag.y()<-256 || mausDrag.y()>256)
				{
				if(mausDrag.y()<0)
					{
					geheNorden();
					mausDrag.setY(mausDrag.y()+256);
					}
				else
					{
					geheSueden();
					mausDrag.setY(mausDrag.y()-256);
					}
				}
			}
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


