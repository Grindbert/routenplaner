#include "downloader.h"
#include <iostream>
#include <unistd.h>

Downloader::Downloader(QObject *parent) :
	QObject(parent)
	{
	meinManager=new QNetworkAccessManager(this);
	meinePixmap = new QPixmap;
	url ="http://tile.openstreetmap.org/";
	//connect(meinManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(fortsetzung(QNetworkReply *)));

	//std::cout<<meinManager->isSignalConnected(meinManager->finished())<<std::endl;

	/* Eigentlich wollte ich hier im Konstruktor schon das Signal
	 * finished() mit meinem fortsetzung() connecten, aber um das
	 * Reply mit irgendwas connecten zu können, muss es vorher
	 * initialisiert (oder deklariert??) werden, also eine url bekommen.
	 * Das hier:
	 * meinReply = new QNetworkReply();
	 * funktioniert leider als initialisierung nicht, da wirft der
	 * Compiler die Fehlermeldung "cannot allocate an object of abstract
	 * type 'QNetworkReply'". Klingt ja auch fast logisch, in der Hilfe
	 * ist ja nicht einmal ein Konstruktor für die Klasse aufgeführt.
	 * Wenn ich dann versuche, ihm einfach irgendeine url zuzuweisen, und
	 * dann zu connecten, also etwa so:
	 * meinReq.setUrl(QUrl("http://tile.openstreetmap.org/12/2200/1312.png"));
	 * connect((const QObject*)meinReply, SIGNAL(finished()), this, SLOT(fortsetzung()));
	 * dann compiliert er zwar, aber sagt mir, mein Programm wäre abgestürzt.
	 * Das einzige, was im Moment "funktioniert", ist wenn ich es bei der
	 * Funktion ladeKachel mit rinpacke (was ich ja aber eigentlich nicht
	 * wollte, weil ich es dann ja jedes mal wieder connecte, wenn ich eine
	 * neue Kachel lade...
	 */
	//std::cout<<"fertig?\n";
	}

void Downloader::ladeKachel(int z, int x, int y)
	{
	std::cout<<"Lade ich Kachel???\n";

	//url zusammenbasteln:
	ss<<url<<z<<"/"<<x<<"/"<<y<<".png";
	url=ss.str();

	std::cout<<url<<std::endl;

	//QString bla = QString(url.c_str());
	//std::cout<<bla.toUtf8().constData()<<std::endl;

	//url an das QNetworkRequest übergeben und download starten:
	meinReq.setUrl(QUrl(QString(url.c_str())));

	//meinReply=meinManager->get(meinReq);
	meinReply=meinManager->get(QNetworkRequest(QUrl(QString(url.c_str()))));

	connect(meinReply, SIGNAL(readyRead()), this, SLOT(fortsetzung()));


	//usleep(60000000);

	//std::cout<<"vor connect\n";

	//while (meinReply->isRunning()){std::cout<<"Ich bin eine Endlosschleife...\n";}
	/* offensichtlich wird der Reply nicht fertig mit downloaden, ich weiß
	 * aber nicht, warum...
	 */


	//std::cout<<"nach connect\n";
	}

//void Downloader::fortsetzung(QNetworkReply *rep)
void Downloader::fortsetzung()
	{
	std::cout<<"fortsetzung erreicht?\n";
	QByteArray content = meinReply->readAll();
	meinePixmap->loadFromData(content);
	}

QPixmap Downloader::getPixmap()
	{
	return(*meinePixmap);
	}
