//
// Created by no-code-team on 10/23/17.
//

#ifndef GENETIC_BOT_ROBOT_H
#define GENETIC_BOT_ROBOT_H

#include "../Genetic/Individual.h"
#include "Sensor.h"
#include "../Vector2D/points.h"
#include "../Neural/NeuralNetwork.h"

typedef struct{

    NeuronalNetwork neuralNetwork;// Reseu de neuronne utiliser
    Individual individual;// Individu contien adn score etc
    Sensor* sensor;// Liste des capteurs laser du robot
    int wheelCommand;// Commande des roues entre -128 et 128
    int engineCommand;// Commande du moteur (ave,cer reculer) -128 et 128
    int engine;// vitesse courente du robot entre -128 et 128
    double ratio_engin;// valeur entre -1 et 1 -1 ->-128 1 ->+128
    double dist_to_target;//Distaace entre 0 et
    int acceleration;// acceleration du robot
    Point position;// Position du robot
    double angle;// Angle du robot

} Robot;

/**
 * Cree un nouveaux robot
 * @param individual Individu lie a lie au robot
 * @return
 */
void newRobot(Robot* robot, Individual individual, NeuronalNetwork neuronalNetwork, Board* board);

/**
 * Tick de simulation du robot
 * Cette fonction bouge le robot
 * Controle si il n'a pas attin la cible
 * @param robot
 * @param board
 */
void robotTick(Robot* robot, Board* board);

/**
 * Reset le robot
 * PS: Cette fonction de reset pas sont adn
 * @param robot
 */
void resetRobot(Robot* robot);

#endif //GENETIC_BOT_ROBOT_H
