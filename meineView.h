#ifndef MEINEVIEW_H
#define MEINEVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

#include "meineSzene.h"


class MeineView : public QGraphicsView
	{
	Q_OBJECT

	public:
	MeineView(QGraphicsScene*);

	private:
	void resizeEvent(QResizeEvent*);

	signals:
	void resized();
	//void zoomInSignal();
	//void zoomOutSignal();
	};

#endif // MEINEVIEW_H
