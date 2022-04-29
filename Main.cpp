/*
Projet: 8INF259 - TP3 Vitesse spatiale -- VERSION AFFICHAGE GRAPHIQUE
Etudiants: André Alano, Audrey Bédard et Laurie-Ann Boily
Date: 29 avril 2022
Description: Il s'agit d'un jeu de simulation ou le joueur doit faire la gestion du transport spatial entre les planetes d'un lointain systeme stellaire. Le joueur doit ainsi minimiser les couts de deplacement du vaisseau en optimisant les routes de transport et en evitant les zones de conflits entre les nations 

POUR QUE LE PROGRAMME COMPILE, IL VOUS FAUDRA INSTALLER LA LIBRAIRIE EXTERNE OPENCV, VOICI UN PETIT DE GUIDE DE COMMENT FAIRE :
0. Fonctionne avec Visual Studio 2019 (les propriétés sont set up pour Visual Studio 2019)
1. Downloader la version de opencv 3.4.3 : https://sourceforge.net/projects/opencvlibrary/files/opencv-win/
2. Installer opencv (le telechargement vous donnera un executable) et le mettre en variable d'environnement sous le nom de OPENCV_DIR comme
   dans ce guide : https://www.opencv-srf.com/2017/11/install-opencv-with-visual-studio.html
   (Faire uniquement la partie Set Up Environment Variables).
3. Mettez les librairies de l'archive Librairies TP3.rar a cote du fichier Main dans le repertoire du projet.
4. Nettoyer la solution, generer puis executer.

*** Si le projet semble ne pas fonctionner, voici un lien github pour recuperer le projet : https://github.com/boila1930883/TP3_AFFICHAGE
	Il suffit de le cloner et de suivre les etapes a partir du #1. Tout devrait fonctionner. Si ce n'est pas le cas et que vous voulez vraiment
	le voir fonctionner :P, hesitez pas a me contacter sur Discord : Lopterion#5804
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