//
// Created by no-code-team on 10/22/17.
//
#include <stdlib.h>
#include <stdio.h>
#include "DnaNeuralNetwork.h"


/**
 * Cree un template d'un gène
 * @param dnaNeuralNetwork structure a init
 * @param min Valuer min que peut avoir un gene
 * @param max Valuer max que peut avoir un gene
 * @param geneSize Taille du gene
 * @param nbGene Nombre de gene (Equivo au nombre entree du reseu de neurone)
 */
void newDnaNeuralNetwork(DnaNeuralNetwork* dnaNeuralNetwork, double min, double max, int geneSize, int nbGene){

    dnaNeuralNetwork->min = min;
    dnaNeuralNetwork->max = max;
    dnaNeuralNetwork->geneSize = geneSize;

    dnaNeuralNetwork->tailleGeneDouble = nbGene;
    dnaNeuralNetwork->listGeneDouble = (GeneDouble*) malloc(nbGene * sizeof(GeneDouble));
}

/**
* Ajoue un gene dans la list de l'adn
* @param dnaNeuralNetwork structure a modifier
* @param geneDouble gene a ajouter
*/
void addDnaGene(DnaNeuralNetwork* dnaNeuralNetwork, GeneDouble geneDouble){

    // Si on a déja ajouter des elements on agrendi le tableau
    if (dnaNeuralNetwork->tailleGeneDouble >= 1){
        // on agrandi l'alocation
        dnaNeuralNetwork->listGeneDouble = realloc(dnaNeuralNetwork->listGeneDouble,
                                                   (dnaNeuralNetwork->tailleGeneDouble + 1) * sizeof(GeneDouble));
    }

    dnaNeuralNetwork->listGeneDouble[dnaNeuralNetwork->tailleGeneDouble++] = geneDouble;
}

/**
 * Cree un adn aléatoir
 * @param dnaNeuralNetwork
 */
void randomDna(DnaNeuralNetwork* dnaNeuralNetwork){

    int nbGene = dnaNeuralNetwork->tailleGeneDouble;

    // Si on n'a pas deja ajouter des genes dans l'adn
    if (dnaNeuralNetwork->tailleGeneDouble < nbGene){
        for (int i = 0; i < nbGene; ++i) {
            GeneDouble geneDouble = newGeneDouble(dnaNeuralNetwork->min, dnaNeuralNetwork->max, dnaNeuralNetwork->geneSize);
            randomGene(&geneDouble);
            addDnaGene(dnaNeuralNetwork, geneDouble);
        }
        // Sinon on ecrase l'ancien adn
    }else{

        for (int i = 0; i < nbGene; ++i) {
            GeneDouble geneDouble = newGeneDouble(dnaNeuralNetwork->min, dnaNeuralNetwork->max, dnaNeuralNetwork->geneSize);
            randomGene(&geneDouble);
            dnaNeuralNetwork->listGeneDouble[i] = geneDouble;
        }
    }
}

/**
 * copie l'adn dnaSrc dans l'adn dnaDest
 * @param dnaDest
 * @param dnaSrc
 */
void setDNA(DnaNeuralNetwork* dnaDest, DnaNeuralNetwork* dnaSrc){

    dnaDest->min = dnaSrc->min;
    dnaDest->max = dnaDest->max;
    dnaDest->geneSize = dnaSrc->geneSize;

    dnaDest->tailleGeneDouble = dnaSrc->tailleGeneDouble;
    dnaDest->listGeneDouble = (GeneDouble*) malloc(dnaSrc->tailleGeneDouble * sizeof(GeneDouble));
    // On copie le gene
    for (int i = 0; i < dnaSrc->tailleGeneDouble; ++i) {
        setGene(&dnaDest->listGeneDouble[i], &dnaSrc->listGeneDouble[i]);
    }

}

/**
 * Affiche l'adn util pour le debug
 * @param dnaNeuralNetwork adn a aficher
 */
void dispDna(DnaNeuralNetwork dnaNeuralNetwork){

    printf("DNA Neural Network:\n");
    printf("\tmin: %f\n", dnaNeuralNetwork.min);
    printf("\tmax: %f\n", dnaNeuralNetwork.max);
    printf("\tgeneSize: %d\n", dnaNeuralNetwork.geneSize);
    printf("\tnbGene: %d\n", dnaNeuralNetwork.tailleGeneDouble);
    printf("\n\tDNA Gene:\n");

    // on parcour la list des genes
    int taillGene = dnaNeuralNetwork.tailleGeneDouble;
    for (int i = 0; i < taillGene; ++i) {
        GeneDouble geneDouble = dnaNeuralNetwork.listGeneDouble[i];
        printf("\t\tGene %d:\n", i + 1);
        printf("\t\t\tSize: %d\n", geneDouble.tailleCode);
        printf("\t\t\tCode: ");

        // on parcour le code du gene
        for (int j = 0; j < geneDouble.tailleCode; ++j) {
            printf("| %f ", geneDouble.codeGene[j]);
        }
        printf("|\n");
    }

}