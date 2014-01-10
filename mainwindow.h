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

#include "widgets.h"
#include "downloader.h"


class MainWindow : public QMainWindow
	{
	Q_OBJECT
	QMenu* fileMenu;	//Menüleiste
	QLabel* statusLabel;	//kommt in die Statuszeile
	Widgets* widget;	//Widgetcontainer
	QGraphicsScene *szene;	//Zeiger auf die Szene im Graphics View
	std::vector<QGraphicsPixmapItem*> kacheln;	//speichert Zeiger
				//auf die Pixmaps, die als QGrahicsPixmapItem in die
				//Szene getan werden
	std::vector<QPixmap> pixmaps;

	std::vector<Downloader*> downl;	//Downloader für die Kacheln
	int zoom, xkoord, ykoord;	//speichert aktuelle Zoomstufe,
			//x- und y-Nummern der Kacheln

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	void starteKarte(int, int, int);
	void setzeKarteNeu(int, int, int);
	//bool eventFilter(QObject *, QEvent *);


	private slots:
	void pixmapAdden(QPixmap, int);
	void geheNorden();
	void geheSueden();
	void geheOsten();
	void geheWesten();
	void zoomIn();
	void zoomOut();
	void mousePressEvent(QMouseEvent*);

	void testSlot();

	//irgendwelche Hilfsvariablen, die noch weg sollen,
	//aber zentral an einer Stelle stehen sollen
	public:
	int zaehler;
	bool hilfe;
	int hilfszaehler;

	};

#endif // MAINWINDOW_H
