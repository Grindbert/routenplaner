#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QPixmap>
#include <QPoint>
#include <string>
#include <sstream>
#include <QString>

class Downloader : public QObject
{
	Q_OBJECT

	QNetworkAccessManager meinManager;
	QNetworkRequest meinReq;
	//meinReq.setUrl(QUrl("Platzhalter"));
	QNetworkReply *meinReply;
	QPixmap *meinePixmap;
	std::string url;
	//QString url;
	std::stringstream ss;



	public:
	explicit Downloader(QObject *parent = 0);
	QPixmap getPixmap();
	void ladeKachel(int, int, int);


	signals:

	public slots:

	void fortsetzung();
	};

#endif // DOWNLOADER_H


/*QNetworkAccessManager meinManager;
QNetworkRequest meinReq;
QNetworkReply *meinReply;// = new QNetworkReply();
meinReply = new QNetworkReply;
QPixmap *meinePixmap = new QPixmap;

meinReq.setUrl(qurl);
meinReply=meinManager.get(meinReq);
while(meinReply->isRunning()){}

QByteArray content = meinReply->readAll();
meinePixmap->loadFromData(content);

return(*meinePixmap);*/


