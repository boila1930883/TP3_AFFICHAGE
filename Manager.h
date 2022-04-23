#pragma once

#include <string>
// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#include <fstream>
#include "Archivist.h"
#include "Galaxy.h"
#include "Planet.h"
#include "Spaceship.h"

class Manager {
private:
	Archivist* archive;
	Galaxy* mainGax;
	Spaceship* ship;

	// Fonctions internes
	int indexDuPoidsPlusPetit(std::vector<double>* poids, std::vector<int>* fixedTable);
	bool isIndexFixed(std::vector<int>* fixedTable, int index);
	
public:
	//constructor
	Manager(Archivist* archive);
	Manager(Galaxy* gax, Spaceship* ship, Archivist* archive);
	// destructor
	~Manager();

	// getters
	Galaxy* getGalaxy() { return mainGax; };
	Spaceship* getShip() { return ship; };

	// changer vaiseaux en question
	void changerShip(Spaceship* newship) { if (newship != nullptr) ship = newship; };

	// Lecture des fichiers de vaisseaux et de planètes
	bool loadPlanets(std::string fileName);
	bool loadShips(std::string fileName);

	//Calcul du chemin, returne faux si le vaissaux ne peut pas arriver.
	bool cheminExistant(std::string shipName, std::string startName, std::string endName);

	//	-Calculs du chemin 
	void calChemin(std::string shipName, std::string startName, std::string endName, bool type);

	//generation des Guerres (ajout/enleve)
	void ajoutGuerre(std::string n1, std::string n2);
	void enleverGuerre(std::string n1, std::string n2);

	double* recalGalaxy(bool type);
	bool loopChemin(double* galaxy, Planet* currpla, Planet* end);

	// afficher tous les informations
	void displayAllInformations();
};