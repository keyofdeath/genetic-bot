//
// Created by no-code-team on 10/23/17.
//

#ifndef GENETIC_BOT_POPULATION_H
#define GENETIC_BOT_POPULATION_H

#include "../Neural/NeuralNetwork.h"
#include "Individual.h"
#include "../Robot/Robot.h"

typedef struct {

    int populationSize;// Taille de la population
    int generation;// Numéro de la génération
    Robot* individualList;// Liste de robot

} Population;

/**
 * Init une population
 * @param population Structur a init
 * @param populationSize Taille de la population
 * @param neuronalNetwork Reseau de neurone pour gene l'adn
 */
void newPopulation(Population* population, int populationSize, Board* board);

/**
 * Fait une nouvelle génération de la population donnée en appliquent la méthode
 * d'un algorithme génétique
 * @param population
 * @param board
 */
void newPopulationGeneration(Population* population);

/**
 * Atribut un score a tout la population
 * @param population
 */
void setPopulationScore(Population* population);

/**
 * Ajoute un individu dans le population
 * PS: L'individu est init avec un adn aléatoire
 * @param population
 * @param board
 */
void addIndividual(Population* population, Board* board);

/**
 * Affiche la population util pour debug
 * @param population population a aficher
 */
void dispPopulation(Population population);

#endif //GENETIC_BOT_POPULATION_H
