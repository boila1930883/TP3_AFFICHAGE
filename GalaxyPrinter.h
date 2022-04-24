#pragma once

#include "Manager.h"
#include "Archivist.h"
#include <opencv2/opencv.hpp>
#include "Galaxy.h"
#include <string>
#include "Planet.h"
#include "Nation.h"
#include <vector>

class GalaxyPrinter {
public:
	static void PrintGalaxy(Manager* manager, Archivist* archvisit, Galaxy* galaxy);
	static void PrintAPath(Manager* manager, Archivist* archivist, std::vector<Planet*>* path);

private:
	static cv::Mat CreateGalaxy(Manager* manager, Archivist* archivist, Galaxy* galaxy);
	static const int GALAXY_SIZE = 1000;
	static bool isInList(std::string nation, std::vector<Nation*>* list);
	static cv::Scalar PlanetToColor(Planet* planet, std::vector<Nation*>* listNation);

	// Les couleurs qui seront utilisees pour le dessin
	static cv::Scalar getScalarByIndex(int index);
	static std::string getColorByIndex(int index);
	static cv::Scalar getPathColor();  // Blanc  - Chemin
	static cv::Scalar getBackgroundColor();// Noir - Fond de la galaxie
};