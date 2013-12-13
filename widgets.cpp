#include <QFont>
#include "widgets.h"
#include "downloader.h"

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


	Downloader meinDownl;
	meinDownl.ladeKachel(12,2200,1312);


	QGraphicsScene *meineSzene = new QGraphicsScene;

	QPixmap meinePixmap=meinDownl.getPixmap();
	//meinePixmap.load(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1312.png"));



	QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
	item=meineSzene->addPixmap(meinePixmap);

	item->setOffset(QPoint(0,-256));


	/*QPixmap meinePixmap2;
	meinePixmap2.load(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1313.png"));

	QGraphicsPixmapItem *item2 = new QGraphicsPixmapItem;
	item2 = meineSzene->addPixmap(meinePixmap2);


	/*QPixmap bla = ladeKachel(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1312.png"));
	meineSzene->addPixmap(bla);*/

	graphicsView = new QGraphicsView(meineSzene);

	gridLayout->addWidget(graphicsView, 0,1,3,1);

	gridLayout->setColumnStretch(1, 10);
	setLayout(gridLayout);
	qdial->setValue(50);
	}
