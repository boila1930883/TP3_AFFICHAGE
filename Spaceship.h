// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : Andr� Alano, Audrey B�dard et Laurie-Ann Boily

#pragma once

#include <string>
#include <iostream>

class Spaceship
{
public:
	Spaceship(std::string model, double fuelCapacity);
	~Spaceship();

	std::string getModel() { return model; }
	double getFuelCapacity() { return fuelCapacity; }

	std::string toString() {
		return "Vaisseau spatial\n   Mod�le: " + this->getModel() +
			   "   Capacit� de carburant: " + std::to_string (this->getFuelCapacity()) + "\n\n";
	}

	friend std::ostream& operator<<(std::ostream& output, Spaceship ship);

private:
	std::string model;
	double fuelCapacity;
};