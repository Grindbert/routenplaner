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

#include "widgets.h"
#include "downloader.h"
#include "Knoten.h"		//Klasse Knoten einbinden
#include "Wegfindung.h"	//Dijkstra-Algorithmus
#include "Timer.h"
#include "funktionen.h"

#include <iostream>


class MainWindow : public QMainWindow
	{
	Q_OBJECT

	//Variablen, die das Mainwindow hat:
	//===============================================

	//Variablen für das Feld:
	int sichtbaresFeld;
	int seitenlaenge;
	int anzahlKacheln;

	QPixmap weisseKachel;	//Platzhalter für leer Kacheln

	//alles, was im Fenster sichtbar sein wird:
	QMenu* fileMenu;		//Menüleiste
	QLabel* statusLabel;	//kommt in die Statuszeile
	Widgets* widget;		//Widgetcontainer

	//Vektoren für alles Mögliche:
	std::vector<QGraphicsPixmapItem*> kacheln;	//speichert Zeiger
				//auf die Pixmaps, die als QGrahicsPixmapItem in die
				//Szene getan werden
	std::vector<QGraphicsEllipseItem*> punktvkt;	//speichert Punkte,
				//die in der Szene gesetzt werden
	std::vector<int> perm;	//Permutationsvektor

	std::vector<Downloader*> downl;	//Downloader für die Kacheln

	std::vector<Knoten> *knoten;	//speichert den Graph aus der
				//Input-datei

	int zoom, xkoord, ykoord;	//speichert aktuelle Zoomstufe,
			//x- und y-Nummern der Kacheln

	//Punkte für das Maus-Drag-Zeug:
	QPointF mausDrag;
	QPoint korrigierteSzene;



	//Funktionen, Signale und Slots:
	//=========================================================

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	void starteKarte();
	void setzeKarteNeu(int, int, int);


	private slots:
	void pixmapAdden(QPixmap, int);
	void geheNorden();
	void geheSueden();
	void geheOsten();
	void geheWesten();
	void zoomIn(QPointF);
	void zoomOut(QPointF);
	void graphLaden();
	void wegBerechnen();
	void berechneKoordinaten(QPointF);
	void bewegungTesten(bool, QPointF);
	void starteKarteFortsetzung(QPixmap);
	void rechteMaustasteGeklickt(QPointF);
	};

#endif // MAINWINDOW_H
