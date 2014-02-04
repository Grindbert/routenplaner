#include<iostream>

#include"Knoten.h"

//printet alle Informationen zum Knoten auf die Standardausgabe
//(war nützlich, um Fehler zu finden, wird jetzt aber nicht mehr verwendet)
void Knoten::print()
	{
	std::cout<<"Nummer: "<<nummer<<"\nx-Koordinate: "<<x<<"\ny-Koordinate: "<<y<<"\n";
	for(unsigned int i = 0; i<nachbarn.size(); i++)
		{
		nachbarn[i].printKante();
		}
	std::cout<<"\n";
	}

//printet die Kante des Knotens:
void Kante::printKante()
	{
	std::cout<<"Zielknoten: "<<((*ziel).nummer)<<"\tLaenge: "<<laenge<<"\n";
	}

//fügt der Liste der ausgehenden Kanten des Knotens eine neue Kante hinzu:
void Knoten::kanteHinzufuegen(Knoten *endknoten, float kantenlaenge)
	{
	static Kante neu;	//augenscheinlich minimal schneller als Kante *neu = bla;...;delete neu;
	neu.setzeKante(endknoten, kantenlaenge);
	nachbarn.push_back(neu);
	//delete neu;
	}

//setzt die Variablen einer Kante neu.
void Kante::setzeKante(Knoten *knoten, float abstand)
	{
	ziel=knoten;
	laenge=abstand;
	}

//setzt die Variablen eines Knotens neu. Sinnvoll, wenn man einen leeren Knoten
//angelegt hat, und ihn dann mit Informationen füllen will.
void Knoten::setzeKoord(float xk,float yk,int n)
	{
	x=xk;
	y=yk;
	nummer=n;
	}
