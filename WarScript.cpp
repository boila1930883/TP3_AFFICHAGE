// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#include <string>
#include "WarScript.h"
#include "Counter.h"

WarScript::WarScript(std::string nation1, std::string nation2) {
	this->nation1 = nation1;
	this->nation2 = nation2;
	Counter::addConstrutor();
}

WarScript::~WarScript() {
	Counter::addDestructor();
}

bool WarScript::AreTheyAtWar(std::string n1, std::string n2) {
	// Cette condition admet les conflits de guerre civile
	if ((n1 == this->nation1 && n2 == this->nation2) || (n2 == this->nation1 && n1 == this->nation2))
		return true;

	return false;
}

std::string WarScript::ToString() { return this->nation1 + " VS " + this->nation2 + "\n";}