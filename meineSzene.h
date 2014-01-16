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

	private slots:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	};

#endif // MEINESZENE_H
