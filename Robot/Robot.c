//
// Created by no-code-team on 10/23/17.
//
#include <stdlib.h>
#include "Robot.h"

/**
 * Cree un nouveaux robot
 * @param individual Individu lie a lie au robot
 * @return
 */
void newRobot(Robot* robot, Individual individual, NeuronalNetwork neuronalNetwork, Board* board){
    
    int laserLength = LASER_LENGTH;
    robot->individual = individual;
    robot->sensor = (Sensor*)malloc(NUMBER_SENSOR_ROBOT * sizeof(Sensor));
    robot->wheelCommand = 0;// entre -128 et 128
    robot->engineCommand = 0;// entre -128 et 128
    robot->engine = 0;
    robot->ratio_engin = 0.0;
    robot->acceleration = ROBOT_ACCELERATION;
    robot->angle = ROBOT_START_ANGLE;// Regarde vers le haut
    robot->position.x[0] = WIDTH / 2;
    robot->position.x[1] = HEIGHT - (ROBOT_R * 3);
    robot->neuralNetwork = neuronalNetwork;
    // on calcule la distance puis on passe cette distance entre 0 et 1.
    // 1 et la distance max qui est la largeur + la hauteur du plateau
    robot->dist_to_target = Point_distance(board->target, robot->position) / (board->width + board->height);

    double angleStep = 360.0 / NUMBER_SENSOR_ROBOT;
    double angleCC = robot->angle;
    int i;
    for (i = 0; i < NUMBER_SENSOR_ROBOT; ++i) {
        robot->sensor[i] = newSensor(laserLength, angleCC);
        // on lie la valeur du capteur du robot a l'entree du reseu
        robot->neuralNetwork.neuronalInput[i].value = &robot->sensor[i].value;
        angleCC += angleStep;
    }
    
    // on lie aussi ratio_engin vitesse du robot
    robot->neuralNetwork.neuronalInput[i++].value = &robot->ratio_engin;
    // On lie la distance que le robot rest a parcourir
    robot->neuralNetwork.neuronalInput[i].value = &robot->dist_to_target;
}

/**
 * Reset le robot
 * PS: Cette fonction de reset pas sont adn
 * @param robot
 */
void resetRobot(Robot* robot){

    robot->wheelCommand = 0;// entre -128 et 128
    robot->engineCommand = 0;// entre -128 et 128
    robot->engine = 0;
    robot->ratio_engin = 0.0;
    robot->acceleration = ROBOT_ACCELERATION;
    robot->angle = ROBOT_START_ANGLE;// Regarde vers le haut
    robot->position.x[0] = WIDTH / 2;
    robot->position.x[1] = HEIGHT - (ROBOT_R * 3);
    resetIndividual(&robot->individual);
}

/**
 * Tick de simulation du robot
 * Cette fonction bouge le robot
 * Controle si il n'a pas attin la cible
 * @param robot
 * @param board
 */
void robotTick(Robot* robot, Board* board){

    // entre -1 et 1
    double ratioWheel = (double)robot->wheelCommand / (double)ROBOT_WHEEL_COMMAND;
    int acc = robot->acceleration;

    // Si notre vitesse sible n'est pas atein
    if (robot->engineCommand > robot->engine){
        if (robot->engineCommand > robot->engine + acc)
            // on accélaire
            robot->engine += acc;
        else
            robot->engine = robot->engineCommand;
    }else if(robot->engineCommand < robot->engine){
        if (robot->engineCommand < robot->engine - acc)
            robot->engine -= acc;
        else
            robot->engine = robot->engineCommand;
    }

    // entre -1 et 1
    robot->ratio_engin = (double)robot->engine / (double)ROBOT_ENGINE_COMMAND;
    // on deplasse le robot en fontion de l'angle de bracage
    if (robot->ratio_engin >= 0)
        robot->angle += ratioWheel;
    else
        robot->angle -= ratioWheel;

    Point newRobotPosition = robot->position;
    // Enfin on deplasse le robot en fonction de langle
    Point_add_angle(robot->angle, robot->ratio_engin, &newRobotPosition);
    // Si le robot n'est pas dans un obstacle on le deplasse
    if (! robotInObstacle(board, newRobotPosition)) {
        robot->position = newRobotPosition;
        robot->individual.tuch_obstacle = 0;
    }
    else{
        // Si c'est la première fois qu'il touche l'obstacle
        if (! robot->individual.tuch_obstacle){
            robot->individual.tuch_obstacle = 1;
            robot->individual.nb_hit_obstacle++;
        }
    }

    // Si le robot a toucher le cible
    if (Point_distance(board->target, robot->position) <= TARGET_R + ROBOT_R){
        robot->individual.hit_goal = 1;
        robot->individual.time_to_goal = board->time_spend;
    }

    // Mise a jours des capteurs
    for (int i = 0; i < NUMBER_SENSOR_ROBOT; ++i) {
        // Mise a jours du capteur
        updateSensor(&robot->sensor[i], board, robot->angle + robot->sensor[i].angle, robot->position);
    }

    // on calcule la distance puis on passe cette distance entre 0 et 1. 1 et la distance max
    robot->dist_to_target = Point_distance(board->target, robot->position) / (board->width + board->height);

    // On regarde si on ne dois pas faire de prélévement
    if (board->time_spend % TIME_DATA_PICK == 0)
        // Si oui on ajoute la distance du robot
        robot->individual.dist_pick[(board->time_spend / TIME_DATA_PICK) - 1] = robot->dist_to_target;
}