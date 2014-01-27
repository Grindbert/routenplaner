#ifndef MEINEVIEW_H
#define MEINEVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

#include "meineSzene.h"

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

	void resizeEvent(QResizeEvent*);

	public:
	MeineView(QGraphicsScene*);

	signals:
	void resized();
	void zoomInSignal();
	void zoomOutSignal();
	};

#endif // MEINEVIEW_H
