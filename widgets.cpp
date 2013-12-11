#include <QFont>
#include "widgets.h"

Widgets::Widgets(QMainWindow *parent) : QWidget(parent)
	{
	qdial=new QDial;
	qspinbox=new QSpinBox;
	maxWertButton = new QPushButton("100%");

	maxWertButton->setFont(QFont("Helvetica", 16, QFont::Normal));
	qdial->setNotchesVisible(true);
	qspinbox->setFont(QFont("Helvetica", 12, QFont::StyleNormal));

	gridLayout = new QGridLayout(this);
	gridLayout->addWidget(maxWertButton, 0, 0);
	gridLayout->addWidget(qspinbox, 1, 0);
	gridLayout->addWidget(qdial, 2, 0);






	/*meinReq.setUrl(QUrl("http://tile.openstreetmap.org/12/2200/1312.png"));
	meinReply=meinManager.get(meinReq);
	QPixmap *meinePixmap;
	connect((const QObject*)meinReply, SIGNAL(finished()),this,SLOT(requestFertig(meinePixmap)));*/

	QPixmap meinePixmap;
	meinePixmap.load(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1312.png"));

	QGraphicsScene *meineSzene = new QGraphicsScene;

	QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
	item=meineSzene->addPixmap(meinePixmap);

	item->setOffset(QPoint(0,-256));


	QPixmap meinePixmap2;
	meinePixmap2.load(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1313.png"));

	QGraphicsPixmapItem *item2 = new QGraphicsPixmapItem;
	item2 = meineSzene->addPixmap(meinePixmap2);



	graphicsView = new QGraphicsView(meineSzene);

	gridLayout->addWidget(graphicsView, 0,1,3,1);

	gridLayout->setColumnStretch(1, 10);
	setLayout(gridLayout);
	qdial->setValue(50);
	}

/*void Widgets::requestFertig(QPixmap *meinePixmap)
	{
	QByteArray content = meinReply->readAll();
	meinePixmap->loadFromData(content);
	}*/
