#include "meineView.h"

MeineView::MeineView(QGraphicsScene* scene) : QGraphicsView(scene)
{}

void MeineView::resizeEvent(QResizeEvent *event)
	{
	emit resized();
	}
