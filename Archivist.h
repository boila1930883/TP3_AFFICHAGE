// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Planet.h"
#include "Spaceship.h"

class Archivist
{
public:
	Archivist();
	~Archivist();

	std::vector<Planet*>* getPlanetList() { return planetList; }
	std::vector<Spaceship*>* getShipList() { return shipList; }

	void addPlanet(std::string name, double positionX, double positionY, int population, std::string nation, double fuelPrice);
	void addSpaceship(std::string model, double fuelCapacity);

	Planet* findPlanet(std::string planetName);
	Spaceship* findSpaceship(std::string shipModel);

	void showPlanets();
	void showSpaceships();

private:
	std::vector<Planet*>* planetList;
	std::vector<Spaceship*>* shipList;
};

