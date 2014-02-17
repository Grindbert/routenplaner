#include "hilfewidget.h"

Hilfewidget::Hilfewidget(QWidget *parent) : QWidget(parent)
	{
	ok = new QPushButton("OK");

	QString hilfe;
	hilfe="Willkommen im Hilfefenster!\n\nGrößtenteils sollte das Programm ja selbsterklärend sein,\nda Sie sich aber dennoch die Mühe gemacht haben, das\nHilfefenster zu öffnen, hier noch ein paar erklärende Worte:\n\nIn der linken Leiste sind einige Buttons zu finden.\nDie, auf denen N,S,O und W steht, sind für die Bewegung\nüber die Karte zuständig. Dabei stehen die Buchstaben\nfür die Himmelsrichtung, in die sich bewegt wird.\n\nDie Buttons mit + und - sind zum Zoomen. + holt die\nKarte näher heran, - zeigt einen größeren Kartenausschnitt.\n\nDarunter sind einige Informationstexte, die einem die\naktuelle Position des Mauszeigers auf der Karte in Längen-\nund Breitengraden, und die Koordinaten des gewählten\nStart- und Zielpunktes anzeigen.\n\nDesweiteren bietet das Programm auch die Möglichkeiten,\nmit der Maus über die Karte zu navigieren. Zum Bewegen kann\ndas Drag&Drop-Prinzip genutzt werden, und die Karte einfach\nan die gewünschte Stelle gezogen werden.\nDasZoomen funktioniert auch mit dem Mausrad.\n\nZum Eingeben des Start oder Zielpunktes wird einfach ein\nRechtsklick auf die Karte gemacht, und im auftauchenden\nMenü die gewünschte Option ausgewählt.\n\nUm die Route dann zu berechnen, wird oben in der Menüleiste\nder Punkt \"Route\" ausgewählt und auf \"Route berechnen\"\ngeklickt. Es können beliebig viele Routen eingezeichnet\nwerden. Unter \"Route\"->\"eingezeichnete Routen löschen\"\nkönnen die eingezeichneten Routen wieder aus der Karte\nentfernt werden.";

	text = new QLabel(hilfe);

	//ok->setMaximumWidth(120);
	ok->setFont(QFont("Helvetica", 16, QFont::Normal));

	QGraphicsScene *szene = new QGraphicsScene();
	szene->addText(hilfe);

	QGraphicsView *view = new QGraphicsView(szene);

	grid = new QGridLayout(this);

	//grid->addWidget(text,0,0);
	grid->addWidget(view,0,0);
	grid->addWidget(ok,1,0);

	setLayout(grid);
	}


QPushButton* Hilfewidget::getOK()
	{
	return(ok);
	}
