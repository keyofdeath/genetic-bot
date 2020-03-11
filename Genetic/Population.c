//
// Created by no-code-team on 10/23/17.
//
#include <stdlib.h>
#include "Population.h"
#include "../Tool/Tool.h"

/**
 * Génère un reseau de neuronne
 * @return reau de neuronne initialiser
 */
NeuronalNetwork make_neuronalNetwork(){

    // valeru par defaut d'une entree du reseau
    double def = DEFAULT_INPUT_VALUE;
    NeuronalNetwork neuronalNetwork;
    NeuralLayer neuralLayer;
    newNeuronalNetwork(&neuronalNetwork, 5.0);

    // ajoue des entree +1 car il y a la vitesse de la voiture en plus des 8 capteur laser
    for (int i = 0; i < NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE; ++i) {
        addInput(&neuronalNetwork, newNeuronalInput(&def));
    }

    // On cree une couche qui est composer de 2 neuron qui on comme fonction d'activation sigmoid
    newNeuralLayer(&neuralLayer, NB_NEURAL, sigmoid);
    // on lajout au réseau
    addLayer(&neuronalNetwork, neuralLayer);

    // on connect tout les entrée a la premère couche du reseau
    connectAllInputOnFirstLayer(&neuronalNetwork);
    return neuronalNetwork;

}

/**
 * Init une population
 * @param population Structur a init
 * @param populationSize Taille de la population
 * @param neuronalNetwork Reseau de neurone pour gene l'adn
 */
void newPopulation(Population* population, int populationSize, Board* board){

    population->populationSize = populationSize;
    population->individualList = (Robot*)malloc(populationSize * sizeof(Robot));
    population->generation = 0;

    for (int i = 0; i < populationSize; ++i) {

        NeuronalNetwork neuronalNetwork = make_neuronalNetwork();
        // On gener un adn qui corespon au reseau de neuone
        DnaNeuralNetwork dnaNeuralNetwork = generateDnaModel(neuronalNetwork);
        // On cree un adn aleatoir
        randomDna(&dnaNeuralNetwork);
        // puis on cree un nouvelle individu
        newRobot(&population->individualList[i], newIndividual(dnaNeuralNetwork), neuronalNetwork, board);
    }

}

/**
 * Ajoute un individu dans le population
 * PS: L'individu est init avec un adn aléatoire
 * @param population
 * @param board
 */
void addIndividual(Population* population, Board* board){

    // on agrendi notre population
    population->individualList = realloc(population->individualList, ++population->populationSize * sizeof(Robot));
    NeuronalNetwork neuronalNetwork = make_neuronalNetwork();
    // On gener un adn qui corespon au reseau de neuone
    DnaNeuralNetwork dnaNeuralNetwork = generateDnaModel(neuronalNetwork);
    // On cree un adn aleatoir
    randomDna(&dnaNeuralNetwork);
    // puis on cree un nouvelle individu
    newRobot(&population->individualList[population->populationSize-1],
             newIndividual(dnaNeuralNetwork), neuronalNetwork, board);
}

/**
 * Obtien le ecore du robot donnée
 * @param robot
 * @return le score du robot
 */
int getScore(Robot robot){

    int score = 1;

    if (robot.individual.hit_goal){
        // on converti le temps en seconde et on retir du score le temps mis en seconde et du nombre obstacle toucher
        score += HIT_GOAL - ((robot.individual.time_to_goal / 1000) * POINT_LOSE_PER_S);
    }else{
        double val = std(robot.individual.dist_pick, MAX_TIME/TIME_DATA_PICK);
        // En fonction de la diversiter des mouvements du robot on augmente son score
        // c'est util pour suprimmer les robots qui ne bouge pas
        if (val > 0.06)
            score += SCORE_NOT_HIT;
        else if(val > 0.02)
            score += SCORE_NOT_HIT / 2;
        else
            score += SCORE_NOT_HIT / 4;
        score -= robot.individual.nb_hit_obstacle * POINT_LOSE_PER_HIT;
    }

    // Petit controle que le sore ne sois pas négatif
    if(score <= 0)
        score = 1;

    return score;

}

/**
 * Atribut un score a tout la population
 * @param population
 */
void setPopulationScore(Population* population){

    for(int i = 0; i < population->populationSize; i++){

        population->individualList[i].individual.score = getScore(population->individualList[i]);
        if (DEBUG)
            printf("Score individu %d: %d\nEcar type distance %f\n", i + 1,
                   population->individualList[i].individual.score,
                   std(population->individualList[i].individual.dist_pick, MAX_TIME/TIME_DATA_PICK));
    }
}

/**
 * Selection a l'aide de la méthode de rejet
 * @param population
 * @return index de l'individu choisie
 */
int selection(Population* population){

    int index;

    while (1){
        // on recupaire un individu aléatoirement dans notre population
        index = int_rand_min_max(0, population->populationSize);
        Robot* robot = &population->individualList[index];
        // Si le score du robot est plus garnd le nombre aléatoire tirée on choisie cette individu
        if(int_rand_min_max(0, HIT_GOAL + 1) < robot->individual.score)
            return index;
    }

}

/**
 * Selection un robot parmi la liste des meilleurs robot choisi
 * @param population
 * @param bestRobot List qui contien la position des meilleurs robot dans la population
 * @param top_best_robot Taille de la liste bestRobot
 * @return index de la liste bestRobot
 */
int selectionBestRobot(Population* population, const int* bestRobot, const int top_best_robot){

    int index;
    while (1){
        // on choisie un de nos meilleur robot
        index = int_rand_min_max(0, top_best_robot + 1);
        // on recupaire sa struct dans notre population
        Robot* robot = &population->individualList[bestRobot[index]];
        // Si le score du robot est plus garnd le nombre aléatoire tirée on choisie cette individu
        if(int_rand_min_max(0, HIT_GOAL + 1) < robot->individual.score)
            return index;
    }

}

/**
 * Fait un croisement entre deux individu
 * @param individual1
 * @param individual2
 * @param child Nouvelle individu
 */
void crossover(Individual individual1, Individual individual2, DnaNeuralNetwork* child){

    // On cree un fils avec l'adn de l'individu 1
    setDNA(child, &individual1.dnaNeuralNetwork);
    // On prend un point aléatoire sur la longeurdu gene pour voir ou on dois commencer a mètre le gène 2
    int midPoint = int_rand_min_max(0, individual1.dnaNeuralNetwork.tailleGeneDouble - 1);
    for (int i = midPoint; i < individual1.dnaNeuralNetwork.tailleGeneDouble; ++i) {
        // on remplace le gène de l'individu 1 avec le 2
        setGene(&child->listGeneDouble[i], &individual2.dnaNeuralNetwork.listGeneDouble[i]);
    }
}

/**
 * Applique une munation a l'adn donnée
 * @param dna
 */
void muation(DnaNeuralNetwork* dna){

    for (int i = 0; i < dna->tailleGeneDouble; ++i) {
        if (rand_min_max(0, 1) <= MUTATION_RATE){
            randomGene(&dna->listGeneDouble[i]);
        }
    }
}

/**
 * Fait un croisement et une mutation sur toute la population
 * @param population
 */
void geneticManipulation(Population* population){

    int index_1, index_2;
    // Liste de nos noueaux bébé yipiiiiiiiii
    DnaNeuralNetwork* newDna = (DnaNeuralNetwork*)malloc(sizeof(DnaNeuralNetwork) * population->populationSize);
    for (int i = 0; i < population->populationSize; i++){
        index_1 = selection(population);
        index_2 = selection(population);
        printf("index1 = %d **** index2 = %d\n", index_1, index_2);

        crossover(population->individualList[index_1].individual,
                  population->individualList[index_2].individual,
                  &newDna[i]);

        muation(&newDna[i]);
    }

    // Une fois toute la population faite on la mais a jours tout les bébé fait ^^
    // et on reset la position des robot
    for (int i = 0; i < population->populationSize; ++i) {

        // population->individualList[i].individual.dnaNeuralNetwork.listGeneDouble = newDna[i].listGeneDouble;
        setDNA(&population->individualList[i].individual.dnaNeuralNetwork, &newDna[i]);
        // Puis on reset le position du robot
        resetRobot(&population->individualList[i]);
    }

    free(newDna);

}

/**
 * Fait un croisement et une mutation que sur la liste des robot qui on attein un la cible
 * @param population
 * @param bestRobot Liste d'index des meilleur robot de la population
 * @param top_best_robot Taille de la liste bestRobot
 */
void copyBestRobot(Population* population, int* bestRobot, int top_best_robot){

    printf("*****************************\nBest robot manipualtion\n");
    int index_1, index_2;
    // Liste de nos noueaux bébé yipiiiiiiiii
    DnaNeuralNetwork* newDna = (DnaNeuralNetwork*)malloc(sizeof(DnaNeuralNetwork) * population->populationSize);
    for (int i = 0; i < population->populationSize; i++){
        index_1 = selectionBestRobot(population, bestRobot, top_best_robot);
        index_2 = selectionBestRobot(population, bestRobot, top_best_robot);
        printf("index1 = %d **** index2 = %d\n", index_1, index_2);

        crossover(population->individualList[index_1].individual,
                  population->individualList[index_2].individual,
                  &newDna[i]);

        setDNA(&newDna[i], &population->individualList[bestRobot[index_1]].individual.dnaNeuralNetwork);
        muation(&newDna[i]);
    }

    // Une fois toute la population faite on la mais a jours tout les bébé fait ^^
    // et on reset la position des robot
    for (int i = 0; i < population->populationSize; ++i) {

        // population->individualList[i].individual.dnaNeuralNetwork.listGeneDouble = newDna[i].listGeneDouble;
        setDNA(&population->individualList[i].individual.dnaNeuralNetwork, &newDna[i]);
        // Puis on reset le position du robot
        resetRobot(&population->individualList[i]);
    }

    free(newDna);

}

/**
 * Fait une nouvelle génération de la population donnée en appliquent la méthode
 * d'un algorithme génétique
 * @param population
 * @param board
 */
void newPopulationGeneration(Population* population){

    population->generation++;
    setPopulationScore(population);

    int* robot_hit_goal = (int*)malloc(population->populationSize * sizeof(int));
    int top_best_robot = -1;
    // On mais dans la liste robot_hit_goal tout les robot qui on atteint l'objectif
    for (int i = 0; i < population->populationSize; ++i) {

        if (population->individualList[i].individual.hit_goal){
            printf("best robot %d\n", i);
            robot_hit_goal[++top_best_robot] = i;
        }
    }

    if (MODE_COPIE && top_best_robot != -1)
        copyBestRobot(population, robot_hit_goal, top_best_robot);
    else
        geneticManipulation(population);
}

/**
 * Affiche la population util pour debug
 * @param population population a aficher
 */
void dispPopulation(Population population){
    printf("Population Size %d\n", population.populationSize);
    printf("Individual List: \n");
    for (int i = 0; i < population.populationSize; ++i) {
        printf("Individual %d:\n", i + 1);
        printf("Position: x ,%f y %f\n", population.individualList[i].position.x[0],population.individualList[i].position.x[1]);
        dispDna(population.individualList[i].individual.dnaNeuralNetwork);
        printf("******NEURAL NETWORK******\n");
        dispNetwork(population.individualList[i].neuralNetwork);
        printf("**************************\n");
    }
}