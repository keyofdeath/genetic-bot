//
// Created by no-code-team on 10/22/17.
//

#ifndef GENETIC_BOT_DNANEURALNETWORK_H
#define GENETIC_BOT_DNANEURALNETWORK_H

#include "GeneDouble.h"
typedef struct{

    double min;// Valuer min que peut resevoir le reseau de neuron
    double max;// Valuer max que peut resevoir le reseau de neuron

    int geneSize;// Taille du gene

    GeneDouble* listGeneDouble;// Liste des genes
    int tailleGeneDouble;// Nombre de gene (Equivo au nombre entree du reseu de neurone)

} DnaNeuralNetwork;

/**
 * Cree un template d'un gène
 * @param dnaNeuralNetwork structure a init
 * @param min Valuer min que peut avoir un gene
 * @param max Valuer max que peut avoir un gene
 * @param geneSize Taille du gene
 * @param nbGene Nombre de gene (Equivo au nombre entree du reseu de neurone)
 */
void newDnaNeuralNetwork(DnaNeuralNetwork* dnaNeuralNetwork, double min, double max, int geneSize, int nbGene);

/**
* Ajoue un gene dans la list de l'adn
* @param dnaNeuralNetwork structure a modifier
* @param geneDouble gene a ajouter
*/
void addDnaGene(DnaNeuralNetwork* dnaNeuralNetwork, GeneDouble geneDouble);

/**
 * Cree un adn aléatoir
 * @param dnaNeuralNetwork
 */
void randomDna(DnaNeuralNetwork* dnaNeuralNetwork);

/**
 * Copie l'adn dnaSrc dans l'adn dnaDest
 * @param dnaDest
 * @param dnaSrc
 */
void setDNA(DnaNeuralNetwork* dnaDest, DnaNeuralNetwork* dnaSrc);

/**
 * Affiche l'adn util pour le debug
 * @param dnaNeuralNetwork adn a aficher
 */
void dispDna(DnaNeuralNetwork dnaNeuralNetwork);

#endif //GENETIC_BOT_DNANEURALNETWORK_H
