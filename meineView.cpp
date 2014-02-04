#include "meineView.h"

MeineView::MeineView(QGraphicsScene* scene) : QGraphicsView(scene)
{}

//Wenn die Größe der View geändert wird, soll ein Signal ausgesendet werden, damit
//die Szene wieder zentriert werden kann
void MeineView::resizeEvent(QResizeEvent *event)
	{
	emit resized();
	}
