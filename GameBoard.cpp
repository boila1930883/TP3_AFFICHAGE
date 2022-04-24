// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#include "GameBoard.h"

using namespace std;

void gameBoard() {
	int gameMode;

	cout << "     BIENVENUE DANS VITESSE SPATIALE !!" << endl << endl << endl;
	gameMode = chooseGameMode();

	if (gameMode == 1) // Mode automatique
	{
		automaticMode();
	}
	else               // Mode manuel
	{
		manualMode();
	}
}

int chooseGameMode() {
	int gameMode;

	cout << "Choisir un mode de jeu:" << endl;
	cout << "     1 - Mode automatique    (charger le fichier de transaction)" << endl;
	cout << "     2 - Mode manuel         (controlez ce qui se passe dans la galaxie!)" << endl << endl;
	cout << "Quel est votre selection: ";
	cin >> gameMode;
	cout << endl;

	return gameMode;
}

void automaticMode() {
	Archivist* archivist = new Archivist();
	Manager* gm = new Manager(archivist);

	vector<Planet*>* path = nullptr;
	string fileName, currentFile, ship, planet1, planet2;
	ifstream transactionFile;
	char opCode, index;
	bool existingRoute, planetsLoaded = false, shipsLoaded = false;

	cout << "--- MODE AUTOMATIQUE ---" << endl << "Quel est le nom du fichier de transactions? ";
	cin >> fileName;

	transactionFile.open(fileName);

	if (!transactionFile.fail())	// Si l'ouverture du fichier réussie
	{
 		while (!transactionFile.eof())		// Tant que l'on est pas à la fin du fichier
		{
			transactionFile >> opCode;		// Lecture de l'opcode

			/*----- Choix de la transaction à effectuer en fonction de l'opcode -----*/
			switch (opCode)
			{
			case '#':		// Charge un fichier
				transactionFile >> index >> currentFile;
				if (index == 'P') {		// Chargement du fichier de planètes (création d'une galaxie)
					if (gm->loadPlanets(currentFile))
						planetsLoaded = true;

				}
				if (index == 'V') {		// Chargement du fichier de vaisseaux
					if (gm->loadShips(currentFile))
						shipsLoaded = true;
				}
				break;
			case '?':

				if (!(shipsLoaded && planetsLoaded)) {
					cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
					break;
				}

				transactionFile >> index >> ship >> planet1 >> planet2;
				if (index == '1') {		// Affiche s'il existe une route entre les deux planètes avec ce type de vaisseau
					existingRoute = gm->cheminExistant(ship, planet1, planet2);
					if (existingRoute) {
						cout << "Il existe un chemin entre " << planet1 << " et " << planet2 << " avec le vaisseau " << ship << " !" << endl << endl;
					}
					else {
						cout << "Il n'existe aucun chemin possible entre " << planet1 << " et " << planet2 << " avec le vaisseau " << ship << "." << endl << endl;
					}
				}
				if (index == '2') {		// Affiche le plus court chemin ainsi que la distance totale que peut parcourir ce type de vaisseau
					path = new vector<Planet*>(0);
					gm->calChemin(ship, planet1, planet2, false, path);
					delete path;
				}
				if (index == '3') {		// Affiche le chemin et le coût du trajet le moins dispendieux que peut suivre ce type de vaisseau
					path = new vector<Planet*>(0);
					gm->calChemin(ship, planet1, planet2, true, path);
					delete path;
				}
				break;
			case '/':		// Applique un scénario de conflit spatial entre deux nations
				if (!(shipsLoaded && planetsLoaded)) {
					cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
					break;
				}
				transactionFile >> planet1 >> planet2;
				gm->ajoutGuerre(planet1, planet2);
				break;
			case '&':		// Affiche toutes les planètes, tous les types de vaisseaux et tous les conflits entre nations
				if (!(shipsLoaded && planetsLoaded)) {
					cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
					break;
				}
				gm->displayAllInformations();
				break;
			default:
				cout << "Transaction invalide!" << endl;
			}
		}
		transactionFile.close();
		delete gm;
	}
	else
	{
		cout << "Erreur d'ouverture du fichier de transactions!" << endl;
	}
}

void manualMode() {
	Archivist* archivist = new Archivist();
	Manager* gm = new Manager(archivist);

	vector<Planet*>* path = nullptr;
	string fileName, ship, planet1, planet2;
	ifstream currentFile;
	bool existingRoute, quitGame(false), planetsLoaded = false, shipsLoaded = false;
	int selection;

	cout << "--- MODE MANUEL ---" << endl;

	while (!quitGame)
	{
		selection = manualModeMenu();

		switch (selection)
		{
		case 1:				// Chargement du fichier de planètes (création d'une galaxie)
			cout << "Quel est le nom du fichier de planète? ";
			cin >> fileName;
			cout << endl;
			if (gm->loadPlanets(fileName))
				planetsLoaded = true;
			break;
		case 2:				// Chargement du fichier de vaisseaux
			cout << "Quel est le nom du fichier de vaisseaux? ";
			cin >> fileName;
			cout << endl;
			if (gm->loadShips(fileName))
				shipsLoaded = true;
			break;
		case 3:				// Affiche s'il existe une route entre les deux planètes avec ce type de vaisseau

			if (!(shipsLoaded && planetsLoaded)) {
				cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
				break;
			}
			questionParameters(ship, planet1, planet2);
			existingRoute = gm->cheminExistant(ship, planet1, planet2);

			if (existingRoute) {
				cout << "Il existe un chemin entre " << planet1 << " et " << planet2 << " avec le vaisseau " << ship << " !" << endl << endl;
			}
			else {
				cout << "Il n'existe aucun chemin possible entre " << planet1 << " et " << planet2 << " avec le vaisseau " << ship << "." << endl << endl;
			}
			break;
		case 4:				// Affiche le plus court chemin ainsi que la distance totale que peut parcourir ce type de vaisseau
			if (!(shipsLoaded && planetsLoaded)) {
				cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
				break;
			}
			questionParameters(ship, planet1, planet2);

			path = new vector<Planet*>(0);

			gm->calChemin(ship, planet1, planet2, false, path);
			gm->printPath(path);
			delete path;
			break;
		case 5:				// Affiche le chemin et le coût du trajet le moins dispendieux que peut suivre ce type de vaisseau
			if (!(shipsLoaded && planetsLoaded)) {
				cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
				break;
			}

			path = new vector<Planet*>(0);
			questionParameters(ship, planet1, planet2);
			gm->calChemin(ship, planet1, planet2, true, path);
			gm->printPath(path);
			delete path;
			break;
		case 6:				// Applique un scénario de conflit spatial entre deux nations
			if (!(shipsLoaded && planetsLoaded)) {
				cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
				break;
			}
			cout << "Quelles nations sont en guerre?" << endl << "  Nation 1: ";
			cin >> planet1;
			cout << "  Nation 2: ";
			cin >> planet2;
			gm->ajoutGuerre(planet1, planet2);
			break;
		case 7:				// Affiche toutes les planètes, tous les types de vaisseaux et tous les conflits entre nations
			if (!(shipsLoaded && planetsLoaded)) {
				cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
				break;
			}
			gm->displayAllInformations();
			break;

		case 8:
			if (!(shipsLoaded && planetsLoaded)) {
				cout << "Les planetes et/ou les vaisseaux n'ont pas encore ete specifie. Il faut les specifier avant de jouer. \n";
				break;
			}
			gm->afficherGalaxie();
			break;

		default:			// Quitter la partie

			if (selection != 9) {
				cout << "Erreur, choix inconnu." << endl;
				break;
			}
			quitGame = true;
			delete gm;
			cout << endl << "     AU REVOIR !" << endl;
		}
	}
}

int manualModeMenu() {
	int selection;

	cout << "\n\n------------------------------" << endl;
	cout << "        OPTIONS DE JEU        " << endl;
	cout << "------------------------------" << endl << endl;
	cout << " 1 - Charger un nouveau fichier de planetes" << endl;
	cout << " 2 - Charger un nouveau fichier de vaisseaux" << endl;
	cout << " 3 - Déterminer s'il existe un chemin entre deux planètes avec un type de vaisseau" << endl;
	cout << " 4 - Afficher le chemin le plus court entre deux planètes avec un type de vaisseau" << endl;
	cout << " 5 - Afficher le chemin le moins dispendieux entre deux planètes avec un type de vaisseau" << endl;
	cout << " 6 - Appliquer un scénario de conflit entre deux nations" << endl;
	cout << " 7 - Afficher toutes les planetes, les vaisseaux et les conflits en cours" << endl;
	cout << " 8 - Afficher la galaxie (C'est vraiment cool, ca fait le jeu de ressources de l'annee !!!)" << endl;
	cout << " 9 - Quitter le jeu" << endl << endl;
	cout << "Quel est votre choix? ";
	cin >> selection;
	cout << endl;

	return selection;
}

void questionParameters(string& ship, string& planet1, string& planet2) {
	cout << "Quel sera le type de vaisseaux a utiliser? ";
	cin >> ship;
	cout << "À partir de quelle planete? ";
	cin >> planet1;
	cout << "Vers quelle planete? ";
	cin >> planet2;
	cout << endl;
}