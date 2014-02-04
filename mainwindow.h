#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QStatusBar>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QAction>
#include <QFileDialog>
#include <fstream>	//filestreams
#include <sstream>	//stringstream
#include <stdlib.h>
#include <vector>

#include "widgets.h"	//für den Widgetcontainer
#include "downloader.h"
#include "Knoten.h"		//Klasse Knoten einbinden
#include "Wegfindung.h"	//Dijkstra-Algorithmus
#include "Timer.h"
#include "funktionen.h"	//für Umrechnung von Pixel in Koordinaten

#include <iostream>


class MainWindow : public QMainWindow
	{
	Q_OBJECT

	//===============================================
	//Variablen, die das Mainwindow hat:
	//===============================================

	//Variablen für das Feld:
	int sichtbaresFeld;
	int seitenlaenge;
	int anzahlKacheln;

	QPixmap weisseKachel;	//Platzhalter für leer Kacheln

	//alles, was im Fenster sichtbar sein wird:
	QMenu* menuDatei;	//Menüpunkt "Datei"
	QMenu* menuRoute;	//Menüpunkt "Route"
	QMenu* menuHilfe;	//Menüpunkt "Hilfe"
	QLabel* statusLabel;	//kommt in die Statuszeile
	Widgets* widget;		//Widgetcontainer

	//Vektoren für alles Mögliche:
	std::vector<QGraphicsPixmapItem*> kacheln;	//speichert die Zeiger
				//auf die QGraphicsPixmapItems, die das Einfügen der Pixmaps
				//in die Szene zurückgegeben werden
	//std::vector<QGraphicsEllipseItem*> punktvkt;	//speichert Punkte,
				//die in der Szene gesetzt werden
	std::vector<int> perm;	//Permutationsvektor

	std::vector<Downloader*> downl;	//Downloader für die Kacheln

	std::vector<Knoten> *knoten;	//speichert den Graph aus der
				//Input-datei

	std::vector<std::vector<int> > *vektorFurWegvektoren;	//speichert die
				//Routen, die in der Wegfindung berechnet werden, um sie z.B.
				//beim Zoomen wieder neu einzeichnen zu können

	int zoom, xkoord, ykoord;	//speichert aktuelle Zoomstufe und die
			//x- und y-Nummer der zentralen Kachel

	//Punkte für das Maus-Drag-Zeug:
	QPointF mausDrag;
	QPoint korrigierteSzene;

	//Objekte für das Rechtsklickmenü:
	QMenu rechtsklickmenu;
	QPointF rechtsklickPunkt;

	//speichert Input vom User:
	QPointF startpunkt;	//speichert den Startpunkt der Route
	QPointF zielpunkt;	//speichert den Zielpunkt der Route
	bool startpunktExistiert;	//speichert, ob schon ein Startpunkt angegeben wurde
	bool zielpunktExistiert;	//speichert, ob schon ein Zielpunkt angegeben wurde
	bool dateiGeladen;		//speichert, ob schon eine Datei eingelesen wurde



	//=========================================================
	//Funktionen, Signale und Slots:
	//=========================================================

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	void rechtsklickmenuAnlegen();
	void starteKarte();
	void setzeKarteNeu(int, int, int);
	void routenOptischEntfernen();
	void routenNeuEinzeichnen();


	private slots:
	void starteKarteFortsetzung(QPixmap);
	void pixmapAdden(QPixmap, int);
	void karteZentrieren();

	void geheNorden();
	void geheSueden();
	void geheOsten();
	void geheWesten();

	void geheNordenButton();
	void geheSuedenButton();
	void geheOstenButton();
	void geheWestenButton();

	void zoomIn(QPointF);
	void zoomOut(/*QPointF*/);
	void zoomInButton();
	//void zoomOutButton();

	void rechteMaustasteGeklickt(QPointF);
	void berechneKoordinaten(QPointF);
	void bewegungTesten(bool, QPointF);

	void graphLaden();
	void wegBerechnen();
	void startFestlegen();
	void zielFestlegen();
	void routenLoeschen();
	};

#endif // MAINWINDOW_H
