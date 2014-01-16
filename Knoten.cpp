#include<iostream>

#include"Knoten.h"

void Knoten::print()
	{
	std::cout<<"Nummer: "<<nummer<<"\nx-Koordinate: "<<x<<"\ny-Koordinate: "<<y<<"\n";
	for(unsigned int i = 0; i<nachbarn.size(); i++)
		{
		nachbarn[i].printKante();
		}
	std::cout<<"\n";
	}

void Knoten::kanteHinzufuegen(Knoten *endknoten, float kantenlaenge)
	{
	static Kante neu;	//augenscheinlich minimal schneller als Kante *neu = bla;...;delete neu;
	neu.setzeKante(endknoten, kantenlaenge);
	nachbarn.push_back(neu);
	//delete neu;
	}

void Knoten::setzeKoord(float xk,float yk,int n)
	{
	x=xk;
	y=yk;
	nummer=n;
	}

void Kante::printKante()
	{
	std::cout<<"Zielknoten: "<<((*ziel).nummer)<<"\tLaenge: "<<laenge<<"\n";
	}

void Kante::setzeKante(Knoten *knoten, float abstand)
	{
	ziel=knoten;
	laenge=abstand;
	}
