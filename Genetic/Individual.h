//
// Created by no-code-team on 10/23/17.
//

#ifndef GENETIC_BOT_INDIVIDUAL_H
#define GENETIC_BOT_INDIVIDUAL_H

#include <stdbool.h>
#include "DnaNeuralNetwork.h"
#include "../Constante/Constante.h"

typedef struct {

    int score;// Score de l'individu
    int nb_hit_obstacle;// Nombre obstacle toucher
    int tuch_obstacle;// Variable drapeau qui passe a 1 si le robot et au conctact d'un obstacle sinon 0
    int hit_goal;// Si il a eu le goal
    int time_to_goal;// Temps qu'il a mie pour aller au goal
    double dist_pick[MAX_TIME/TIME_DATA_PICK];// Tableau de distance entre la cible prise pendant la simulation.
    // Se sera util pour voir les robots qui tourne en rond ou qui ne bouge pas
    DnaNeuralNetwork dnaNeuralNetwork;// Adn de l'individu

} Individual;

/**
 * Cree un individu
 * @param dnaNeuralNetwork adn de l'individu
 * @return Un individu
 */
Individual newIndividual(DnaNeuralNetwork dnaNeuralNetwork);

/**
 * Reset un individu
 * @param individual
 */
void resetIndividual(Individual* individual);

#endif //GENETIC_BOT_INDIVIDUAL_H
