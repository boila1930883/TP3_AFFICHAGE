// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : Andr� Alano, Audrey B�dard et Laurie-Ann Boily

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
		<< "   Mod�le: " << ship.getModel() << endl
		<< "   Capacit� de carburant: " << ship.getFuelCapacity() << endl << endl;	

	return output;
}