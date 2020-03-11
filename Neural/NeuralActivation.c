//
// Created by no-code-team on 10/21/17.
//
#include "NeuralActivation.h"
#include <math.h>

/**
 * Fonction d'activation (courbe en S) pour les neurones
 * @param value de de lasomme des produit des entrée et poid du neuron
 * @return une valeur bornée entre 0 et 1
 */
double sigmoid(double value){
    return 1.0 / (1.0 + exp(value * -1));
}