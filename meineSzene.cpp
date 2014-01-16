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
	}
