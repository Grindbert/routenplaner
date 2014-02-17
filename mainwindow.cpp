#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	{
	//Fenster anlegen:
	setAttribute(Qt::WA_DeleteOnClose);
	setGeometry(100, 100, 800, 600);	//Größe und Ort des "aufpoppens" festlegen
	setWindowTitle("Nicht tomtom, auch nicht HansHans, sondern BastiBasti ;-)");

	//Widgets anlegen und im Fenster zentrieren:
	widget = new Widgets(this);	//Widgetcontainer anlegen
	setCentralWidget(widget);

	hilfefenster = new Hilfefenster(this);
	wartefenster = new Wartefenster(this);

	//sollte selbsterklärend sein:
	menuAnlegen();
	statuszeileAnlegen();
	rechtsklickmenuAnlegen();

	//Vektor, der die Wegvektoren speichert, die der Dijkstra zurückgibt
	vektorFurWegvektoren = new std::vector<std::vector<int> >;

	//Punkt, auf den die Karte beim Starten gesetzt wird, definieren:
	zoom=12;
	xkoord=2200;
	ykoord=1313;

	startpunktExistiert=false;
	zielpunktExistiert=false;
	dateiGeladen=false;

	//Maus-tracking einschalten, damit die Koordinaten der Maus live im Fenster
	//angezeigt werden können:
	widget->getView()->setMouseTracking(true);

	//Buttons und Zeug aus dem Widgetcontainer mit Funktionen connecten:
	//Richtungs- und Zoombuttons connecten:
	connect(widget->getButton(0), SIGNAL(clicked()), this, SLOT(geheNordenButton()));
	connect(widget->getButton(1), SIGNAL(clicked()), this, SLOT(geheSuedenButton()));
	connect(widget->getButton(2), SIGNAL(clicked()), this, SLOT(geheOstenButton()));
	connect(widget->getButton(3), SIGNAL(clicked()), this, SLOT(geheWestenButton()));
	connect(widget->getButton(4), SIGNAL(clicked()), this, SLOT(zoomInButton()));
	connect(widget->getButton(5), SIGNAL(clicked()), this, SLOT(zoomOut/*Button*/()));

	//Zoom mit dem Mausrad connecten:
	connect(widget->getView()->scene(), SIGNAL(zoomInSignal(QPointF)), this, SLOT(zoomIn(QPointF)));
	connect(widget->getView()->scene(), SIGNAL(zoomOutSignal(QPointF)), this, SLOT(zoomOut(/*QPointF*/)));

	//Menü der rechten Maustaste connecten:
	connect(widget->getView()->scene(), SIGNAL(rechteMaustaste(QPointF)), this, SLOT(rechteMaustasteGeklickt(QPointF)));

	//linke Maustaste: Aktionen zum Karte ziehen (bei klick und wieder loslassen)
	connect(widget->getView()->scene(), SIGNAL(linkeMaustasteGedruckt(bool,QPointF)), this, SLOT(bewegungTesten(bool,QPointF)));
	connect(widget->getView()->scene(), SIGNAL(linkeMaustasteLoslassen(bool,QPointF)), this, SLOT(bewegungTesten(bool,QPointF)));

	//Längen- und Breitengrade des Mauszeigers immer wieder aktualisieren:
	connect(widget->getView()->scene(), SIGNAL(mausBewegt(QPointF)), this, SLOT(berechneKoordinaten(QPointF)));

	//Karte wieder in View zentrieren, wenn die View die Größe geändert hat:
	connect(widget->getView(), SIGNAL(resized()), this, SLOT(karteZentrieren()));

	connect(widget->getButton(6), SIGNAL(clicked()), this, SLOT(wegBerechnen()));

	kartenrasterAnlegen(7);
	}


MainWindow::~MainWindow()
	{}


//===================================================================
//Funktionen um Menüs und Statuszeile anzulegen:
//===================================================================
void MainWindow::kartenrasterAnlegen(int eingabe)
	{
	//Punkte für die leichtere Naviation in der Szene festlegen:
	mausDrag=QPointF(0,0);		//prüft, wie sich die Maus bewegt hat, um bei
					//entsprechenden Änderungen Kacheln nachzuladen
	korrigierteSzene=QPoint(0,0);	//merkt sich bei Bewegungen die obere
					//linke Ecke der mittleren Kachel, um besser in der Szene
					//navigieren zu können

	//Feldgröße festlegen und merken (sehr nützlich zum navigieren im Kachelgitter):
	sichtbaresFeld=eingabe;	//Kachenl, die in der View sichtbar sind
	seitenlaenge=3*sichtbaresFeld;	//Seitenlänge des gesamten Kachelgitters
	anzahlKacheln=seitenlaenge*seitenlaenge;	//Gesamtzahl Kacheln, nützlich
					//für das resizen der ganzen Vektoren

	//alle Vektoren, die für die Kacheln sind, auf entsprechende Länge setzen:
	kacheln.resize(anzahlKacheln);
	perm.resize(anzahlKacheln+seitenlaenge);	//das "+seitenlaenge" ist, damit
					//Platz ist, um sich Nummern beim Bewegen in eine Himmelsrichtung
					//zu merken und zwischenzuspeichern
	for(unsigned int i=0;i<perm.size();i++)
		{
		perm[i]=i;
		}

	downl.resize(anzahlKacheln);
	for(unsigned int i = 0; i<downl.size(); i++)		//die 9 Downloader (einer für jede
		{							//Kachel einen) anlegen
		downl[i]=new Downloader;
		}

	//Karte vom Startpunkt laden:
	starteKarte();
	}


void MainWindow::menuAnlegen()
	{
	//Datei-Menü:
	menuDatei = menuBar()->addMenu(tr("&Datei"));

	//Graph-laden-Button:
	QAction *ladeGraph = new QAction(tr("&Graph laden"), this);
	ladeGraph->setShortcut(tr("Ctrl+L"));
	ladeGraph->setStatusTip(tr("lies Graph von Textdatei ein"));
	menuDatei->addAction(ladeGraph);
	connect(ladeGraph, SIGNAL(triggered()), this, SLOT(graphLaden()));

	//Einstellungen:
	QAction *einstellung = new QAction(tr("&Einstellungen"), this);
	einstellung->setShortcut(tr("Ctrl+E"));
	einstellung->setStatusTip(tr("stellt die Anzahl der zu ladenden Kacheln ein"));
	menuDatei->addAction(einstellung);
	connect(einstellung, SIGNAL(triggered()), this, SLOT(optionen()));

	//Beenden-Button:
	QAction *beenden = new QAction(tr("&Beenden"), this);
	beenden->setShortcut(tr("Ctrl+T"));
	beenden->setStatusTip(tr("Programm beenden"));
	menuDatei->addAction(beenden);
	// qApp ist globale Variable der Applikation
	connect(beenden, SIGNAL(triggered()), qApp, SLOT(quit()));


	//Menü für Funktionen, die die Routenplanerfunktion betreffen:
	menuRoute=menuBar()->addMenu(tr("&Route"));

	//Aktion, um Routenberechnung zu starten und fertige Route einzuzeichnen:
	QAction *routeBerechnen =new QAction(tr("&Route berechnen (Gogogo!!!)"), this);
	routeBerechnen->setShortcut(tr("Ctrl+G"));
	routeBerechnen->setStatusTip(tr("starte die Routenberechnung"));
	menuRoute->addAction(routeBerechnen);
	connect(routeBerechnen, SIGNAL(triggered()), this, SLOT(wegBerechnen()));

	//alle eingezeichneten Routen aus der Karte wieder löschen:
	QAction *routenWeg=new QAction(tr("&eingezeichnete Routen löschen"), this);
	routenWeg->setShortcut(tr("Ctrl+B"));
	routenWeg->setStatusTip(tr("löscht die eingezeichnete(n) Route(n)"));
	menuRoute->addAction(routenWeg);
	connect(routenWeg, SIGNAL(triggered()), this, SLOT(routenLoeschen()));


	//Hilfemenü:
	menuHilfe=menuBar()->addMenu(tr("&Hilfe"));

	QAction *hilfeAnzeigen=new QAction(tr("&Hilfe anzeigen"), this);
	hilfeAnzeigen->setShortcut(tr("Ctrl+H"));
	hilfeAnzeigen->setStatusTip(tr("zeigt die Hilfe zum Programm an"));
	menuHilfe->addAction(hilfeAnzeigen);
	connect(hilfeAnzeigen, SIGNAL(triggered()), hilfefenster, SLOT(show()));
	}


//erstellt die Statuszeile am unteren Rand des Hauptfensters:
void MainWindow::statuszeileAnlegen()
	{
	statusLabel = new QLabel("Solange du das hier noch lesen kannst, ist alles in Ordnung! ;-)");
	statusBar()->addWidget(statusLabel);
	}


//erstellt das Menü, das erscheint, wenn man einen Rechtsklick macht:
void MainWindow::rechtsklickmenuAnlegen()
	{
	//Startpunkt der gewünschten Route festlegen:
	QAction *startpkt = new QAction(tr("&von hier starten"), this);
	startpkt->setStatusTip(tr("setzt den Startpunkt für die Route hierher"));
	rechtsklickmenu.addAction(startpkt);
	connect(startpkt, SIGNAL(triggered()), this, SLOT(startFestlegen()));

	//Zielpunkt der gewünschten Route festlegen:
	QAction *zielpkt = new QAction(tr("&nach hier wollen"), this);
	zielpkt->setStatusTip(tr("setzt den Startpunkt für die Route hierher"));
	rechtsklickmenu.addAction(zielpkt);
	connect(zielpkt, SIGNAL(triggered()), this, SLOT(zielFestlegen()));
	}


//===================================================================
//Kartenfunktionen: initialisieren, neu setzen, Pixmaps hinzufügen:
//===================================================================

//soll die Karte initialisieren:
void MainWindow::starteKarte()
	{
	//jeder Downloader wird so connectet, dass die Kacheln nach dem Runterladen gleich
	//in die Szene gesetzt werden:
	for(int i=0; i<anzahlKacheln; i++)
		{
		connect(downl[i], SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(pixmapAdden(QPixmap, int)));
		}

	//eine weiße "Standard"-Kachel wird runtergeladen, die überall hingesetzt wird,
	//wo noch keine Kachel aus dem Internet geladen wurde:
	//(die Kachel stammt aus der Antarktis, daher die Koordinaten 8,200,255)
	Downloader *weisseKachelDownl=new Downloader();
	connect(weisseKachelDownl, SIGNAL(gedownloaded(QPixmap, int)), this, SLOT(starteKarteFortsetzung(QPixmap)));
	weisseKachelDownl->ladeKachel(8,200,255,0);	//die 0 wird am Ende nur angegeben,
			//weil die Funktion immer gleich die Position haben will, wo die Kachel
			//nach dem Download hin soll. Die weiße Kachel soll aber nicht direkt in
			//die Szene, sondern gespeichert werden.

	//wenn die weiße Kachel fertig runtergeladen wurde, wird mit der Funktion
	//"starteKarteFortsetzung" weitergemacht, die vom connect die Pixmap der
	//weißen Kachel übergeben bekommt.
	}


void MainWindow::starteKarteFortsetzung(QPixmap pixmap)
	{
	weisseKachel=pixmap;	//speichere die weiße Kachel, um sie später immer
			//wieder verwenden und nicht immer wieder herunterzuladen zu müssen.

	//besetze zunächst alle Kacheln im Kachelgitter mit der weißen Standardkachel:
	//(i sind hier die Zeilen, j die Spalten, wie bei einer Matrix)
	for(int i=0;i<seitenlaenge;i++)
		{
		for(int j=0;j<seitenlaenge;j++)
			{
			kacheln[(i*seitenlaenge)+j]=widget->getView()->scene()->addPixmap(weisseKachel);
			kacheln[(i*seitenlaenge)+j]->setOffset(QPoint((j-seitenlaenge/2)*256,(i-seitenlaenge/2)*256));
			}
		}

	karteZentrieren();

	//rufe diese Funktion auf, um alle in der GraphicsView sichtbaren PixmapItems mit
	//den der Zoomstufe und Koordinaten entsprechenden Kacheln zu besetzen:
	setzeKarteNeu(zoom, xkoord, ykoord);
	}


//lädt alle Kacheln um die zentrale Kachel mit den Koordinaten x und y herunter
//und setzt sie an die entsprechende Stelle im Kachelgitter:
void MainWindow::setzeKarteNeu(int z, int x, int y)
	{
	//Zähler, um das sichtbare Feld an Kacheln durchzulaufen:
	int xDazu=-1*sichtbaresFeld/2;
	int yDazu=-1*sichtbaresFeld/2;

	//laufe Kacheln im sichtbaren Feld ab:
	for(int i=sichtbaresFeld;i<2*sichtbaresFeld;i++)
		{
		for(int j=sichtbaresFeld;j<2*sichtbaresFeld;j++)
			{
			//lade die entsprechende Kachel runter:
			downl[perm[(i*seitenlaenge)+j]]->ladeKachel(z,x+xDazu,y+yDazu,perm[(i*seitenlaenge)+j]);
			xDazu++;	//gehe in der Zeile eine Position weiter
			if(xDazu>sichtbaresFeld/2)	//wenn du am Ende der Zeile bist:
				{
				xDazu=-1*sichtbaresFeld/2;	//gehe in der x-Koordinate wieder zum Anfang einer Zeile
				yDazu++;	//springe in die nächste Zeile
				}
			}
		}
	}


//zentriert die GraphicsView wieder auf die Mitte der zentralen Kachel:
//(der Punkt "korrigierteSzene" enthält ja die Pixelkoordinaten der zentralen
//Kachel in der Szene. Es soll also auf die Mitte der zentralen Kachel zentriert
//werden, daher werden in der x- und der y-Koordinate noch 128 Pixel dazu
//addiert (zur Erinnerung: die Kacheln haben eine Seitenlänge von 256 Pixeln))
void MainWindow::karteZentrieren()
	{
	widget->getView()->centerOn(QPointF(korrigierteSzene.x()+128,korrigierteSzene.y()+128));
	}


//setzt die Pixmap "meinePix" an die Stelle "index" im Kachelgitter:
void MainWindow::pixmapAdden(QPixmap meinePix, int index)
	{
	kacheln[index]->setPixmap(meinePix);
	}


//====================================================================
//Bewegungsfunktionen für die 4 Himmelsrichtungen:
//====================================================================
void MainWindow::geheNorden()
	{
	if(ykoord>1)
		{
		//Aktualisieren der y-Koordinate "ykoord" der zentralen Kachel
		//entsprechend der Bewegungsrichtung:
		//("korrigierteSzene" wird auch aktualisiert (die hat ja die
		//Szenenkoordinate der linken oberen Ecke der zentralen Kachel
		//gespeichert))
		ykoord=ykoord-1;
		korrigierteSzene.setY(korrigierteSzene.y()-256);

		//PixmapItems, die weiter von der zentralen Kachel weggerückt sind,
		//werden wieder an die andere Seite des Kachelgitters verschoben
		//und mit der weißen Standardkachel versehen:
		for(int i=anzahlKacheln-seitenlaenge;i<anzahlKacheln;i++)
			{
			kacheln[perm[i]]->moveBy(0,seitenlaenge*(-256));
			kacheln[perm[i]]->setPixmap(weisseKachel);

			//Werte von "perm" der verschobenen Kacheln zwischenspeichern:
			perm[i+seitenlaenge]=perm[i];
			}

		//"perm" aktualisieren:
		for(int i=anzahlKacheln-1;i>=seitenlaenge;i--)
			{
			perm[i]=perm[i-seitenlaenge];
			}

		//zwischengespeicherte Werte werden an die entsprechende Stelle kopiert:
		for(int i=0;i<seitenlaenge;i++)
			{
			perm[i]=perm[anzahlKacheln+i];
			}

		//neue Kacheln nachladen:
		int ersteStelleInZeile=((sichtbaresFeld)*seitenlaenge);
		int xDazu=-1*sichtbaresFeld/2;
		for(int i=sichtbaresFeld;i<2*sichtbaresFeld;i++)
			{
			downl[perm[ersteStelleInZeile+i]]->ladeKachel(zoom,xkoord+xDazu,ykoord-(sichtbaresFeld/2),perm[ersteStelleInZeile+i]);
			xDazu++;
			}
		}
	else
		{
		karteZentrieren();
		}
	}


void MainWindow::geheSueden()
	{
	if(ykoord<pow(2,zoom)-1)
		{
		ykoord=ykoord+1;
		korrigierteSzene.setY(korrigierteSzene.y()+256);

		for(int i=0;i<seitenlaenge;i++)
			{
			kacheln[perm[i]]->moveBy(0,seitenlaenge*256);
			kacheln[perm[i]]->setPixmap(weisseKachel);

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
	else
		{
		karteZentrieren();
		}
	}


void MainWindow::geheOsten()
	{
	xkoord=xkoord+1;
	korrigierteSzene.setX(korrigierteSzene.x()+256);

	for(int i=0;i<seitenlaenge;i++)
		{
		kacheln[perm[i*seitenlaenge]]->moveBy(seitenlaenge*256,0);
		kacheln[perm[i*seitenlaenge]]->setPixmap(weisseKachel);

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
	korrigierteSzene.setX(korrigierteSzene.x()-256);

	for(int i=1;i<=seitenlaenge;i++)
		{
		kacheln[perm[i*seitenlaenge-1]]->moveBy(seitenlaenge*(-256),0);
		kacheln[perm[i*seitenlaenge-1]]->setPixmap(weisseKachel);

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


//Funktionalitäten der Buttons:
//die Buttons benutzen die Funktionen, die auch von der Bewegung mit der Maus
//genutzt werden. Danach muss aber wieder auf die Mitte zentriert werden, da
//ja beim einfachen Aufrufen der Funktionen ohne das Ziehen mit der Maus die
//Szene nicht bewegt wird.
void MainWindow::geheNordenButton()
	{
	geheNorden();
	karteZentrieren();
	}


void MainWindow::geheSuedenButton()
	{
	geheSueden();
	karteZentrieren();
	}


void MainWindow::geheOstenButton()
	{
	geheOsten();
	karteZentrieren();
	}


void MainWindow::geheWestenButton()
	{
	geheWesten();
	karteZentrieren();
	}


//====================================================================
//Zoomfunktionen:
//====================================================================
void MainWindow::zoomIn(QPointF punkt)
	{
	if(zoom<=18)	//Für eine höhere Zoomstufe als 18 sind keine Kacheln mehr
		{			//verfügbar, daher macht es keinen Sinn, weiter reinzoomen zu wollen.
		//berechne die Längen- und Breitengerade der aktuellen Mausposition:
		double lo=tilex2long(xkoord,zoom);
		lo=lo+((tilex2long(xkoord+1,zoom)-lo)/256)*(punkt.x()-korrigierteSzene.x());
		double la=tiley2lat(ykoord,zoom);
		la=la+((tiley2lat(ykoord+1,zoom)-la)/256)*(punkt.y()-korrigierteSzene.y());

		//aktualisiere Zoomstufe und Nummern der zentralen Kachel:
		//(als neue zentrale Kachel wird die gewählt, auf die der Mauszeiger gerade
		//zum Zeitpunkt des Zoomens gezeigt hat)
		zoom=zoom+1;
		xkoord=(int)floor(long2tile(lo,zoom));
		ykoord=(int)floor(lat2tile(la,zoom));

		karteZentrieren();

		//da gerade gezoomt wird, sind die "alten" Kacheln in der falschen
		//Zoomstufe nicht mehr nützlich, daher werden alle Kacheln wieder auf die
		//weiße Standardkachel gesetzt:
		for(int i=0;i<seitenlaenge;i++)
			{
			for(int j=0;j<seitenlaenge;j++)
				{
				kacheln[perm[i*seitenlaenge+j]]->setPixmap(weisseKachel);
				}
			}

		//anschließend werden alle Kacheln im sichtbaren Feld mit der neuen
		//Zoomstufe geladen:
		setzeKarteNeu(zoom, xkoord, ykoord);

		routenOptischEntfernen();	//eingezeichnete Routen werden aus der Szene entfernt
		routenNeuEinzeichnen();		//und in der neuen Zoomstufe wieder eingezeichnet
		}
	}


void MainWindow::zoomOut(/*QPointF punkt*/)
	{
	if(zoom>2)	//wenn die Zoomstufe zu klein ist, zoome nicht mehr
		{
		//aktualisieren der Zommstufe und x- und y-Nummer:
		zoom=zoom-1;
		xkoord=xkoord/2;
		ykoord=ykoord/2;

		karteZentrieren();

		//wie beim zoomIn alle Kacheln wieder auf die weiße Standardkachel setzen:
		for(int i=0;i<seitenlaenge;i++)
			{
			for(int j=0;j<seitenlaenge;j++)
				{
				kacheln[perm[i*seitenlaenge+j]]->setPixmap(weisseKachel);
				}
			}

		//Kacheln in neuer Zoomstufe wieder laden:
		setzeKarteNeu(zoom, xkoord, ykoord);

		routenOptischEntfernen();	//Routen entfernen
		routenNeuEinzeichnen();		//um sie in der neuen Zoomstufe wieder einzuzeichnen
		}
	}


//macht genau das gleiche wie "zoomIn", aber da diese Funktion über den Button
//aktiviert werden soll, macht es keinen Sinn, auf die Position des Mauszeigers
//zu zoomen. Daher werden xkoord und ykoord anders aktualisiert:
//(ansonsten aber die gleiche Funktion wie "zoomIn")
void MainWindow::zoomInButton()
	{
	if(zoom<=18)
		{
		zoom=zoom+1;
		xkoord=2*xkoord;
		ykoord=2*ykoord;

		karteZentrieren();

		for(int i=0;i<seitenlaenge;i++)
			{
			for(int j=0;j<seitenlaenge;j++)
				{
				kacheln[perm[i*seitenlaenge+j]]->setPixmap(weisseKachel);
				}
			}

		setzeKarteNeu(zoom, xkoord, ykoord);

		routenOptischEntfernen();
		routenNeuEinzeichnen();
		}
	}


/*void MainWindow::zoomOutButton()
	{
	zoomOut(QPointF());
	}*/


//===================================================================
//Spaß mit der Maus:
//===================================================================

//wird aufgerufen, wenn ein Rechtsklick in die Szene erfolgt:
void MainWindow::rechteMaustasteGeklickt(QPointF punkt)
	{
	rechtsklickPunkt=punkt;	//speichere den Punkt, wo rechtsgeklickt wurde
	rechtsklickmenu.move(QCursor::pos());	//verschiebe das Menü zu dem Punkt
								//auf dem Bildschirm, wo rechtsgeklickt wurde
	rechtsklickmenu.show();	//zeige das Menü
	}


//diese Funktion wird immer ausgelöst, wenn die Maus bewegt wurde
//(mouseMoveEvent in "meineSzene.h" bzw. "meineSzene.cpp")
void MainWindow::berechneKoordinaten(QPointF punkt)
	{
	//berechnet den Längen- und Breitengrad:
	double lo=tilex2long(xkoord,zoom);
	lo=lo+((tilex2long(xkoord+1,zoom)-lo)/256)*(punkt.x()-korrigierteSzene.x());
	double la=tiley2lat(ykoord,zoom);
	la=la+((tiley2lat(ykoord+1,zoom)-la)/256)*(punkt.y()-korrigierteSzene.y());

	//setze die Mauskoordinaten auf die eben berechneten:
	widget->mausKoordSetzen(QPointF(lo,la));
	}


//Wird immer aufgerufen, wenn etwas mit der linken Maustaste gemacht wurde,
//also wenn die Karte irgendwie bewegt wurde:
void MainWindow::bewegungTesten(bool geklickt, QPointF punkt)
	{
	if(geklickt)	//wenn die linke Maustaste geklickt wurde, wird der Punkt,
					//an dem das passiert ist, auf einen "Speicherpunkt" addiert
		{
		mausDrag=mausDrag+punkt;
		}

	else	//wenn die linke Maustaste losgelassen wurde, wird der Punkt, an dem
			//losgelassen wurde, wieder vom "Speicherpunkt" abgezogen. Damit wurde
			//effektiv dann die Bewegungsdistanz auf den Speicherpunkt addiert.
			//(beim Klicken wurde der aktuelle Punkt addiert, beim Loslassen wurde
			//der aktuelle Punkt wieder abgezogen --> die Differenz aus Punkt, wo
			//geklickt wurde und Punkt, wo losgelassen wurde, wurde letzendlich
			//auf den "Speicherpunkt" addiert)
		{
		mausDrag=mausDrag-punkt;

		//Wenn der "Speicherpunkt" in der x- oder y-Koordinate größer ist als 256,
		//also die Seitenlänge der Kacheln (oder kleiner als -256), wird eine Aktion
		//"gehe[Himmelsrichtung]" ausgeführt, je nach dem, welche Koordinate wie
		//groß ist.
		if(mausDrag.x()<-256 || mausDrag.x()>256 || mausDrag.y()<-256 || mausDrag.y()>256)
			{
			//so lange in der x-Koordinate noch eine größere Abweichung als eine
			//Kachelkantenlänge besteht, muss "gehe[Himmelsrichtung]" aufgerufen
			while(mausDrag.x()<-256 || mausDrag.x()>256)
				{
				//wenn x kleiner als 0 ist, muss Richtung Westen gegangen werden.
				//Jedes mal, wenn die Funktion aufgerufen wurde, wird 256 auf die
				//x-Koordinate addiert, da beim Funktionsaufruf eine Kachelreihe
				//verschoben wurde.
				if(mausDrag.x()<0)
					{
					geheWesten();
					mausDrag.setX(mausDrag.x()+256);
					}

				//Wenn die x-Koordinate größer ist als 256, wird nach Osten gegangen
				//und 256 von der Koordinate abgezogen.
				else
					{
					geheOsten();
					mausDrag.setX(mausDrag.x()-256);
					}
				}

			//genau wie bei der x-Koordinate muss überprüft werden, ob eine Bewegung
			//notwendig ist. (analog zur x-Koordinate)
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


//=====================================================================
//Graph: von Datei laden und Dijkstra
//=====================================================================

//Liest eine Graph-Datei ein, damit die Informationen im Routenplaner genutzt werden
//können.
void MainWindow::graphLaden()
	{
	//Öffnet ein Kommunikationsfenster, in dem der Nutzer nach der gewünschten
	//Datei browsen kann. Für die Datei, die der Nutzer auswählt, wird der
	//Dateipfad zurückgegeben und in "infile" aufgefangen:
	QString infile = QFileDialog::getOpenFileName(this, tr("Open Image"), "~", tr("All Files (*)"));

	//QString infile="/media/grindbert/Aeneon/Basti_C++/testdaten/mecklenburg-vorpommern-latest.gtxt";
	//qDebug()<<infile;
	//emit blubs();

	//öffne InputFile:
	std::ifstream meineDatei(infile.toStdString().c_str());

	//Wenn die Datei aus irgendwelchen Gründen nicht geöffnet werden konnte, soll
	//eine Fehlermeldung in die Statuszeile geprintet werden und das Einlesen
	//abbrechen.
	if(!meineDatei)
		{
		statusLabel->setText("Fehler: Konnte Datei nicht öffnen! Einlesen wurde abgebrochen.");
		}

	else
		{
		wartefenster->show();

		//zum Speichern von Knoten- und Kantenzahl:
		unsigned int knotenzahl=0;
		unsigned int kantenzahl=0;

		//zum Einlesen der Knoten:
		float x;
		float y;

		//zum einlesen der Kanten:
		unsigned int start=0;	//Index vom Startknoten
		unsigned int ziel=0;	//Index vom Zielknoten
		float laenge;

		//Einlesen:
		meineDatei>>knotenzahl;

		//Knotenvektor mit [knotenzahl] einträgen anlegen:
		knoten = new std::vector<Knoten>(knotenzahl);

		meineDatei>>kantenzahl;

		wartefenster->setText("Knoten werden geladen...");

		//Knoten einlesen:
		for(unsigned int i = 0; i<knotenzahl; i++)	//lies [Knotenzahl] Zeilen der
							//Datei aus und speichere sie als Knoten ab
			{
			wartefenster->setStatusBalken((i*100)/knotenzahl);
			meineDatei>>x>>y;	//Koordinaten auslesen
			(*knoten)[i].setzeKoord(x,y,i);	//Koordinaten und Knotennummer in den
								//Vektor speichern
			}

		wartefenster->setText("Kanten werden geladen...");

		//Kanten einlesen:
		for(unsigned int i = 0; i<kantenzahl; i++)	//lies [Kantenzahl] Zeilen der
							//Datei und speichere sie als Kanten in die Knoten
			{
			wartefenster->setStatusBalken((i*100)/kantenzahl);
			meineDatei>>start>>ziel>>laenge;	//Parameter auslesen
			(*knoten)[start].kanteHinzufuegen(&((*knoten)[ziel]),laenge);	//Kante
							//in die Liste der ausgehenden Kanten des Startknotens
							//schreiben
			}

		//Würde alle Knoteninformationen in die Standardausgabe printen
		//(auskommentiert, weil printen für große Dateien sehr lange dauert...
		//und natürlich auch, weil es nicht gebraucht wird^^)
		/*for(int i = 0; i<(*knoten).size(); i++)
			{
			(*knoten)[i].print();
			}*/

		//merke dir, ob schon eine Graphdatei geladen wurde:
		dateiGeladen=true;

		//wartefenster->setText(" ");
		//wartefenster->hide();
		}
	}


//Der Wegfindungsalgorithmus:
void MainWindow::wegBerechnen()
	{
	if(!dateiGeladen)	//Wenn noch kein Graph eingelesen wurde, macht die Wegfindung
						//nicht viel Sinn...
		{
		statusLabel->setText("Es wurde noch kein Graph geladen. Daher ist auch keine Berechnung möglich! :-(");
		}

	else if(!startpunktExistiert)	//wenn noch kein Startpunkt übergeben wurde,
						//macht die Wegberechnung wiederum wenig Sinn...
		{
		statusLabel->setText("Es wurde kein Startpunkt angegeben! Keine Wegberechnung möglich :-(");
		}

	else if(!zielpunktExistiert)	//ohne Zielpunkt genauso...
		{
		statusLabel->setText("Es wurde kein Zielpunkt angegeben! Keine Wegberechnung möglich :-(");
		}

	//wenn Start- und Zielpunkt vorhanden sind und eine Graphdatei eingelesen wurde,
	//kann der Algorithmus starten:
	if(startpunktExistiert && zielpunktExistiert && dateiGeladen)
		{
		bool *gibtWeg = new bool(false);	//um zu prüfen, ob ein Weg zwischen Start und Ziel existiert
		float *abstand = new float();		//für die Länge der Route

		//"Wegfindung" ist der Wegfindungsalgorithmus. Die Funktion gibt einen
		//Vektor mit den Nummern der Knoten wieder, die den besten Weg definieren.
		//Dieser Vektor wird in einen Vektor getan, der alle Routen, die eingezeichnet
		//wurden, speichern soll, um sie z.B. beim Zoomen wieder in der richtigen
		//Zoomstufe einzeichnen zu können.
		vektorFurWegvektoren->push_back(Wegfindung(knoten, startpunkt, zielpunkt, gibtWeg, abstand));

		//Wenn es einen Weg gibt, zeichne ihn in die Karte:
		if(*gibtWeg)
			{
			statusLabel->setText("Solange du das hier noch lesen kannst, ist alles in Ordnung! ;-)");

			for(int i = ((vektorFurWegvektoren->back()).size())-2; i>=0; i--)
				{
				int x1 = (long2tile((*knoten)[(vektorFurWegvektoren->back())[i]].x,zoom)-xkoord)*256+korrigierteSzene.x();
				int y1 = (lat2tile((*knoten)[(vektorFurWegvektoren->back())[i]].y,zoom)-ykoord)*256+korrigierteSzene.y();
				int x2 = (long2tile((*knoten)[(vektorFurWegvektoren->back())[i+1]].x,zoom)-xkoord)*256+korrigierteSzene.x();
				int y2 = (lat2tile((*knoten)[(vektorFurWegvektoren->back())[i+1]].y,zoom)-ykoord)*256+korrigierteSzene.y();
				widget->getView()->scene()->addLine(x1,y1,x2,y2,QPen(Qt::blue, 3));
				}
			}
		else
			{
			statusLabel->setText("<font color='red'>Leider gibt es keine gültige Route zwischen den eingegeben Start- und Zielpunkten.</font>");
			}
		}
	}


//wird ausgelöst, wenn im Rechtsklickmenü der Startpunkt gesetzt werden soll:
void MainWindow::startFestlegen()
	{
	//berechne die Koordinaten des Punktes:
	//("rechtsklickPunkt" war ja der Punkt, wo gespeichert wurde, wo rechtsgeklickt
	//wurde)
	double lo=tilex2long(xkoord,zoom);
	lo=lo+((tilex2long(xkoord+1,zoom)-lo)/256)*(rechtsklickPunkt.x()-korrigierteSzene.x());
	double la=tiley2lat(ykoord,zoom);
	la=la+((tiley2lat(ykoord+1,zoom)-la)/256)*(rechtsklickPunkt.y()-korrigierteSzene.y());

	startpunkt=QPointF(lo,la);	//setze den Startpunkt auf die Koordinaten
	startpunktExistiert=true;	//merke dir, dass schon ein Startpunkt gewählt wurde
	widget->startKoordSetzen(startpunkt);
	}


//Zielpunkt Festlegen (wie beim Startpunkt, nur dass die Koordinaten hier in
//"zielpunkt" gespeichert werden):
void MainWindow::zielFestlegen()
	{
	//Koordinaten berechnen:
	double lo=tilex2long(xkoord,zoom);
	lo=lo+((tilex2long(xkoord+1,zoom)-lo)/256)*(rechtsklickPunkt.x()-korrigierteSzene.x());
	double la=tiley2lat(ykoord,zoom);
	la=la+((tiley2lat(ykoord+1,zoom)-la)/256)*(rechtsklickPunkt.y()-korrigierteSzene.y());

	zielpunkt=QPointF(lo,la);	//Koordinaten speichern
	zielpunktExistiert=true;	//merken, dass Zielpunkt existiert
	widget->zielKoordSetzen(zielpunkt);
	}


//Löscht alle eingezeichneten Routen und resettet den Vektor, der die Routen
//gespeichert hat:
void MainWindow::routenLoeschen()
	{
	//gehe alle Items in der Szene durch:
	foreach(QGraphicsItem *item, widget->getView()->scene()->items())
		{
		//wenn du etwas findest, was kein PixmapItem ist, lösche es aus der Szene:
		if(item->type() != QGraphicsPixmapItem::Type)
			{
			widget->getView()->scene()->removeItem(item);
			delete item;
			}
		}

	//resette den Vektor, der die Routen gespeichert hat:
	vektorFurWegvektoren = new std::vector<std::vector<int> >;
	}


//Löscht alle eingezeichneten Routen aus der Szene, lässt aber den Routenvektor
//unangetastet:
void MainWindow::routenOptischEntfernen()
	{
	//gehe alle Items in der Szene durch:
	foreach (QGraphicsItem *item, widget->getView()->scene()->items())
		{
		//lösche alles aus der Szene, was kein PixmapItem ist:
		if (item->type() != QGraphicsPixmapItem::Type)
			{
			widget->getView()->scene()->removeItem(item);
			delete item;
			}
		}
	}


//Zeichnet alle Routen im Routenvektor neu in die Szene (z.B. nachdem beim Zoomen
//alle Routen entfernt wurden, und diese in der neuen Zoomstufe wieder eingezeichnet
//werden sollen)
void MainWindow::routenNeuEinzeichnen()
	{
	//gehe jede Route durch:
	for(unsigned int i = 0; i<vektorFurWegvektoren->size(); i++)
		{
		//gehe jeden Punkt der Route durch und zeichne eine Linie zu seinem Nachfolger:
		for(int j = ((*vektorFurWegvektoren)[i].size())-2; j>=0; j--)
			{
			int x1 = (long2tile((*knoten)[(*vektorFurWegvektoren)[i][j]].x,zoom)-xkoord)*256+korrigierteSzene.x();
			int y1 = (lat2tile((*knoten)[(*vektorFurWegvektoren)[i][j]].y,zoom)-ykoord)*256+korrigierteSzene.y();
			int x2 = (long2tile((*knoten)[(*vektorFurWegvektoren)[i][j+1]].x,zoom)-xkoord)*256+korrigierteSzene.x();
			int y2 = (lat2tile((*knoten)[(*vektorFurWegvektoren)[i][j+1]].y,zoom)-ykoord)*256+korrigierteSzene.y();
			widget->getView()->scene()->addLine(x1,y1,x2,y2,QPen(Qt::blue, 3));
			}
		}
	}


void MainWindow::optionen()
	{
	bool *ok = new bool();
	QInputDialog *dialog = new QInputDialog();
	int input = dialog->getInt(this, "Neuen Wert eingeben", "Bitte neuen Wert für die Anzahl\nder zu ladenden Kacheln\neingeben:\n(Standard ist 7, wenn das\nProgramm zu langsam ist,\nsollte ein kleinerer Wert\ngewählt werden)", 7, 3, 99, 1, ok);

	if(*ok)
		{
		if(input%2==0)
			{
			input = input -1;
			}
		if(input!=sichtbaresFeld)
			{
			widget->getView()->scene()->clear();
			kartenrasterAnlegen(input);
			}
		}
	}


//ToDo:
//-setzeKarteNeu schöner überarbeiten
