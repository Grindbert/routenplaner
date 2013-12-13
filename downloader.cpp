#include "downloader.h"
#include <iostream>

Downloader::Downloader(QObject *parent) :
	QObject(parent)
	{
	//meinReply = new QNetworkReply();
	meinePixmap = new QPixmap;
	meinReq.setUrl(QUrl("http://tile.openstreetmap.org/12/2200/1312.png"));
	url ="http://tile.openstreetmap.org/";

	}

void Downloader::ladeKachel(int z, int x, int y)
	{
	std::cout<<"Lade ich Kachel???\n";
	ss<<url<<z<<"/"<<x<<"/"<<y<<".png";
	url=ss.str();
	std::cout<<url<<std::endl;
	meinReq.setUrl(QUrl(QString(url.c_str())));
	meinReply=meinManager.get(meinReq);
	std::cout<<"vor connect\n";
	connect((const QObject*)meinReply, SIGNAL(finished()), this, SLOT(fortsetzung()));
	//while (meinReply->isRunning()){std::cout<<"bla\n";}
	std::cout<<"nach connect\n";
	}

void Downloader::fortsetzung()
	{
	QByteArray content = meinReply->readAll();
	meinePixmap->loadFromData(content);
	std::cout<<"Yey?\n";
	}

QPixmap Downloader::getPixmap()
	{
	return(*meinePixmap);
	}
