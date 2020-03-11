//
// Created by no-code-team on 10/22/17.
//

#include <stdlib.h>
#include "GeneDouble.h"
#include "../Tool/Tool.h"

/**
 * Cree un gene
 * @param min Valeur max que peut prendre le gene
 * @param max Valeur min que peut prendre le gene
 * @param size Taille du gene
 * @return Un nouveux gene
 */
GeneDouble newGeneDouble(double min, double max, int size){

    GeneDouble geneDouble;
    geneDouble.min = min;
    geneDouble.max = max;
    geneDouble.tailleCode = size;
    geneDouble.codeGene = (double*)malloc(size * sizeof(double));
    return geneDouble;

}

/**
 * Ajoute un code dans le gene
 * @param geneDouble structure a modifier
 * @param code code a ajouter
 */
void addCodeGene(GeneDouble* geneDouble, double code){

    // Si on a déja ajouter des elements on agrendi le tableau
    if (geneDouble->tailleCode >= 1){
        // on agrandi l'alocation
        geneDouble->codeGene = realloc(geneDouble->codeGene,
                                                   (geneDouble->tailleCode + 1) * sizeof(GeneDouble));
    }

    geneDouble->codeGene[geneDouble->tailleCode++] = code;

}

/**
 * Copie le gene geneDoubleSrc dans geneDoubleDest
 * @param geneDoubleDest
 * @param geneDoubleSrc
 */
void setGene(GeneDouble* geneDoubleDest, GeneDouble* geneDoubleSrc){


    geneDoubleDest->min = geneDoubleSrc->min;
    geneDoubleDest->max = geneDoubleSrc->max;
    geneDoubleDest->tailleCode = geneDoubleSrc->tailleCode;
    geneDoubleDest->codeGene = (double*)malloc(geneDoubleSrc->tailleCode * sizeof(double));

    for (int i = 0; i < geneDoubleSrc->tailleCode; ++i) {
        geneDoubleDest->codeGene[i] = geneDoubleSrc->codeGene[i];
    }
}

/**
 * Cree un gene aleatoir
 * @param geneDouble structure a modifier
 */
void randomGene(GeneDouble* geneDouble){

    // Puis on mais un code aleatoir
    for (int i = 0; i < geneDouble->tailleCode; ++i)
        geneDouble->codeGene[i] = rand_min_max(geneDouble->min, geneDouble->max);

}