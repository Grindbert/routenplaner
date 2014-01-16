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

#include "widgets.h"
#include "downloader.h"
#include "Knoten.h"		//Klasse Knoten einbinden
#include "Wegfindung.h"	//Dijkstra-Algorithmus
#include "Timer.h"


class MainWindow : public QMainWindow
	{
	Q_OBJECT
	QMenu* fileMenu;	//Menüleiste
	QLabel* statusLabel;	//kommt in die Statuszeile
	Widgets* widget;	//Widgetcontainer
	std::vector<QGraphicsPixmapItem*> kacheln;	//speichert Zeiger
				//auf die Pixmaps, die als QGrahicsPixmapItem in die
				//Szene getan werden
	std::vector<QPixmap> pixmaps;

	std::vector<Downloader*> downl;	//Downloader für die Kacheln
	int zoom, xkoord, ykoord;	//speichert aktuelle Zoomstufe,
			//x- und y-Nummern der Kacheln

	std::vector<Knoten> *knoten;

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	void starteKarte(int, int, int);
	void setzeKarteNeu(int, int, int);


	private slots:
	void pixmapAdden(QPixmap, int);
	void geheNorden();
	void geheSueden();
	void geheOsten();
	void geheWesten();
	void zoomIn();
	void zoomOut();
	void graphLaden();
	void wegBerechnen();
	void rechteMaustasteGeklickt(QPointF);

	//irgendwelche Hilfsvariablen, die noch weg sollen,
	//aber zentral an einer Stelle stehen sollen

	public:
	int zaehler;
	bool hilfe;
	int hilfszaehler;

	};

#endif // MAINWINDOW_H
