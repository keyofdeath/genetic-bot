//
// Created by no-code-team on 12/11/17.
//

#ifndef GENETIC_BOT_WORKERS_H
#define GENETIC_BOT_WORKERS_H

#include <pthread.h>
#include <semaphore.h>
#include "../Board/Board.h"
#include "../Genetic/Population.h"
#include "../Constante/Constante.h"

/**
 * Struct qui donnée au thread pour qu'il est accés au donnée util
 */
typedef struct {

    int end;// Passe a 1 quand on veut arreter les workers
    int index_cc;// index courent du tableau de la population
    pthread_mutex_t mutex;// Mutex pour protéger l'écritur dans les variables
    sem_t sem_attent_workers;// Semaphore pour débloquer ou bloquer les threads
    // Semaphore pour le programme principale. Pour qu'il attend les workers
    sem_t sem_attent_main;// Semaphore pour faire attendre le programme principale
    Population* population;// Population avec les robots
    Board* board;

} InfoWorkers;

/**
 * Struct global qui contien la liste des threads un une
 * instance de la struct InfoWorkers
 */
typedef struct{

    pthread_t tab_worker[NBWORKERS];// Tableaut des workeur
    InfoWorkers infoWorkers;// Struct pour les workers

} Workers;


/**
 * Cree les threads
 * @param workers structur a initialiser
 * @param population Pointeru ver la popualtion
 * @param board
 */
void newWorkers(Workers* workers, Population* population, Board* board);

/**
 * Démmare un les thread et lance un tic de calcul a toute la population
 * @param workers
 */
void launchWorkers(Workers* workers);

/**
 * Détruit les threads et la structur
 * @param workers
 */
void firedWorkers(Workers* workers);

#endif //GENETIC_BOT_WORKERS_H
