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

	int xZumBearbeiten=x;

	//Wenn x rechts aus der Weltkarte rausläuft, fange wieder links an:
	if(xZumBearbeiten>=pow(2,z))
		{
		xZumBearbeiten=xZumBearbeiten%((int)pow(2,z));
		}

	//Wenn x links aus der Weltkarte rausläuft, fange rechts wieder an:
	if(xZumBearbeiten<0)
		{
		xZumBearbeiten=pow(2,z)+(xZumBearbeiten%((int)pow(2,z)));
		}

	//Url für die angefragte Kachel zusammenbauen:
	QString url = "http://tile.openstreetmap.org/" + QString::number(z)
			+ "/" + QString::number(xZumBearbeiten) + "/" + QString::number(y) + ".png";

	//Kachel runterladen:
	QNetworkRequest re=QNetworkRequest(QUrl(url));
	re.setRawHeader("User-Agent" , "Mozilla Firefox");

	meinManager.get(re);

	//meinManager.get(QNetworkRequest(QUrl(url)));

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

QPixmap Downloader::getPixmap()
	{
	return(*meinePixmap);
	}
