// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#include "Planet.h"
#include "Counter.h"

using namespace std;

Planet::Planet(string name, double positionX, double positionY, int population, string nation, double fuelPrice)
{
	this->name = name;
	this->positionX = positionX;
	this->positionY = positionY;
	this->population = population;
	this->nation = nation;
	this->fuelPrice = fuelPrice;

	Counter::addConstrutor();
}

Planet::~Planet()
{
	Counter::addDestructor();
}

ostream& operator<<(ostream& output, Planet planet)
{
	output << "----- Planète " << planet.getName() << " -----" << endl
		<< "Coordonnées (x,y): " << planet.getPositionX() << ", " << planet.getPositionY() << endl
		<< "Population: " << planet.getPopulation() << endl
		<< "Nation: " << planet.getNation() << endl
		<< "Prix du carburant/unite distance: " << planet.getFuelPrice() << endl << endl;

	return output;
}