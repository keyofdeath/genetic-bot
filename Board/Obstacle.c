//
// Created by no-code-team on 10/31/17.
//
#include "Obstacle.h"
#include <math.h>

/**
 * Cree un nouvelle obstacle
 * @param p1 point en haut a gauche du rectagle
 * @param largeur
 * @param hauteur
 * @return le nouvelle obstacle
 */
Obstacle newObstacle(Point p1, int largeur, int hauteur){

    Obstacle obstacle;
    obstacle.hauteur = hauteur;
    obstacle.largeur = largeur;
    obstacle.p1 = p1;
    obstacle.p2 = newPoint(p1.x[0] + largeur, p1.x[1] + hauteur);
    return obstacle;

}

/**
 * cree a obstacle par raport a 2 point
 * @param p1 point en haut a gauche
 * @param p2 point en bas a droit
 * @return
 */
Obstacle newObstacleP(Point p1, Point p2){

    Obstacle obstacle;
    obstacle.hauteur = fabs(p2.x[1] - p1.x[1]);
    obstacle.largeur = fabs(p2.x[0] - p1.x[0]);
    obstacle.p1 = p1;
    obstacle.p2 = p2;
    return obstacle;

}

/**
 * Regarde si le point et dans l'obstacle
 * @param obstacle obstacle a traiter
 * @param p point en question
 * @return 1 le point p et dans l'obstacle sinon 0
 */
int inObstacle(Obstacle obstacle, Point p){

    return Point_in_range(obstacle.p1, obstacle.p2, p);

}
