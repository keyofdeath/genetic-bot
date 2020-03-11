//
// Created by no-code-team on 10/21/17.
//

#ifndef GENETIC_BOT_NEURALACTIVATION_H
#define GENETIC_BOT_NEURALACTIVATION_H

/**
 * Fonction d'activation (courbe en S) pour les neurones
 * @param value de de lasomme des produit des entrée et poid du neuron
 * @return une valeur bornée entre 0 et 1
 */
double sigmoid(double value);

#endif //GENETIC_BOT_NEURALACTIVATION_H
