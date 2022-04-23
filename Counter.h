// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#pragma once

class Counter
{
private:
	static int constructor;		// Comptabilise le nombre de constructeurs appelé
	static int destructor;			// Comptabilise le nombre de destructeurs appelé

public:
	Counter();
	~Counter();

	static void addConstrutor() { constructor++; }
	static void addDestructor() { destructor++; }
	static int getNbConstructors() { return constructor; }
	static int getNbDestructors() { return destructor; }
};

