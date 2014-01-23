#include "meineSzene.h"

MeineSzene::MeineSzene() : QGraphicsScene()
{
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
		QPointF startpunkt=QCursor::pos();//event->scenePos();
		emit linkeMaustasteGedruckt(true, startpunkt);
		}
	}


void MeineSzene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
	{
	if(event->button()==Qt::LeftButton)
		{
		QPointF endpunkt=QCursor::pos();//event->scenePos();
		emit linkeMaustasteLoslassen(false, endpunkt);
		}
	}


//19. 02. 2014 15:30Uhr
