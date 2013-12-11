#ifndef WIDGETS_H
#define WIDGETS_H

#include <QWidget>
#include <QMainWindow>
#include <QDial>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsView>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QPixmap>


class Widgets : public QWidget
{
	Q_OBJECT

	QDial *qdial;
	QSpinBox *qspinbox;
	QPushButton *maxWertButton;
	QGridLayout *gridLayout;
	QGraphicsView *graphicsView;

	QNetworkAccessManager meinManager;
	QNetworkRequest meinReq;
	QNetworkReply *meinReply;


	public:
	explicit Widgets(QMainWindow *parent = 0);



	signals:

	public slots:

	private slots:
	void requestFertig(QPixmap*);


	};

#endif // WIDGETS_H
