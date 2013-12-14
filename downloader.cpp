#include "downloader.h"
#include <iostream>
#include <unistd.h>

Downloader::Downloader(QObject *parent) :
	QObject(parent)
	{
	connect(&meinManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(fortsetzung(QNetworkReply *)));
	//meinManager=new QNetworkAccessManager(this);
	meinePixmap = new QPixmap;
	url ="http://tile.openstreetmap.org/";
	//connect(meinManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(fortsetzung(QNetworkReply *)));

	//std::cout<<meinManager->isSignalConnected(meinManager->finished())<<std::endl;

	std::cout<<"Konstruktor fertig?\n";
	}

Downloader::~Downloader()
	{}


void Downloader::ladeKachel(int z, int x, int y)
	{
	std::cout<<"Lade ich Kachel???\n";

	//url zusammenbasteln:
	ss<<url<<z<<"/"<<x<<"/"<<y<<".png";
	url=ss.str();

	std::cout<<url<<std::endl;

	QString test_was_im_QString_landet = QString(url.c_str());
	std::cout<<test_was_im_QString_landet.toUtf8().constData()<<std::endl;


	//url an das QNetworkRequest übergeben und download starten:
	meinReq.setUrl(QUrl(QString(url.c_str())));
	std::cout<<"mitte\n";
	meinManager.get((const QNetworkRequest&)meinReq);
	//meinReply=meinManager->get(QNetworkRequest(QUrl(QString(url.c_str()))));

	//connect(meinReply, SIGNAL(readyRead()), this, SLOT(fortsetzung()));


	//usleep(60000000);

	//std::cout<<"vor connect\n";

	//while (meinReply->isRunning()){std::cout<<"Ich bin eine Endlosschleife...\n";}


	std::cout<<"Ende von ladeKachel\n";
	}

void Downloader::fortsetzung(QNetworkReply *rep)
//void Downloader::fortsetzung()
	{
	std::cout<<"fortsetzung erreicht?\n";
	daten = rep->readAll();
	emit downloaded();
	//meinePixmap->loadFromData(content);
	}

void downloaded()
	{

	}

QPixmap Downloader::getPixmap()
	{
	return(*meinePixmap);
	}

