// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#pragma once
#include <string>

class WarScript {

	public:
		WarScript(std::string nation1, std::string nation2);
		~WarScript();
		bool AreTheyAtWar(std::string n1, std::string n2);
		std::string ToString();

	private:

		std::string nation1;
		std::string nation2;
};