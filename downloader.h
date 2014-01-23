#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QByteArray>
#include <QPixmap>
#include <QString>

#include <funktionen.h>


class Downloader : public QObject
	{
	Q_OBJECT

	QNetworkAccessManager meinManager;
	QPixmap *meinePixmap;
	int stelleInSzene;

	public:
	explicit Downloader(QObject *parent = 0);
	virtual ~Downloader();

	void ladeKachel(int, int, int, int);

	signals:
	void gedownloaded(QPixmap, int);

	private slots:
	void fileDownloaded(QNetworkReply* pReply);

	public:
	//QByteArray zwischenablage;
	//NetworkError bla;
	};


#endif // DOWNLOADER_H


