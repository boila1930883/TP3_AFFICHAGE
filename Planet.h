// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#pragma once

#include <string>
#include <iostream>

class Planet
{
public:
	Planet(std::string name, double positionX, double positionY, int population, std::string nation, double fuelPrice);
	~Planet();

	std::string getName() { return name; }
	int getPositionX() { return positionX; }
	int getPositionY() { return positionY; }
	int getPopulation() { return population; }
	std::string getNation() { return nation; }
	double getFuelPrice() { return fuelPrice; }
	bool visited() { return vis; };
	void visit() { vis = true; }
	void unvisit() { vis = false; }

	std::string toString () {return "----- Planète " + this->getName() + " -----" + "\n" +
		 "Coordonnées (x,y): " + std::to_string(this->getPositionX())  +", " + std::to_string(this->getPositionY()) + "\n" +
		 "Population: " + std::to_string(this->getPopulation()) + "\n" +
		 "Nation: " + this->getNation() + " \n" +
		 "Prix du carburant/unite distance: " + std::to_string(this->getFuelPrice()) + "\n\n";
	}
	friend std::ostream& operator<<(std::ostream& output, Planet planet);

private:
	bool vis = false;
	std::string name;
	int positionX;
	int positionY;
	int population;
	std::string nation;
	double fuelPrice;
};