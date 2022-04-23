// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : Andr� Alano, Audrey B�dard et Laurie-Ann Boily

#include "Archivist.h"
#include "Counter.h"

using namespace std;

Archivist::Archivist()
{
	this->planetList = new vector<Planet*>();
	this->shipList = new vector<Spaceship*>();

	Counter::addConstrutor();
}

Archivist::~Archivist()
{
	for (int i = 0; i < planetList->size() ; i++)
		delete planetList->at(i);

	for (int i = 0; i < shipList->size(); i++)
		delete shipList->at(i);
	
	delete planetList;
	delete shipList;

	Counter::addDestructor();
}

void Archivist::addPlanet(string name, double positionX, double positionY, int population, string nation, double fuelPrice)
{
	vector<Planet*>::iterator iterPlanet;
	Planet* currentElement = nullptr;

	for (iterPlanet = planetList->begin(); iterPlanet != planetList->end(); iterPlanet++)
	{
		// R�cup�rer l'�l�ment point�
		currentElement = *iterPlanet;

		if (currentElement->getName() == name)
		{
			cout << "Plan�te " << name << " non ajout�e. Il y a d�j� une plan�te du m�me nom." << endl;
			return;
		}
		if (currentElement->getPositionX() == positionX && currentElement->getPositionY() == positionY)
		{
			cout << "Plan�te " << name << " non ajout�e. Il y a d�j� une plan�te � ces coordonn�es." << endl;
			return;
		}
	}

	(*planetList).push_back(new Planet(name, positionX, positionY, population, nation, fuelPrice));
}

void Archivist::addSpaceship(string model, double fuelCapacity)
{
	vector<Spaceship*>::iterator iterShip;
	Spaceship* currentElement = nullptr;

	for (iterShip = shipList->begin(); iterShip != shipList->end(); iterShip++)
	{
		currentElement = *iterShip;

		if (currentElement->getModel() == model && currentElement->getFuelCapacity() == fuelCapacity)
		{
			cout << "Vaisseau " << model << " non ajout�. Ce vaisseau est d�j� sur la liste" << endl;
			return;
		}
	}
	(*shipList).push_back(new Spaceship(model, fuelCapacity));
}

Planet* Archivist::findPlanet(std::string planetName)
{
	vector<Planet*>::iterator iterPlanet;
	Planet* currentElement = nullptr;

	for (iterPlanet = planetList->begin(); iterPlanet != planetList->end(); iterPlanet++)
	{
		// R�cup�rer l'�l�ment point�
		currentElement = *iterPlanet;

		if (currentElement->getName() == planetName)
		{
			return currentElement;
		}
	}

	return nullptr;
	cout << "La plan�te " << planetName << " ne fait pas partie de la liste!" << endl;
}

Spaceship* Archivist::findSpaceship(string shipModel)
{
	
	for (int i = 0; i < shipList->size(); i++)
		if (shipList->at(i)->getModel() == shipModel)
			return shipList->at(i);

	return nullptr;
	cout << "Le vaisseau " << shipModel << " ne fait pas partie de la liste!" << endl;
}

void Archivist::showPlanets()
{
	vector<Planet*>::iterator iterPlanet;
	Planet* currentElement = nullptr;

	for (iterPlanet = planetList->begin(); iterPlanet != planetList->end(); iterPlanet++)
	{
		// R�cup�rer l'�l�ment point�
		currentElement = *iterPlanet;
		cout << currentElement->toString();
	}
}

void Archivist::showSpaceships()
{
	vector<Spaceship*>::iterator iterShip;
	Spaceship* currentElement = nullptr;

	for (iterShip = shipList->begin(); iterShip != shipList->end(); iterShip++)
	{
		currentElement = *iterShip;
		cout << currentElement->toString();
	}
}