#include<vector>
#include<iostream>
#include<queue>		//für die Priority-Queue
#include<limits>

#include"Wegfindung.h"
#include"Knoten.h"

struct vergleichen
		{
		bool operator () (const std::pair<Knoten*,float> &a, const std::pair<Knoten*,float> &b)
			{
			return(a.second>b.second);
			}
		};

std::vector<int> Wegfindung(std::vector<Knoten> *knotenvek, unsigned int start, unsigned int ziel, bool *gibtWeg)
	{
//Vorbereitungen:
	std::vector<int> ergebnis;
	
	//maximaler Abstand, den "float" erlaubt:
	float max = std::numeric_limits<float>::max();
	
	//Priority-Queue definieren:
	std::priority_queue<std::pair<Knoten*,float>, std::vector<std::pair<Knoten*,float> >, vergleichen> queue;
	
	std::vector<bool> besucht((*knotenvek).size(),false);
	std::vector<float> abstand((*knotenvek).size(),max);
	std::vector<Knoten*> vorganger((*knotenvek).size());
	Knoten *aktuellerKnoten = new Knoten();
	float aktuellerAbstand = 0;
	unsigned int nachbarnummer = 0;
	
//Algorithmus:
	
	abstand[start]=0;
	
	queue.push(std::make_pair(&((*knotenvek)[start]),0));
	
	while(!queue.empty())
		{
		aktuellerKnoten=queue.top().first;
		aktuellerAbstand=queue.top().second;
		queue.pop();
		
		if(besucht[aktuellerKnoten -> nummer]) {continue;}
		
		for(unsigned int i = 0; i<(aktuellerKnoten -> nachbarn).size(); i++)
			{
			nachbarnummer = ((aktuellerKnoten -> nachbarn)[i].ziel) -> nummer;
			
			if(aktuellerAbstand+(aktuellerKnoten -> nachbarn)[i].laenge < abstand[nachbarnummer])
				{
				abstand[nachbarnummer] = aktuellerAbstand+(aktuellerKnoten -> nachbarn)[i].laenge;
				vorganger[nachbarnummer] = aktuellerKnoten;
				queue.push(std::make_pair(&((*knotenvek)[nachbarnummer]),abstand[nachbarnummer]));
				}
			}
		
		besucht[aktuellerKnoten -> nummer] = true;
		
		if((aktuellerKnoten -> nummer)==ziel){break;}
		}
	*gibtWeg = besucht[ziel];
	
	std::cout<<abstand[ziel]<<std::endl;
	
	if(*gibtWeg)
		{
		ergebnis.push_back(ziel);
	
		while(ziel!=start)
			{
			ziel=(vorganger[ziel]) -> nummer;
			ergebnis.push_back(ziel);
			}
		}
	else
		{
		std::cerr<<"Leider gibt es keinen gültigen Weg!\n";
		}
	
	return(ergebnis);
	
	std::cout<<"\n\n";
	}
