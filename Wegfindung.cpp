#include"Wegfindung.h"

struct vergleichen
		{
		bool operator () (const std::pair<Knoten*,float> &a, const std::pair<Knoten*,float> &b)
			{
			return(a.second>b.second);
			}
		};

std::vector<int> Wegfindung(std::vector<Knoten> *knotenvek, QPointF startpkt, QPointF zielpkt, bool *gibtWeg, float *routenlaenge)
	{
//Vorbereitungen:
	std::vector<int> ergebnis;	//enthält am Ende die Nummern der Knoten der Route
	
	//maximaler Abstand, den "float" erlaubt:
	float max = std::numeric_limits<float>::max();
	
	//Priority-Queue definieren:
	std::priority_queue<std::pair<Knoten*,float>, std::vector<std::pair<Knoten*,float> >, vergleichen> queue;
	
	//man will sich merken, welche Knoten schon fertig sind:
	//(ein Vektor mit der gleichen Länge wie der Knotenvektor wird angelegt,
	//wobei jeder Eintrag am Anfang false ist)
	std::vector<bool> besucht(knotenvek->size(),false);

	//Zu jeden Knoten wollen wir uns auch den derzeit minimalen Abstand merken:
	//(es wird wieder ein Vektor mit der gleichen Länge wie der Knotenvektor
	//angelegt, die Werte werden alle auf den mit float maximal möglichen Abstand
	//gesetzt (der ist so groß, dass die Abstände durchaus in Zentimeter seien
	//dürften, und man dennoch mehrmals um die Welt gehen kann, ohne, dass die
	//Variable überläuft (daher kein double, float reicht auch und verbraucht
	//weniger Speicherplatz)))
	std::vector<float> abstand((*knotenvek).size(),max);

	//speichert zu jeden Knoten den Vorgänger, von dem die für ihn momentan optimale
	//kommt. Unbedingt notwendig, um am Ende die fertige Route erstellen zu können.
	std::vector<Knoten*> vorganger((*knotenvek).size());

	//aktueller Knoten, der gerade vom Algorithmus bearbeitet wird.
	Knoten *aktuellerKnoten = new Knoten();

	//zum Zwischenspeichern von Daten:
	float aktuellerAbstand = 0;
	unsigned int nachbarnummer = 0;


//Nummer von Start- und Zielpunkt suchen, die den vom Benutz eingegebenen
	//Koordinaten am nächsten kommen:

	//die minimalen Distanzen von Start- und Zielknoten werden zunächst auf die
	//Distanz zum Knoten mit der Nummer 0 im Graphen gesetzt:
	double minDistS=sqrt(pow((*knotenvek)[0].x-startpkt.x(),2)+pow((*knotenvek)[0].y-startpkt.y(),2));
	double minDistZ=sqrt(pow((*knotenvek)[0].x-zielpkt.x(),2)+pow((*knotenvek)[0].y-zielpkt.y(),2));

	//dementsprechend werden die Nummern der Kandidaten für Start- und Zielpunkt
	//zunächst auch auf die Nummer 0 gesetzt:
	int startnummer = 0;
	int zielnummer=0;

	//jetzt werden alle Knoten beginnend bei der Nummer 1 durchgegangen, und es wird
	//geprüft, ob es nicht einen Knoten gibt, der den vom Nutzer ausgewählten
	//Koordinaten näher kommt:
	for(unsigned int i=1;i<knotenvek->size();i++)
		{
		//prüfe aktuellen Punkt, ob er nicht ein besserer Startpunkt wäre:
		if(minDistS>sqrt(pow((*knotenvek)[i].x-startpkt.x(),2)+pow((*knotenvek)[i].y-startpkt.y(),2)))
			{
			//wenn ja, korrigiere die minimale Distanz und merke dir die Startnummer:
			minDistS=sqrt(pow((*knotenvek)[i].x-startpkt.x(),2)+pow((*knotenvek)[i].y-startpkt.y(),2));
			startnummer=(*knotenvek)[i].nummer;
			}

		//das gleiche für den Zielpunkt:
		if(minDistZ>sqrt(pow((*knotenvek)[i].x-zielpkt.x(),2)+pow((*knotenvek)[i].y-zielpkt.y(),2)))
			{
			minDistZ=sqrt(pow((*knotenvek)[i].x-zielpkt.x(),2)+pow((*knotenvek)[i].y-zielpkt.y(),2));
			zielnummer=(*knotenvek)[i].nummer;
			}
		}

	//Wenn alle Knoten des Graphen durchgegangen wurden, werden die Nummern der
	//besten Punkte gespeichert und dem Algorithmus als Start- und Zielpunkt
	//übergeben:
	unsigned int start=startnummer;
	unsigned int ziel=zielnummer;

//Algorithmus:
	
	//Abstand des Startknotens zu sich selbst ist 0:
	abstand[start]=0;
	
	//Startpunkt als erstes Element in die Queue tun:
	queue.push(std::make_pair(&((*knotenvek)[start]),0));
	
	//solange noch Elemente in der Queue sind, mache mit dem Algorithmus weiter:
	while(!queue.empty())
		{
		//hole dir die Informationen des ersten Knotens der Queue:
		aktuellerKnoten=queue.top().first;
		aktuellerAbstand=queue.top().second;

		//entferne das erste Element aus der Queue:
		queue.pop();
		
		//Wenn der Knoten schon besucht wurde, wurde schon der optimale Abstand
		//gefunden, und wir können mit dem nächsten Knoten weitermachen:
		if(besucht[aktuellerKnoten -> nummer]) {continue;}
		
		//gehe alle Nachbarn des aktuellen Knotens durch:
		for(unsigned int i = 0; i<(aktuellerKnoten -> nachbarn).size(); i++)
			{
			nachbarnummer = ((aktuellerKnoten -> nachbarn)[i].ziel) -> nummer;
			
			//Wenn der Abstand vom aktuellen Knoten + die Kantenlänge vom aktuellen
			//Knoten zum derzeitigen Nachbarknoten geringer ist, als der Abstand,
			//den der Nachbarknoten im Moment hat, wurde offensichtlich ein besserer
			//Weg gefunden:
			if(aktuellerAbstand+(aktuellerKnoten -> nachbarn)[i].laenge < abstand[nachbarnummer])
				{
				//wir korrigieren also den Abstand...
				abstand[nachbarnummer] = aktuellerAbstand+(aktuellerKnoten -> nachbarn)[i].laenge;
				vorganger[nachbarnummer] = aktuellerKnoten;	//... den Vorgänger...
				//... und machen einen neuen Eintrag in der Queue, da sich der
				//Abstand des Nachbarknotens ja jetzt geändert hat:
				queue.push(std::make_pair(&((*knotenvek)[nachbarnummer]),abstand[nachbarnummer]));
				}
			}
		
		//nachdem wir alle Nachbarknoten überprüft haben, sind wir mit dem aktuellen
		//Knoten fertig, wir können also den "besucht"-Eintrag auf true setzen:
		besucht[aktuellerKnoten -> nummer] = true;
		
		//Wenn der Knoten, den wir gerade bearbeitet haben, schon unser gewünschter
		//Zielknoten ist, können wir aufhören.
		if((aktuellerKnoten -> nummer)==ziel){break;}
		}

	//Wenn wir jeden Knoten einmal durchgegangen sind (oder früher aufgehört haben,
	//weil wir unseren Zielknoten erreicht haben), können wir feststellen, ob wir
	//einen Weg gefunden haben, oder nicht, indem wir schauen, ob wir den Zielknoten
	//auch besucht haben (denn für alle Knoten, die wir besucht haben, wurde auch
	//ein optimaler Abstand gefunden:
	*gibtWeg = besucht[ziel];

	//speichere die Länge der Route:
	//(wenn keine Route gefunden wurde, wird der startwert "max" zurückgegeben)
	*routenlaenge = abstand[ziel];
	
	//Wenn es einen Weg gibt, wird er aus dem "vorganger"-Vektor rekonstruiert:
	if(*gibtWeg)
		{
		//starte mit der Nummer des Zielknotens:
		ergebnis.push_back(ziel);

		//solange wir nicht beim Startknoten angekommen sind, wird jeweils der
		//Vorgänger des Knotens in den ergebnis-Vektor gepusht:
		while(ziel!=start)
			{
			ziel=(vorganger[ziel]) -> nummer;
			ergebnis.push_back(ziel);
			}
		}
	
	return(ergebnis);
	}
