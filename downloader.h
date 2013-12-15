#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QByteArray>
#include <QPixmap>
#include <QPoint>
#include <string>
#include <sstream>
#include <QString>

class Downloader : public QObject
	{
	Q_OBJECT

	QNetworkAccessManager *meinManager;
	QNetworkRequest meinReq;
	QNetworkReply *meinReply;
	QPixmap *meinePixmap;
	QByteArray daten;
	std::string url;
	std::stringstream ss;


	public:
	explicit Downloader(QObject *parent = 0);
	virtual ~Downloader();
	QPixmap getPixmap();
	void ladeKachel(int, int, int);


	signals:
	void gedownloaded();

	public slots:
	void fortsetzung(QNetworkReply *rep);
	};



class FileDownloader : public QObject
	{
	Q_OBJECT

	QNetworkAccessManager meinManager;
	QPixmap meinePixmap;
	std::string url;
	std::stringstream ss;


	public:
	explicit FileDownloader(QObject *parent = 0);
	virtual ~FileDownloader();

	void ladeKachel(int, int, int);
	QPixmap getPixmap();


	signals:
	void downloaded();

	private slots:
	void fileDownloaded(QNetworkReply* pReply);

	private:

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


