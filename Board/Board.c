//
// Created by no-code-team on 10/31/17.
//

#include <stdlib.h>
#include "Board.h"
#include "../Tool/Tool.h"

/**
 * Creation d'un nouveaux plateau
 * @param board pointeur du plateau
 * @param width largeur du plateau
 * @param height Hauteur du plateau
 */
void newBoard(Board* board, int width, int height){

    board->obstacle = (Obstacle*)malloc(sizeof(Obstacle));
    board->nbObstacle = 0;
    board->lenTabObstacle = 1;
    board->width = width;
    board->height = height;
    board->temp_x = -1.0;
    board->temp_y = -1.0;
    board->time_spend = 0;
    newTargetPosition(board);
}

/**
 * Donne une nouvelle position a la cible
 * @param board
 */
void newTargetPosition(Board* board){

    board->target.x[0] = rand_min_max(ROBOT_R, board->width - ROBOT_R);
    board->target.x[1] = rand_min_max(ROBOT_R, board->height - ROBOT_R);
}

/**
 * Ajoute a obstacle dans notre plateau
 * @param board poineur du plateau
 * @param obstacle obstacle a ajouter
 */
void addObstacle(Board* board, Obstacle obstacle){

    // Si on a déja ajouter des elements on agrendi le tableau
    if (board->nbObstacle >= board->lenTabObstacle){
        board->lenTabObstacle *= 2;
        // on agrandi l'alocation
        board->obstacle = realloc(board->obstacle, (board->lenTabObstacle) * sizeof(Obstacle));
    }

    board->obstacle[board->nbObstacle++] = obstacle;
}

/**
 * Suprimme un obstacle dans notre plateau
 * @param board poineur du plateau
 * @param p zone ou on a cliquez pour suprimer l'obstacle
 */
void suppObstacle(Board* board, Point p){
    int obstacleIndex = -1;

    if (board->nbObstacle == 0)
        return;

    for(int i = 0; i < board->nbObstacle; i++){

        if (inObstacle(board->obstacle[i], p)) {
            obstacleIndex = i;
            break;
        }
    }

    if (obstacleIndex == -1)
        return;

    // puis on decale les obstacle dans la liste
    board->nbObstacle--;
    for (int i = obstacleIndex; i < board->nbObstacle; i++){
        board->obstacle[i] = board->obstacle[i + 1];
    }

}

/**
 * Regarde si a ce point donnée il y a un obstacle
 * @param board poineur du plateau
 * @param p point ou on veu voire si on est dans un obstacle
 * @return 1 il y a un obstacle sinon 0
 */
int obstacleHere(Board* board, Point p){

    // Si le robot n'est pas dans la fenetre
    if (! Point_in_range(newPoint(0, 0), newPoint(board->width, board->height), p))
        return 1;

    for(int i = 0; i < board->nbObstacle; i++){

        if (inObstacle(board->obstacle[i], p))
            return 1;
    }
    return 0;
}

/**
 * Regarde si la poosition donnée touche un obstacle
 * @param board
 * @param robotPosition
 * @return 1 il y a une colision sinon 0
 */
int robotInObstacle(Board* board, Point robotPosition){

    // on transform notre cercle en carrée
    robotPosition.x[0] -= ROBOT_R;
    robotPosition.x[1] -= ROBOT_R;

    // on regarde que le robot ne sorte pas de l'ecrant
    if(robotPosition.x[0] + ROBOT_R*2 >= board->width || robotPosition.x[0] <= 0 ||
            robotPosition.x[1] + ROBOT_R*2 >= board->height || robotPosition.x[1] <= 0)
        return 1;


    Obstacle obstacle_cc;
    for(int i = 0; i < board->nbObstacle; i++){
        obstacle_cc = board->obstacle[i];
        // Si ne sois au bord de l'obstacle
        if(robotPosition.x[0] < obstacle_cc.p1.x[0] + obstacle_cc.largeur &&
                robotPosition.x[0] + ROBOT_R*2 > obstacle_cc.p1.x[0] &&
                robotPosition.x[1] < obstacle_cc.p1.x[1] + obstacle_cc.hauteur &&
                robotPosition.x[1] + ROBOT_R*2 > obstacle_cc.p1.x[1])
            return 1;
    }
    return 0;
}
