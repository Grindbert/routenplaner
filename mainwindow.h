#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QStatusBar>
#include <widgets.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/qnetworkrequest.h>



class MainWindow : public QMainWindow
	{
	Q_OBJECT
	QMenu* fileMenu;
	QLabel* statusLabel;
	Widgets* widget;

	QNetworkAccessManager *meinManager;
	//QNetworkRequest meinReq;

	public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	private:
	void menuAnlegen();
	void statuszeileAnlegen();
	};

#endif // MAINWINDOW_H
