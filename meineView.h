#ifndef MEINEVIEW_H
#define MEINEVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

//meineView soll im Prinzip das Gleiche machen, wie die
//normale QGraphicsView, aber beim Scrollen, also den
//wheelEvents, soll in der Karte gezoomt und nicht gescrollt
//werden. Daher wird das wheelEvent überschrieben, sodass
//es Signale zum Rin- und Rauszoomen aussendet, die im
//Konstruktor des MainWindows mit den Zoom-Slots connected
//werden.

class MeineView : public QGraphicsView
	{
	Q_OBJECT

	public:
	MeineView(QGraphicsScene*);
	virtual void wheelEvent(QWheelEvent*);

	signals:
	void zoomInSignal();
	void zoomOutSignal();

	//public slots:

	};

#endif // MEINEVIEW_H
