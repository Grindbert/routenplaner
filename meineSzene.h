#ifndef MEINESZENE_H
#define MEINESZENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include "funktionen.h"

class MeineSzene : public QGraphicsScene
	{
	Q_OBJECT

	public:
	MeineSzene();
	MeineSzene(QGraphicsScene);

	private:
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void wheelEvent(QGraphicsSceneWheelEvent*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

	signals:
	void zoomInSignal(QPointF);
	void zoomOutSignal(QPointF);
	void rechteMaustaste(QPointF);
	void linkeMaustasteGedruckt(bool, QPointF);
	void linkeMaustasteLoslassen(bool, QPointF);
	void mausBewegt(QPointF);
	};

#endif // MEINESZENE_H
