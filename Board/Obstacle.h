//
// Created by no-code-team on 10/31/17.
//

#ifndef GENETIC_BOT_OBSTACLE_H
#define GENETIC_BOT_OBSTACLE_H

#include "../Vector2D/points.h"

typedef struct {

    Point p1;// position en haut gauche
    Point p2;// position en bas a droit
    double largeur;
    double hauteur;

} Obstacle;

/**
 * Cree un nouvelle obstacle
 * @param p1 point en haut a gauche du rectagle
 * @param largeur
 * @param hauteur
 * @return le nouvelle obstacle
 */
Obstacle newObstacle(Point p1, int largeur, int hauteur);

/**
 * cree a obstacle par raport a 2 point
 * @param p1 point en haut a gauche
 * @param p2 point en bas a droit
 * @return
 */
Obstacle newObstacleP(Point p1, Point p2);

/**
 * Regarde si le point et dans l'obstacle
 * @param obstacle obstacle a traiter
 * @param p point en question
 * @return 1 le point p et dans l'obstacle sinon 0
 */
int inObstacle(Obstacle obstacle, Point p);

#endif //GENETIC_BOT_OBSTACLE_H
