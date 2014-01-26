#include "meineView.h"

MeineView::MeineView(QGraphicsScene* scene) : QGraphicsView(scene)
{}

/*void MeineView::wheelEvent(QWheelEvent* event)
	{
	if(event->delta()>0)
		{
		emit zoomInSignal();
		}
	else if(event->delta()<0)
		{
		emit zoomOutSignal();
		}
	}*/

