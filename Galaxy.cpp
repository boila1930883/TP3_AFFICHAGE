// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#include <vector>
#include <string>
#include <iostream>
#include "Galaxy.h"
#include "Planet.h"
#include "WarScript.h"
#include "Counter.h"

// ============== Constructeur et destructeur ==============
Galaxy::Galaxy() 
{
	planetsList = new std::vector<Planet*>();
	warScripts = new std::vector<WarScript*>();
	galaxyDistances = nullptr;
	galaxyGasFees = nullptr;
	galaxyCreated = false;

	Counter::addConstrutor();
}

Galaxy::Galaxy(std::vector<Planet*>* planetList)
{
	this->planetsList = planetList;
	warScripts = new std::vector<WarScript*>();
	galaxyDistances = nullptr;
	galaxyGasFees = nullptr;
	galaxyCreated = false;
	
	Counter::addConstrutor();
}

Galaxy::~Galaxy() {

	Counter::addDestructor();

	for (int i = 0; i < warScripts->size(); i++)
		delete warScripts->at(i);


	delete warScripts;
	delete galaxyDistances;
	delete galaxyGasFees;
}


// ============== Acces aux matrices // Type : 0 -> distance, 1 -> gasfees ==============

double* Galaxy::GetMatrixX(bool type) {
	if (this->galaxyCreated == false) {
		std::cout << "Galaxie inexistante";
		return nullptr;
	}

	if (type)
		return galaxyGasFees;
	return galaxyDistances;
}
double Galaxy::getXBetween2Planets(Planet* a, Planet* b, bool type) {
	return this->getXBetween2Planets(this->GetPlanetId(a), this->GetPlanetId(b), type);
}
double Galaxy::getXBetween2Planets(int a, int b, bool type) {
	if (galaxyCreated == false) {
		std::cout << "Galaxie inexistante";
		return -1;
	}

	if (type)
		return this->galaxyGasFees[a * this->planetsList->size() + b];
	return this->galaxyDistances[a * this->planetsList->size() + b];
}


// ============== Acces aux planetes ==============
int Galaxy::GetPlanetId(Planet* a) {
	for (int i = 0; i < planetsList->size(); i++) {
		if (planetsList->at(i) == a)
			return i;
	}

	return -1;
}

std::vector<Planet*>* Galaxy::getPlanetsList() { return this->planetsList;}

bool Galaxy::AddPlanet(Planet* newPlanet) {

	for (int i = 0; i < planetsList->size(); i++)
		if (planetsList->at(i)->getPositionX() == newPlanet->getPositionX() && planetsList->at(i)->getPositionY() == newPlanet->getPositionY()) {
			std::cout << "Une planete habite deja ces coordonnees -> " << newPlanet->toString() << std::endl;
			return false;
		}

	this->planetsList->push_back(newPlanet);
	return true;
}

// ============== Controles des scenerios de guerre ==============
bool Galaxy::AddWarScript(std::string nation1, std::string nation2) {	// Retourne 1 si le scenario a bien ete ajoute, 0 sinon
	bool areTheyAlreadyAtWar = false;

	for (int i = 0; i < warScripts->size(); i++) {
		if (warScripts->at(i)->AreTheyAtWar(nation1, nation2)) {
			std::cout << "Une guerre entre ces deux nations est deja declaree ! : " << warScripts->at(i)->ToString() << std::endl;
			return false;
		}
	}

	this->warScripts->push_back(new WarScript(nation1, nation2));

	// On scan pour retirer tous les chemins des planetes de la nation 1 vers la nation 2
	
	this->removePathsFromNationAToNationB(nation1, nation2);

	// On scan pour retirer tous les chemins des planetes de la nation 2 vers la nation 1
	this->removePathsFromNationAToNationB(nation2, nation1);
	

	return true;
}

void Galaxy::removePathsFromNationAToNationB(std::string nationA, std::string nationB) {
	for (int i = 0; i < this->planetsList->size(); i++)
		if (this->planetsList->at(i)->getNation() == nationA)
			for (int j = 0; j < this->planetsList->size(); j++)
				if (this->planetsList->at(j)->getNation() == nationB) {
					galaxyDistances[i * this->planetsList->size() + j] = -1;
					galaxyGasFees[i * this->planetsList->size() + j] = -1;
				}
}

bool Galaxy::RemoveWarScript(std::string nation1, std::string nation2) {	// Retourne 1 si le scenaria a bien ete retire, 0 sinon
		WarScript* warScriptToDelete = nullptr;

	for (int i = 0; i < warScripts->size(); i++) {
		if (warScripts->at(i)->AreTheyAtWar(nation1, nation2)) {
			warScriptToDelete = warScripts->at(i);
			warScripts->erase(warScripts->begin() + i);

			for (int i = 0; i < this->planetsList->size(); i++) {
				if (this->planetsList->at(i)->getNation() == nation1 || this->planetsList->at(i)->getNation() == nation2)
					for (int j = 0; j < this->planetsList->size(); j++)
						if (galaxyDistances[i * this->planetsList->size() + j] == -1) {
							galaxyDistances[i * this->planetsList->size() + j] = CalculateDistanceBetween2Planets (this->planetsList->at(i), this->planetsList->at(j));
							galaxyGasFees[i * this->planetsList->size() + j] = galaxyDistances[i * this->planetsList->size() + j] * this->planetsList->at(i)->getFuelPrice();
						}
			}

			delete warScriptToDelete;
			return true;
		}
	}
	std::cout << "Les nations " << nation1 << " et " << nation2 << " ne sont pas en guerre." << std::endl;
	return false;
}

// ============== Gestion de l'init et du reset des graphes de planetes ==============

void Galaxy::deleteGalaxy() {
	galaxyCreated = false;

	// On delete la matrice pour pouvoir la recreer a la bonne taille
	delete galaxyDistances;
	delete galaxyGasFees;
}

void Galaxy::CreateGalaxy() {											// Genere la matrice des planetes
	if (galaxyCreated == true) {
		std::cout << "Erreur, une galaxie a deja ete cree, pour regenerer un nouveau systeme, il faut d'abord supprimer l'ancien" << std::endl;
		return;
	}

	galaxyCreated = true;

	galaxyDistances = new double[planetsList->size() * planetsList->size()];
	galaxyGasFees = new double[planetsList->size() * planetsList->size()];

	for (int i = 0; i < planetsList->size(); i++)
		for (int j = 0; j < planetsList->size(); j++) {
			galaxyDistances[i * planetsList->size() + j] = CalculateDistanceBetween2Planets(planetsList->at(i), planetsList->at(j));
			galaxyGasFees[i * planetsList->size() + j] = this->galaxyDistances[i * planetsList->size() + j] * planetsList->at(i)->getFuelPrice();
		}

	std::cout << "Galaxie créée!" << std::endl;
}

// ============== toString ==============

std::string Galaxy::PlanetsListToString() {

	if (planetsList == nullptr)
		return "Liste de planete vide";

	std::string strList = "Liste des planetes : \n";

	for (int i = 0; i < this->planetsList->size(); i++)
		strList += "ID : " + std::to_string(i) + "\n\n" + planetsList->at(i)->toString();

	return strList;
}

// ============== Fonctions utilitees ==============

// Renvoie la distance entre les planetes a et b (pytagore)
double Galaxy::CalculateDistanceBetween2Planets(Planet* a, Planet* b) {
		return (std::sqrt(std::pow(a->getPositionX() - b->getPositionX(), 2) + std::pow(a->getPositionY() - b->getPositionY(), 2)));
}