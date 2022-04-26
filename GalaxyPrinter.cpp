#include "GalaxyPrinter.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "Nation.h"

using namespace std;
using namespace cv;

void GalaxyPrinter::PrintGalaxy(Manager* manager, Archivist* archivist, Galaxy* galaxy) {

	namedWindow("Galaxie");
	imshow("Galaxie", CreateGalaxy(manager, archivist, galaxy));
	waitKey(10000);
	destroyWindow("Galaxie");

}
void  GalaxyPrinter::PrintAPath(Manager* manager, Archivist* archivist, std::vector<Planet*>* path) {

	Mat img = CreateGalaxy(manager, archivist, manager->getGalaxy());

	if (path->size() < 1) {
		cout << "Le chemin est de longueur < 1, rien a afficher" << endl;
		return;
	}

	Point p1 (path->at(0)->getPositionX(), GALAXY_SIZE - path->at(0)->getPositionY()), p2 (0,0);

	for (int i = 1; i < path->size(); i++) {
		p2.x = path->at(i)->getPositionX();
		p2.y = GALAXY_SIZE - path->at(i)->getPositionY();

		line(img, p1, p2, getPathColor());

		p1.x = p2.x;
		p1.y = p2.y;
	}

	namedWindow("Galaxie");
	imshow("Galaxie", img);
	waitKey(10000);
	destroyWindow("Galaxie");
}
cv::Mat GalaxyPrinter::CreateGalaxy(Manager* manager, Archivist* archivist, Galaxy* galaxy) {

	vector<Nation*>* listNations = new vector<Nation*>();
	vector<Planet*>* planetsNotPrinted = new vector<Planet*>();
	Mat img = Mat(1000, 1000, CV_8UC3, GalaxyPrinter::getBackgroundColor());

	// Determinon combien de nations nous avons
	for (int i = 0; i < archivist->getPlanetList()->size(); i++) {
		if (!isInList(archivist->getPlanetList()->at(i)->getNation(), listNations))
			listNations->push_back(new Nation(archivist->getPlanetList()->at(i)->getNation(), getColorByIndex(i), getScalarByIndex(i)));
	}

	// Nous mettons les points pour les planetes
	for (int i = 0; i < archivist->getPlanetList()->size(); i++) {
		if (archivist->getPlanetList()->at(i)->getPositionX() > GALAXY_SIZE || archivist->getPlanetList()->at(i)->getPositionY() > GALAXY_SIZE) {
			planetsNotPrinted->push_back(archivist->getPlanetList()->at(i));
			continue;
		}

		circle(img, Point(archivist->getPlanetList()->at(i)->getPositionX(), GALAXY_SIZE - archivist->getPlanetList()->at(i)->getPositionY()), 2, PlanetToColor(archivist->getPlanetList()->at(i), listNations), FILLED);
	}

	// Afficher les nations
	for (int i = 0; i < listNations->size(); i++)
		cout << listNations->at(i)->toString() << endl;
	
	cout << "Planetes trop eloignees pour etre affichees:" << endl;
	for (int i = 0; i < planetsNotPrinted->size(); i++)
		cout << planetsNotPrinted->at(i)->getName() << endl;

	cout << "*** Si la fenetre freeze/bug, attendez 10s et elle se fermera seule et le programme continuera" << endl;

	// Supprime liste nations et planetes non affichees
	for (int i = 0; i < listNations->size(); i++)
		delete listNations->at(i);

	delete listNations;
	delete planetsNotPrinted;

	return img;
}

bool GalaxyPrinter::isInList(string nation, vector<Nation*>* list) {

	for (int i = 0; i < list->size(); i++)
		if (list->at(i)->getName() == nation)
			return true;

	return false;
}

Scalar GalaxyPrinter::PlanetToColor(Planet* planet, vector<Nation*>* listNation) {

	for (int i = 0; i < listNation->size(); i++)
		if (listNation->at(i)->getName() == planet->getNation())
			return listNation->at(i)->getColor();

	return Scalar(0, 0, 0);
}

// Les couleurs qui seront utilisees pour le dessin
Scalar GalaxyPrinter::getScalarByIndex(int index) {

	switch (index) {
		case 0 : return Scalar(0, 0, 255);      break; 		// Rouge  - Nation 1
		case 1 : return Scalar(0, 255, 0);      break;		// Vert	  - Nation 1
		case 2 : return	Scalar(255, 128, 0);    break;		// Bleu	  - Nation 1
		case 3 : return Scalar(0, 128, 255);    break;		// Orange - Nation 1
		case 4 : return Scalar(0, 255, 255);    break;		// Jaune  - Nation 1
		case 5 : return Scalar(255, 128, 128);    break;		// Mauve  - Nation 1
		case 6 : return Scalar(64, 128, 128);    break;		// Or	  - Nation 1
		case 7 : return	Scalar(192, 128, 255);  break;		// Rose	  - Nation 1
		default : return Scalar(128, 128, 128); break;		// Gris   - 8e et toutes les autres nations		
	};
}

string GalaxyPrinter::getColorByIndex(int index) {

	switch (index) {
	case 0: return "ROUGE";    break; 		// Rouge  - Nation 1
	case 1: return "VERT";     break;		// Vert	  - Nation 2
	case 2: return "BLEU";     break;		// Bleu	  - Nation 3
	case 3: return "ORANGE";   break;		// Orange - Nation 4
	case 4: return "JAUNE";    break;		// Jaune  - Nation 5
	case 5: return "MAUVE";    break;		// Mauve  - Nation 6
	case 6: return "OR";	   break;		// Or	  - Nation 7
	case 7: return	"ROSE";	   break;		// Rose	  - Nation 8
	default: return "GRIS";	   break;		// Gris   - 9e et toutes les autres nations		
	};
}

Scalar GalaxyPrinter::getPathColor () {return Scalar(255, 255, 255); }  // Blanc  - Chemin
Scalar GalaxyPrinter::getBackgroundColor () { return Scalar(0, 0, 0); } // Noir - Fond de la galaxie