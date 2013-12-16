#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QByteArray>
#include <QPixmap>
#include <string>
#include <sstream>
#include <QString>


class Downloader : public QObject
	{
	Q_OBJECT

	QNetworkAccessManager meinManager;
	std::string url;
	std::stringstream ss;
	QPixmap *meinePixmap;
	int stelleInSzene;

	public:
	//Konstruktor und Destruktor:
	explicit Downloader(QObject *parent = 0);
	virtual ~Downloader();

	void ladeKachel(int, int, int, int);

	signals:
	void gedownloaded(QPixmap, int);

	private slots:
	void fileDownloaded(QNetworkReply* pReply);
	};


#endif // DOWNLOADER_H


