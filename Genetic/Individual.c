//
// Created by no-code-team on 10/23/17.
//
#include "Individual.h"

/**
 * Cree un individu
 * @param dnaNeuralNetwork adn de l'individu
 * @return Un individu
 */
Individual newIndividual(DnaNeuralNetwork dnaNeuralNetwork){

    Individual individual;
    individual.score = 0;
    individual.nb_hit_obstacle = 0;// Nombre obstacle toucher
    individual.hit_goal = 0;// Si il a eu le goal
    individual.dnaNeuralNetwork = dnaNeuralNetwork;
    individual.tuch_obstacle = 0;
    return individual;

}

/**
 * Reset un individu
 * @param individual
 */
void resetIndividual(Individual* individual){

    individual->score = 0;
    individual->nb_hit_obstacle = 0;
    individual->hit_goal = 0;
    individual->tuch_obstacle = 0;
}
