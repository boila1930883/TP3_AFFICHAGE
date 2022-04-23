// Projet: 8INF259 - TP3 Vitesse spatiale
// Etudiants : André Alano, Audrey Bédard et Laurie-Ann Boily

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Archivist.h"
#include "Manager.h"

void gameBoard();

int chooseGameMode();

void automaticMode();

void manualMode();

int manualModeMenu();

void questionParameters(std::string& ship, std::string& planet1, std::string& planet2);