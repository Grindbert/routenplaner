#include "downloader.h"

Downloader::Downloader(QObject *parent) :
	QObject(parent)
	{
	meinePixmap=new QPixmap;	//meinePixmap initialisieren... oder deklarieren??
	connect(&meinManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));
	}

Downloader::~Downloader()
	{}

void Downloader::ladeKachel(int z, int x, int y, int stelleInSzeneEingabe)
	{
	stelleInSzene=stelleInSzeneEingabe;

	//Url für die angefragte Kachel zusammenbauen:
	QString url = "http://tile.openstreetmap.org/" + QString::number(z)
			+ "/" + QString::number(x) + "/" + QString::number(y) + ".png";

	//Kachel runterladen:
	meinManager.get(QNetworkRequest(QUrl(url)));

	//wenn fertig mit ladeKachel, wird gleich mit fileDownloaded 3 Zeilen weiter
	//unten weitergemacht
	//(siehe connect im Konstruktor)
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
