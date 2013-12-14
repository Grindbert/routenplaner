#include "mainwindow.h"
#include "widgets.h"
#include "downloader.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	{
	setAttribute(Qt::WA_DeleteOnClose);
	setGeometry(100, 100, 800, 600);
	widget = new Widgets(this);
	setCentralWidget(widget);
	menuAnlegen();
	statuszeileAnlegen();
	//starteKarte();
	//connect(widget->getZeichenflaeche(), SIGNAL(radiusChanged(int)), this, SLOT(statuszeileAktualisieren(int)));
	}

MainWindow::~MainWindow()
	{}


void MainWindow::starteKarte()
	{
	//Downloader meinDownl;
	//meinDownl.ladeKachel(12,2200,1312);
	}





void MainWindow::menuAnlegen()
	{
	//Datei-Menü:
	fileMenu = menuBar()->addMenu(tr("&Datei"));

	//Graph-laden-Button:
	QAction *ladeGraph = new QAction(tr("&Graph laden"), this);
	ladeGraph->setShortcut(tr("Ctrl+L"));
	ladeGraph->setStatusTip(tr("lies Graph von Textdatei ein"));
	fileMenu->addAction(ladeGraph);

	//Beenden-Button:
	QAction *quitAction = new QAction(tr("&Beenden"), this);
	quitAction->setShortcut(tr("Ctrl+T"));
	quitAction->setStatusTip(tr("Programm beenden"));
	fileMenu->addAction(quitAction);
	// qApp ist globale Variable der Applikation
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	}

void MainWindow::statuszeileAnlegen()
	{
	statusLabel = new QLabel("nicht bewegt");
	statusBar()->addWidget(statusLabel);
	}
