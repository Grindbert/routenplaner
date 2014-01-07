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
	QMenu* fileMenu;
	QLabel* statusLabel;
	Widgets* widget;
	QGraphicsScene *szene;
	std::vector<QGraphicsPixmapItem*> kacheln;

	int zaehler;

	std::vector<Downloader*> downl;
	int zoom, xkoord, ykoord;

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	void starteKarte(int, int, int);
	void setzeKarteNeu(int, int, int);
	void wheelEvent(QWheelEvent *event);
	//bool eventFilter(QObject *, QEvent *);

	bool hilfe;
	int hilfszaehler;

	private slots:
	void pixmapAdden(QPixmap, int);
	void geheNorden();
	void geheSueden();
	void geheOsten();
	void geheWesten();
	void zoomIn();
	void zoomOut();
	};

#endif // MAINWINDOW_H
