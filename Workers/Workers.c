#include "Workers.h"


/**
 * Transform une valeur entre 0 et 1 en une valeur entre min et max
 * @param min
 * @param max
 * @param val valeur entre 0 et 1
 * @return
 */
int normelize(int min, int max, double val){
    return (int)(val * (max - min) + min);
}


/**
 * Travailleur qui va se chager de fair avencer les robots
 * @param infoWorkers
 */
void worker(InfoWorkers* infoWorkers){


    pthread_mutex_lock(&infoWorkers->mutex);
    int end = infoWorkers->end;
    pthread_mutex_unlock(&infoWorkers->mutex);
    int index_cc;
    double res[2];
    Robot* robot_cc;
    while(! end){

        // on attend qu'il y est du travail
        sem_wait(&infoWorkers->sem_attent_workers);
        // on controle que ne se sois pas la fin
        pthread_mutex_lock(&infoWorkers->mutex);
        end = infoWorkers->end;
        pthread_mutex_unlock(&infoWorkers->mutex);
        if(end)
            break;
        // on recupair l'individu a traiter
        pthread_mutex_lock(&infoWorkers->mutex);
        index_cc = infoWorkers->index_cc--;
        pthread_mutex_unlock(&infoWorkers->mutex);
        // on traite tout la populations
        while (index_cc >= 0){

            robot_cc = &infoWorkers->population->individualList[index_cc];
            // Si il a atien l'obstacle on ne fai rien
            if (! robot_cc->individual.hit_goal){
                // reseau du robot
                NeuronalNetwork* robot_netWork = &robot_cc->neuralNetwork;
                // on charge l'adn du robot dans sont reseau de neurone
                initFromDna(robot_netWork, robot_cc->individual.dnaNeuralNetwork);
                // PS On n'a pas besoin de charger les valeurs des capteur dans les entrees du reseau de neurone
                // car elle sont lie entre elle
                calculateNetwork(robot_netWork);
                // onrecupair les resultas

                getNetworkResultList(robot_netWork, res);
                // vitesse du robot
                int engineCommande = normelize(-ROBOT_ENGINE_COMMAND, ROBOT_ENGINE_COMMAND, res[0]);
                // pilotage des roues
                int wheelCommande = normelize(-ROBOT_WHEEL_COMMAND, ROBOT_WHEEL_COMMAND, res[1]);
                robot_cc->engineCommand = engineCommande;
                robot_cc->wheelCommand = wheelCommande;
                // tick de calcule au robot
                robotTick(robot_cc, infoWorkers->board);
            }


            pthread_mutex_lock(&infoWorkers->mutex);
            index_cc = infoWorkers->index_cc--;
            pthread_mutex_unlock(&infoWorkers->mutex);
        };
        // on signal que on a fini le traitement
        sem_post(&infoWorkers->sem_attent_main);
        // on controle que ne se sois pas la fin
        pthread_mutex_lock(&infoWorkers->mutex);
        end = infoWorkers->end;
        pthread_mutex_unlock(&infoWorkers->mutex);

    }
}

/**
 * Cree les threads
 * @param workers structur a initialiser
 * @param population Pointeru ver la popualtion
 * @param board
 */
void newWorkers(Workers* workers, Population* population, Board* board){

    // Initialisation de la semaphore
    sem_init(&workers->infoWorkers.sem_attent_workers, 0, 0);
    sem_init(&workers->infoWorkers.sem_attent_main, 0, 0);
    // Initialisation mutex
    pthread_mutex_init(&workers->infoWorkers.mutex, NULL);

    workers->infoWorkers.end = 0;
    workers->infoWorkers.board = board;
    workers->infoWorkers.population = population;
    // Creation des workeurs
    for (int i = 0; i < NBWORKERS; ++i)
    {
        pthread_create(&workers->tab_worker[i], NULL, THREAD_FUNC(worker), (void *)&workers->infoWorkers);
    }
}

/**
 * Démmare un les thread et lance un tic de calcul a toute la population
 * @param workers
 */
void launchWorkers(Workers* workers){

    workers->infoWorkers.index_cc = workers->infoWorkers.population->populationSize - 1;
    // on lance les workers
    for(int i = 0; i < NBWORKERS; i++){
        sem_post(&workers->infoWorkers.sem_attent_workers);
    }

    // on attend que tout les workers on post
    for (int i = 0; i < NBWORKERS; ++i) {
        sem_wait(&workers->infoWorkers.sem_attent_main);
    }
}

/**
 * Détruit les threads et la structur
 * @param workers
 */
void firedWorkers(Workers* workers){

    pthread_mutex_lock(&workers->infoWorkers.mutex);
    workers->infoWorkers.end = 1;
    //efkze,j
    pthread_mutex_unlock(&workers->infoWorkers.mutex);

    // On attend la fin de tout les threads
    for (int i = 0; i < NBWORKERS; ++i)
    {
        pthread_join(workers->tab_worker[i], NULL);
    }

    // Destruction du mutex
    pthread_mutex_destroy(&workers->infoWorkers.mutex);

    sem_destroy(&workers->infoWorkers.sem_attent_main);
    sem_destroy(&workers->infoWorkers.sem_attent_workers);

}