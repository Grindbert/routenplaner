#include <QFont>
#include "widgets.h"
#include "downloader.h"
#include <QUrl>
#include <unistd.h>	//für das usleep

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


	//QUrl imageUrl("http://qt.digia.com/Documents/1/QtLogo.png");
	FileDownloader *m_pImgCtrl = new FileDownloader(/*imageUrl,*/ this);
	m_pImgCtrl->ladeKachel(12,2200,1312);

	usleep(10000000);


	//Downloader meinDownl;
	//meinDownl.ladeKachel(12,2200,1312);


	QGraphicsScene *meineSzene = new QGraphicsScene;

	QPixmap *meinePixmap = new QPixmap;//=meinDownl.getPixmap();

	*meinePixmap=m_pImgCtrl->getPixmap();

	QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
	item=meineSzene->addPixmap(*meinePixmap);


	/*QPixmap *meinePixmap2 = new QPixmap;
	meinePixmap2->load(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1312.png"));
	*/

	//QGraphicsPixmapItem *item2 = new QGraphicsPixmapItem((const QPixmap&)meinePixmap2);

	//*item=*item2;

	//item->setPixmap((const QPixmap&)meinePixmap2);

	//meineSzene->addItem(item2);

	//item->setOffset(QPoint(0,-256));


	/*QPixmap meinePixmap2;
	meinePixmap2.load(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1313.png"));

	QGraphicsPixmapItem *item2 = new QGraphicsPixmapItem;
	item2 = meineSzene->addPixmap(meinePixmap2);


	QPixmap bla = ladeKachel(QString("/media/grindbert/Aeneon/Basti_C++/Route/12-2200-1312.png"));
	meineSzene->addPixmap(bla);*/

	graphicsView = new QGraphicsView(meineSzene);

	//graphicsView->scene();

	gridLayout->addWidget(graphicsView, 0,1,3,1);

	gridLayout->setColumnStretch(1, 10);
	setLayout(gridLayout);
	qdial->setValue(50);
	}
