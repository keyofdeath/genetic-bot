//
// Created by no-code-team on 10/31/17.
//

#ifndef GENETIC_BOT_BOARD_H
#define GENETIC_BOT_BOARD_H

#include "Obstacle.h"

typedef struct {

    Obstacle* obstacle;// Liste obstacle
    Point target;// objectif que doive ateindre les robot
    int nbObstacle;// nombre obstacle courent dans notre liste
    int lenTabObstacle;// longeur réele de notre liste d'obstacle
    int width;// Largeur du plateau
    int height;// Hauteur du plateau
    double temp_x;// Cette atribut contiendera la valeur du premier click (position x) dans le canvas pour ajouter un obstacle
    double temp_y;// Cette atribut contiendera la valeur du premier click (position y) dans le canvas pour ajouter un obstacle
    int p1_set;// Passe a 1 quand on a choisi notre position x de notre obstacle
    int time_spend;// Temps écouler debuit le début de la simulation en ms

} Board;

/**
 * Creation d'un nouveaux plateau
 * @param board pointeur du plateau
 * @param width largeur du plateau
 * @param height Hauteur du plateau
 */
void newBoard(Board* board, int width, int height);

/**
 * Donne une nouvelle position a la cible
 * @param board
 */
void newTargetPosition(Board* board);

/**
 * Ajoute a obstacle dans notre plateau
 * @param board poineur du plateau
 * @param obstacle obstacle a ajouter
 */
void addObstacle(Board* board, Obstacle obstacle);

/**
 * Suprimme un obstacle dans notre plateau
 * @param board poineur du plateau
 * @param p zone ou on a cliquez pour suprimer l'obstacle
 */
void suppObstacle(Board* board, Point p);

/**
 *
 * @param board poineur du plateau
 * @param p point ou on veur si on est dans un obstacle
 * @return 1 il y a un obstacle sinon 0
 */
int obstacleHere(Board* board, Point p);

/**
 * Regarde si a ce point donnée il y a un obstacle
 * @param board poineur du plateau
 * @param p point ou on veu voire si on est dans un obstacle
 * @return 1 il y a un obstacle sinon 0
 */
int robotInObstacle(Board* board, Point robotPosition);

#endif //GENETIC_BOT_BOARD_H
