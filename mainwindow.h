#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QStatusBar>

#include "widgets.h"


class MainWindow : public QMainWindow
	{
	Q_OBJECT
	QMenu* fileMenu;
	QLabel* statusLabel;
	Widgets* widget;

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();

	//private slots:
	};

#endif // MAINWINDOW_H
