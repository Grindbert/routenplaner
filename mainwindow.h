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

#include "widgets.h"


class MainWindow : public QMainWindow
	{
	Q_OBJECT
	QMenu* fileMenu;
	QLabel* statusLabel;
	Widgets* widget;
	QGraphicsScene *szene;
	std::vector<QGraphicsPixmapItem*> kacheln;

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	void starteKarte();

	private slots:
	void pixmapAdden(QPixmap, int);
	};

#endif // MAINWINDOW_H
