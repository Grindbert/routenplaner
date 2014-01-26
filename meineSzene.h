#ifndef MEINESZENE_H
#define MEINESZENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include "funktionen.h"

class MeineSzene : public QGraphicsScene
	{
	Q_OBJECT

	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void wheelEvent(QGraphicsSceneWheelEvent*);

	public:
    MeineSzene();
	MeineSzene(QGraphicsScene);

	signals:
	void zoomInSignal(QPointF);
	void zoomOutSignal(QPointF);
	void rechteMaustaste(QPointF);
	void linkeMaustasteGedruckt(bool, QPointF);
	void linkeMaustasteLoslassen(bool, QPointF);
	void mausBewegt(QPointF);

	private slots:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	};

#endif // MEINESZENE_H
