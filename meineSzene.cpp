#include "meineSzene.h"


MeineSzene::MeineSzene() : QGraphicsScene()
{
}


//wenn die Maus über die Szene bewegt wird, soll ihr aktueller Punkt weitergegeben
//werden, sodass die Längen- und Breitengrade im Mainwindow aktualisiert werden können:
void MeineSzene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
	{
	QPointF punkt=event->scenePos();
	emit mausBewegt(punkt);
	}


//Wenn Maustasten gedrückt wurden, sollen entsprechende Signale gesendet werden:
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


//das Loslassen der linken Maustaste ist für das Ziehen der Karte wichtig, daher
//soll auch bei diesem Event ein Signal ausgesendet werden:
void MeineSzene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
	{
	if(event->button()==Qt::LeftButton)
		{
		QPointF endpunkt=QCursor::pos();
		emit linkeMaustasteLoslassen(false, endpunkt);
		}
	}


//Das wheelEvent soll zum Zoomen genutzt werden, daher sollen je nach Drehrichtung
//des Mausrades entsprechende Signale ausgesendet werden soll:
void MeineSzene::wheelEvent(QGraphicsSceneWheelEvent *event)
	{
	//(delta ist eine Variable des wheelEvents, das angibt, in welche Richtung das
	//Mausrad gedreht wurde)
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
