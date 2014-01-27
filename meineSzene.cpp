#include "meineSzene.h"


MeineSzene::MeineSzene() : QGraphicsScene()
{
}


void MeineSzene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
	{
	QPointF punkt=event->scenePos();
	emit mausBewegt(punkt);
	}


void MeineSzene::mousePressEvent(QGraphicsSceneMouseEvent *event)
	{
	if((event->button())==Qt::RightButton)
		{
		QPointF punkt=event->scenePos();
		emit rechteMaustaste(punkt);
		}
	if(event->button()==Qt::LeftButton)
		{
		QPointF startpunkt=QCursor::pos();
		emit linkeMaustasteGedruckt(true, startpunkt);
		}
	}


void MeineSzene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
	{
	if(event->button()==Qt::LeftButton)
		{
		QPointF endpunkt=QCursor::pos();
		emit linkeMaustasteLoslassen(false, endpunkt);
		}
	}


void MeineSzene::wheelEvent(QGraphicsSceneWheelEvent *event)
	{
	if(event->delta()>0)
		{
		emit zoomInSignal(event->scenePos());
		}
	else if(event->delta()<0)
		{
		emit zoomOutSignal(event->scenePos());
		}
	}


//19. 02. 2014 15:30Uhr
