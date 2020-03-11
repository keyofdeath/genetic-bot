//
// Created by no-code-team on 10/24/17.
//

#ifndef GENETIC_BOT_SENSOR_H
#define GENETIC_BOT_SENSOR_H

#include "../Board/Board.h"

typedef struct{

    // defait constante LASER_LENGTH
    int legth;//porter du capteur
    double angle;// ongle du capteur (il faut prende aussi en compte l'orientation du robot)
    double dist;// distance de l'obstacle
    double value;// valeur de la distance entre 0 et 1

}Sensor;

/**
 * Cree un nouveux capteur laser
 * @param length longeur de porter du capteur
 * @param angle Angle d'orientation du robot
 * @return Le capteur cree
 */
Sensor newSensor(int length, double angle);

/***
 * Mais a jour la valeur de sortie du robot
 * @param sensor
 * @param board plateau pour savoir si le laser détèct un obstacle
 * @param absAngle Angle absolue du capteur donc l'angle du capteur + l'angle du robot
 * @param posRobot position du robot pour savoir a position du capteur
 */
void updateSensor(Sensor* sensor, Board* board, double absAngle, Point posRobot);

#endif //GENETIC_BOT_SENSOR_H
