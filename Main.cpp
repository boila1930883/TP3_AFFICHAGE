/*
Projet: 8INF259 - TP3 Vitesse spatiale
Etudiants: André Alano, Audrey Bédard et Laurie-Ann Boily
Date: 29 avril 2022
Description: Il s'agit d'un jeu de simulation ou le joueur doit faire la gestion du transport spatial entre les planetes d'un lointain systeme stellaire. Le joueur doit ainsi minimiser les couts de deplacement du vaisseau en optimisant les routes de transport et en evitant les zones de conflits entre les nations 
*/

#include <iostream>
#include "Counter.h"
#include "GameBoard.h"

using namespace std;

void displayClassBalance();

int main(void) {

	setlocale(LC_CTYPE, "fr-FR");					// Permet l'affichage des caracteres francophones
	gameBoard();
	displayClassBalance();

	return 0;
}


/*
	Valider le balancement des constructeurs et des destructeurs
	Permet de valider l'absence de fuite de memoire liee aux objets (class)
*/
void displayClassBalance() {
	cout << endl << endl;
	cout << endl << "-----------------------------" << endl
		<< "NB constructeurs           : " << Counter::getNbConstructors() << endl
		<< "NB destructeurs            : " << Counter::getNbDestructors() << endl;
}