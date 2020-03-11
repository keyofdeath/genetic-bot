//
// Created by no-code-team on 10/22/17.
//

#ifndef GENETIC_BOT_GENEDOUBLE_H
#define GENETIC_BOT_GENEDOUBLE_H

typedef struct{

    double min, max;// Valeur minimu et maximum que peur avoir le gene
    double* codeGene;// Liste des codes du genes
    int tailleCode;// Taille du gene

} GeneDouble;

/**
 * Cree un gene
 * @param min Valeur max que peut prendre le gene
 * @param max Valeur min que peut prendre le gene
 * @param size Taille du gene
 * @return Un nouveux gene
 */
GeneDouble newGeneDouble(double min, double max, int size);

/**
 * Ajoute un code dans le gene
 * @param geneDouble structure a modifier
 * @param code code a ajouter
 */
void addCodeGene(GeneDouble* geneDouble, double code);

/**
 * Copie le gene geneDoubleSrc dans geneDoubleDest
 * @param geneDoubleDest
 * @param geneDoubleSrc
 */
void setGene(GeneDouble* geneDoubleDest, GeneDouble* geneDoubleSrc);

/**
 * Cree un code aleatoir
 * @param geneDouble structure a modifier
 */
void randomGene(GeneDouble* geneDouble);

#endif //GENETIC_BOT_GENEDOUBLE_H
