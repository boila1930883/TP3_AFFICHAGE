// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#pragma once

#include <vector>
#include <string>
#include "Planet.h"
#include "WarScript.h"

class Galaxy {
	private:
		// Renvoie la distance entre les planetes a et b (pytagore)
		double CalculateDistanceBetween2Planets(Planet* a, Planet* b);
		void removePathsFromNationAToNationB(std::string nationA, std::string nationB);



	/* Matrice de dimension X(X : nb de planetes).Le graphe sera complet (à partir de chaque planete, 
	 on peut se rendre à n'importe quelle autre plaete). Les cases contiendront la distances mesurée par pytagore entre deux planetes.
	*/
		double* galaxyDistances;
		double* galaxyGasFees;
		std::vector<WarScript*> *warScripts;
		bool galaxyCreated;
		std::vector<Planet*> *planetsList;
	public:
		Galaxy();
		Galaxy(std::vector<Planet*>* planetList);
		~Galaxy();

		// Type : 0 -> distance, 1 -> gasfees
		double* GetMatrixX(bool type);
		double getXBetween2Planets(Planet* a, Planet* b, bool type);
		double getXBetween2Planets(int a, int b, bool type);

		bool getGalaxyCreated() { return galaxyCreated; }

		int GetPlanetId(Planet* a);
		bool AddPlanet(Planet* newPlanet);

		std::vector<Planet*>* getPlanetsList();

		bool AddWarScript(std::string nation1, std::string nation2);
		bool RemoveWarScript(std::string nation1, std::string nation2);

		void deleteGalaxy();
		void CreateGalaxy();

		std::string PlanetsListToString();

		int GetMatrixSize() { return this->planetsList->size(); }
		std::vector<WarScript*>* getWarScripts() { return warScripts; }

		void unvisitall() {
			for (int i = 0; i < planetsList->size(); i++) {
				planetsList->at(i)->unvisit();
			}
		}


};