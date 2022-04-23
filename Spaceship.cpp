// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#include "Spaceship.h"
#include "Counter.h"

using namespace std;

Spaceship::Spaceship(string model, double fuelCapacity)
{
	this->model = model;
	this->fuelCapacity = fuelCapacity;

	Counter::addConstrutor();
}

Spaceship::~Spaceship()
{
	Counter::addDestructor();
}

ostream& operator<<(ostream& output, Spaceship ship)
{
	output << "Vaisseau spatial" << endl
		<< "   Modèle: " << ship.getModel() << endl
		<< "   Capacité de carburant: " << ship.getFuelCapacity() << endl << endl;	

	return output;
}