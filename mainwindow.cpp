#include "mainwindow.h"
#include "widgets.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
	{
	setAttribute(Qt::WA_DeleteOnClose);
	setGeometry(100, 100, 800, 600);
	widget = new Widgets(this);
	setCentralWidget(widget);
	menuAnlegen();
	statuszeileAnlegen();
	//connect(widget->getZeichenflaeche(), SIGNAL(radiusChanged(int)), this, SLOT(statuszeileAktualisieren(int)));

	meinReq.setUrl(QUrl("http://tile.openstreetmap.org/12/2200/1312.png"));
	meinReply=meinManager->get(meinReq);
	connect((const QObject*)meinReply, SIGNAL(finished()),this,SLOT(requestFertig()));
	}

MainWindow::~MainWindow()
	{}

void MainWindow::menuAnlegen()
	{
	//Beenden-Button:
	fileMenu = menuBar()->addMenu(tr("&Datei"));
	QAction *ladeGraph = new QAction(tr("&Graph laden"), this);
	ladeGraph->setShortcut(tr("Ctrl+L"));
	ladeGraph->setStatusTip(tr("lies Graph von Textdatei ein"));
	fileMenu->addAction(ladeGraph);

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

void MainWindow::requestFertig()
	{
	QByteArray content = meinReply->readAll();
	QPixmap meinePixmap;
	meinePixmap.loadFromData(content);
	}
