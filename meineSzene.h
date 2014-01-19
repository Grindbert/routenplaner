#ifndef MEINESZENE_H
#define MEINESZENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MeineSzene : public QGraphicsScene
	{
	Q_OBJECT

	public:
    MeineSzene();
	MeineSzene(QGraphicsScene);

	signals:
	void rechteMaustaste(QPointF);
	void linkeMaustasteGedruckt(bool, QPointF);
	void linkeMaustasteLoslassen(bool, QPointF);

	private slots:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	};

#endif // MEINESZENE_H
