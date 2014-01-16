#include<vector>

#ifndef __KNOTEN_H
#define __KNOTEN_H

class Knoten;
class Kante;


class Knoten
	{
	public:
	unsigned int nummer;
	float x;
	float y;
	
	std::vector<Kante> nachbarn;
	
	void print();
	void kanteHinzufuegen(Knoten*, float);
	void setzeKoord(float, float, int);
	
	Knoten(float a, float b, unsigned int n)
		{
		x=a;
		y=b;
		nummer=n;
		}
	
	Knoten()
		{}
	
	~Knoten()
		{}
	};


class Kante
	{
	public:
	Knoten *ziel;
	float laenge;
	
	public:
	void printKante();
	void setzeKante(Knoten*, float);
	
	Kante(Knoten *z, float l)
		{
		ziel=z;
		laenge=l;
		}
	
	Kante()
		{}
	
	~Kante()
		{}
	};



#endif
