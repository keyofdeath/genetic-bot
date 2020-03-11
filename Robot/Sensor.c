//
// Created by no-code-team on 10/24/17.
//
#include "Sensor.h"
#include "../Constante/Constante.h"

/**
 * Cree un nouveux capteur laser
 * @param length longeur de porter du capteur
 * @param angle Angle d'orientation du robot
 * @return Le capteur cree
 */
Sensor newSensor(int length, double angle){

    Sensor s;
    s.legth = length;
    s.angle = angle;
    s.dist = 0.0;
    s.value = 0.0;
    return s;

}

/***
 * Mais a jour la valeur de sortie du robot
 * @param sensor
 * @param board plateau pour savoir si le laser détèct un obstacle
 * @param absAngle Angle absolue du capteur donc l'angle du capteur + l'angle du robot
 * @param posRobot position du robot pour savoir a position du capteur
 */
void updateSensor(Sensor* sensor, Board* board, double absAngle, Point posRobot){

    // on cree un point au centre du robot
    Point laser_point = newPoint(posRobot.x[0], posRobot.x[1]);
    // puis on regard a quelle position il est a l'extrémiter du robot
    Point_add_angle(absAngle, ROBOT_R, &laser_point);
    int length = sensor->legth;
    sensor->dist = 0.0;

    for (double distCC = 0.0; distCC <= length; distCC += LASER_PRESITION) {

        // on augmente la distance de recherche
        Point_add_angle(absAngle, LASER_PRESITION, &laser_point);

        // si pas obstacle detecter
        if (! obstacleHere(board, laser_point)){
            sensor->dist = distCC;
        }else{
            break;
        }

    }
    sensor->value = sensor->dist / (double)sensor->legth;
}
