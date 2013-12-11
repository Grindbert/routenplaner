#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QStatusBar>
#include <widgets.h>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>


class MainWindow : public QMainWindow
	{
	Q_OBJECT
	QMenu* fileMenu;
	QLabel* statusLabel;
	Widgets* widget;

	QNetworkAccessManager meinManager;//=new QNetworkAccessManager(this);
	QNetworkRequest meinReq;

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	};

#endif // MAINWINDOW_H
