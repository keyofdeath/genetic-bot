//
// Created by no-code-team on 10/24/17.
//

#ifndef GENETIC_BOT_CONSTANTE_H
#define GENETIC_BOT_CONSTANTE_H

// Mode debug 0 ou 1 actif
#define DEBUG 1

//                 __________________________________
//________________/CONSTANTE POUR LA PARTIE GÉNÉTIQUE\________________

// nombre de neurone (1 pour l'accélération durobot 1 pour les roue rotation)
#define NB_NEURAL 2
// valeur par defaut d'une entree du reseau de neuronne
#define DEFAULT_INPUT_VALUE 0.0
// Nombre de capteur sur le robot
#define NUMBER_SENSOR_ROBOT 8
// Autre entree donnée au robot (vitesse et distance de sont objectif)
#define NUMBER_OTHER_DIVICE 2
// Nombre de robot par simulation
#define POPULATION_SIZE 30
// Porter du laser
#define LASER_LENGTH 100
//precision du laser
#define LASER_PRESITION 1.0
// orientation du robot au debut de la simulation
#define ROBOT_START_ANGLE 90
// Costante pour l'aceleration du robot
#define ROBOT_ACCELERATION 1
// Constante pour la vitesse du robot
#define ROBOT_ENGINE_COMMAND 128
// costante pour la direction des roue
#define ROBOT_WHEEL_COMMAND 128
// Vitesse de la simulation en ms sois 1000ms -> 1sec
#define TICK_TIME 1000
// Temps en ms que le programme dois
#define TIME_DATA_PICK 500
// Temps maximum qu'a le robot pour aller a la cible en ms
#define MAX_TIME 15000
// Taut de mutation entre 0 et 1
#define MUTATION_RATE 0.3

//********SCORE********

// Score gagane quand on arrive au goal
#define HIT_GOAL 100
#define SCORE_NOT_HIT 50
// Nombre de point perdu par seconde
#define POINT_LOSE_PER_S 1
// Nombre de point perdu par obstacle toucher
#define POINT_LOSE_PER_HIT 3

// Si c'est a 1 des que un robot atein un objectif sont adn et copier a tout population avec de la mutation
#define MODE_COPIE 1

//                        ___________________________
//_______________________/CONSTANTE POUR LA PARTIE UI\________________

// Largeur de la fenetre
#define WIDTH 500
// Hauteur de la fenetre
#define HEIGHT 500
// Pas de temps pour les ticks de simulation en s (sois 10ms) 1000*0.01 = 10ms
#define DT 0.01
// Pas de temps en s pour le réaffichage (soit 20ms)
#define DT_AFF 0.02
// Epesseur du trai du laser
#define LASER_LINE_WIDTH 1
// Rayon du robot
#define ROBOT_R 20
// Rayon de la cible
#define TARGET_R 20
// Robot direction row width
#define ROBOT_DIRECTION_WIDTH 3
// Nombre de label pour afficher des info divers
#define NB_LABEL_INFO 3
// Mode sauvgarde
#define MODE_SAVE 2
// Mode test dna
#define MODE_TEST 1
// Mode normale
#define MODE_NORMAL 0

//                        _________________________
//_______________________/CONSTANTE POUR LES THREAD\________________

// Nombre de thread qui seront générer
#define NBWORKERS 8
// Macro pour faciliter le cast de la careation d'un thread
#define THREAD_FUNC(f) (void*(*)(void*))f

#endif //GENETIC_BOT_CONSTANTE_H
