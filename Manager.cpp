// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#include "Manager.h"
#include "Counter.h"
#include <stack>
#include "GalaxyPrinter.h"

using namespace std;

Manager::Manager(Galaxy* gax, Spaceship* ship, Archivist* archive)
{
	this->mainGax = gax;
	this->ship = ship;
	this->archive = archive;
	Counter::addConstrutor();
}

Manager::Manager(Archivist* archive)
{
	this->archive = archive;
	this->mainGax = nullptr;

	Counter::addConstrutor();
}

Manager::~Manager() 
{
	delete mainGax;
	delete archive;

	Counter::addDestructor();
}

bool Manager::loadPlanets(string fileName)
{
	ifstream file;
	string name, nation;
	double positionX, positionY, fuelPrice;
	int population;

	if (mainGax != nullptr)
	{
		if (mainGax->getGalaxyCreated())		// Si une galaxie est déjà créée, on doit d'abord la supprimer
		{
			mainGax->deleteGalaxy();
		}
		if (!this->archive->getPlanetList()->empty())		// Si la liste de planètes n'est pas vide, il faut d'abord la vider
		{
			for (int i = 0; i < this->archive->getPlanetList()->size(); i++)
				delete this->archive->getPlanetList()->at(i);

		}
	}
	
	file.open(fileName);
	if (!file.fail())			// Si l'ouverture du fichier a réussie
	{
		cout << "Ouverture et chargement du fichier: " << fileName << endl;

		while (!file.eof())
		{
			file >> name >> positionX >> positionY >> population >> nation >> fuelPrice;
			this->archive->addPlanet(name, positionX, positionY, population, nation, fuelPrice);
		}
		file.close();

		// Création de la galaxie
		this->mainGax = new Galaxy(this->archive->getPlanetList());
		this->mainGax->CreateGalaxy();
		return true;
	}
	else {
		cout << "Erreur à l'ouverture du fichier " << fileName << endl;
	}

	return false;
}

bool Manager::loadShips(string fileName)
{
	ifstream file;
	string model;
	double capacity;

	if (!this->archive->getShipList()->empty())		// Si la liste de vaisseaux n'est pas vide, il faut d'abord la vider
	{
		this->archive->getShipList()->clear();
	}

	file.open(fileName);
	if (!file.fail())			// Si l'ouverture du fichier a réussie
	{
		cout << "Ouverture et chargement du fichier: " << fileName << endl << endl;

		while (!file.eof())
		{
			file >> model >> capacity;
			this->archive->addSpaceship(model, capacity);
		}
		file.close();
		return true;
	}
	else {
		cout << "Erreur à l'ouverture du fichier " << fileName << endl;
	}

	return false;
}

bool Manager::cheminExistant(string shipName, string startName, string endName) 
{
	changerShip(archive->findSpaceship(shipName));
	Planet* start = archive->findPlanet(startName);
	Planet* end = archive->findPlanet(endName);

	if (start == nullptr || end == nullptr || this->ship == nullptr) {

		cout << "Calcul Chemin : Planetes et/ou vaisseaux inexistants.\n";
		return false;
	}

	//recalculate galaxy
	double* newgax = recalGalaxy(false);
	bool exist = loopChemin(newgax, start, end);

	mainGax->unvisitall();

	//loop, return true si chemin trouvé
	return exist;

}

bool Manager::loopChemin(double* galaxy, Planet* currpla, Planet* end) {
	if (currpla == end) {
		return true;
	}
	currpla->visit();

		for (int j = 0; j < mainGax->getPlanetsList()->size(); j++) {
			if (galaxy[mainGax->GetPlanetId(currpla) * mainGax->getPlanetsList()->size() + j] != -1
				&& !mainGax->getPlanetsList()->at(j)->visited())
			{
				return loopChemin(galaxy, mainGax->getPlanetsList()->at(j), end);
			}
		}
	return false;
}

// recalculate galaxy sans chemins impossibles pour le vaisseau. 1 = carburant, 0 = distance (defaul)
double* Manager::recalGalaxy(bool type = 0) {

	double* tempgax = new double[mainGax->GetMatrixSize()* mainGax->GetMatrixSize()];

	for (int i = 0; i < mainGax->GetMatrixSize(); i++)
		for (int j = 0; j < mainGax->GetMatrixSize(); j++)
			if (mainGax->getXBetween2Planets(i, j, false) > ship->getFuelCapacity())
				tempgax[i * mainGax->GetMatrixSize() + j] = -1;
			else
				tempgax[i * mainGax->GetMatrixSize() + j] = mainGax->getXBetween2Planets(i, j, type);

	return tempgax;
}

// Creer chemin. true = 1 = prix, false = 0 = distance
void Manager::calChemin(string shipName, string startName, string endName, bool type, vector<Planet*>* pathPlanet)
{
	changerShip(archive->findSpaceship(shipName));
	Planet* start = archive->findPlanet(startName);
	Planet* end = archive->findPlanet(endName);
	
	if (this->ship == nullptr) {
		cout << "Calcul du chemin : Erreur de type de vaisseaux.\n";
			return;
	}

	if (!cheminExistant(ship->getModel(), startName, endName)) {
		cout << "Requête invalide! Il n'existe pas de chemin possible entre " << startName << " et " << endName << " avec le vaisseau " << ship->getModel() << endl << endl;
		return;
	}

	double* newgax = recalGalaxy(type);

	int sizeTab = mainGax->getPlanetsList()->size();
	int indexMin = mainGax->GetPlanetId(start);

	//list opened et closed
	std::vector<int>* fixed = new vector<int>();

	// poids temporaire
	std::vector<double>* poids = new std::vector<double>(sizeTab);

	// init tab de poids
	for (int counter = 0; counter < poids->size(); counter++) {
		poids->at(counter) = -1;
	}

	// idex parent temporaire
	int* chemin = new int[sizeTab];

	// premier case
	poids->at(indexMin) = 0;
	chemin[indexMin] = indexMin;

	fixed->push_back(mainGax->GetPlanetId(start));

	//trouver tous les distances (pas -1) qui partent de start
	//regarder dans [start][j]
	for (int i = 0; i < sizeTab; i++) {
		if (newgax[indexMin * sizeTab + i] != -1) {
			// MAJ des poids, et le chemin
			poids->at(i) = newgax[indexMin * sizeTab + i];
			chemin[i] = indexMin;
		}
	}

	// tant qu'on a pas trouver le planete final
	while (mainGax->getPlanetsList()->at(fixed->back()) != end ) {

		//trouver index avec poids plus petit dans tableau qui sont pas fixés
		// dans les fixes
		// On recherche dans la table des poids le plus petit parmi ceux non fixés
		indexMin = indexDuPoidsPlusPetit(poids, fixed);

		//chercher [nouvel index][j]
		for (int i = 0; i < sizeTab; i++) {
			// si le nouvel planete a ce arrete, et si la somme des poids est plus petit que le poids d'avant
			if ((newgax[indexMin * sizeTab + i] + poids->at(indexMin) < poids->at(i)
				|| poids->at(i) == -1) && !isIndexFixed (fixed ,i) && newgax[indexMin * sizeTab + i] != -1) {
			//MAJ des poids et chemin
				poids->at(i) = newgax[indexMin * sizeTab + i] + poids->at(indexMin);
				chemin[i] = indexMin;
			}
		}
	//fixer ce index
		fixed->push_back(indexMin);
	//repeter
	}
	if (type) {
		cout << "Le chemin le moins dispendieux entre " << startName << " et " << endName << " avec le vaisseau " << shipName << " coute " << std::to_string(poids->at(mainGax->GetPlanetId(end))) << " et est: " << endl << "     ";
	}
	else {
		cout << "Le Chemin le plus court entre " << startName << " et " << endName << " avec le vaisseau " << shipName << " fait " << std::to_string(poids->at(mainGax->GetPlanetId(end))) << " unites de distance et est: " << endl << "     ";
	}

	int current = mainGax->GetPlanetId(end);
	std::string path = "";
	while (current != mainGax->GetPlanetId(start)) {
		pathPlanet->push_back(mainGax->getPlanetsList()->at(current));
		path = ", " + mainGax->getPlanetsList()->at(current)->getName() + path;
		current = chemin[current];
	}

	pathPlanet->push_back(start);
	path = start->getName() + path + ".";
	cout << path << endl << endl;

	delete newgax;
	delete poids;
	delete fixed;

}

int Manager::indexDuPoidsPlusPetit(std::vector<double>* poids, std::vector<int>* fixedTable) {
	
	int index = -1;
	double poidsMin;


	for (int i = 0; i < poids->size(); i++) {

		if (poids->at(i) == -1 || isIndexFixed(fixedTable, i))
			continue;

		if (index == -1) {
			index = i;
			poidsMin = poids->at(i);
		}
		else if (poidsMin >= poids->at(i)) {
			index = i;
			poidsMin = poids->at(i);
		}
	}

	return index;
}

bool Manager::isIndexFixed(std::vector<int>* fixedTable, int index) {
	
	for (int i = 0; i < fixedTable->size(); i++)
		if (index == fixedTable->at(i))
			return  true;
	return false;
}

void Manager::ajoutGuerre(string n1, string n2)
{
	if (mainGax->AddWarScript(n1, n2)) {
		std::cout << "Guerre declaree entre " + n1 + " et " + n2 << std::endl;
	}
	else {
		std::cout << "Erreur dans l'ajout d'une guerre!" << std::endl;
	}
}

void Manager::enleverGuerre(string n1, string n2)
{
	if (mainGax->RemoveWarScript(n1, n2)) {
		std::cout << "Guerre terminee entre " + n1 + " et " + n2 << std::endl;
	}
	else {
		std::cout << "Erreur dans la fin d'une guerre!" << std::endl;
	}
}

void Manager::displayAllInformations()
{
	// Affichage des planètes
	this->archive->showPlanets();

	//Affichage des vaisseaux
	this->archive->showSpaceships();

	//Affichage des conflits
	vector<WarScript*>::iterator iterWar;
	WarScript* currentElement = nullptr;

	cout << "Guerres déclarées: " << endl;
	if (mainGax->getWarScripts()->empty())
	{
		cout << "   Aucune guerre dans la galaxie pour le moment..." << endl;
	}
	else {
		for (iterWar = mainGax->getWarScripts()->begin(); iterWar != mainGax->getWarScripts()->end(); iterWar++)
		{
			currentElement = *iterWar;
			cout << "   " << currentElement->ToString();
		}
	}

	cout << endl << endl;
}

void Manager::afficherGalaxie() {
	GalaxyPrinter::PrintGalaxy(this, archive, mainGax);
}

void Manager::printPath(vector<Planet*>* path) {
	GalaxyPrinter::PrintAPath(this, archive, path);
}