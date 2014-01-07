#include "downloader.h"

Downloader::Downloader(QObject *parent) :
	QObject(parent)
	{
	meinePixmap=new QPixmap;
	connect(&meinManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));
	url ="http://tile.openstreetmap.org/";
	}

Downloader::~Downloader()
	{}

void Downloader::ladeKachel(int z, int x, int y, int stelleInSzeneEingabe)
	{
	stelleInSzene=stelleInSzeneEingabe;

	//url zusammenbasteln:
	//ss<<url<<z<<"/"<<x<<"/"<<y<<".png";
	//url=ss.str();

	QString test = "http://tile.openstreetmap.org/";
	test = test + QString::number(z) + "/" + QString::number(x) + "/" + QString::number(y) + ".png";

	//Kachel runterladen:
	//meinManager.get(QNetworkRequest(QUrl(url.c_str())));
	meinManager.get(QNetworkRequest(QUrl(test)));
	}

void Downloader::fileDownloaded(QNetworkReply* pReply)
	{
	//Umwandeln des Replys in eine Pixmap:
	QByteArray zwischenablage;
	zwischenablage = pReply->readAll();
	meinePixmap->loadFromData(zwischenablage);

	pReply->deleteLater();

	//gib Laut, wenn du fertig bist:
	emit gedownloaded(*meinePixmap, stelleInSzene);
	}
