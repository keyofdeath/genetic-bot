//
// Created by no-code-team on 10/21/17.
//

#ifndef GENETIC_BOT_NEURONALINPUT_H
#define GENETIC_BOT_NEURONALINPUT_H

/**
 * Structur d'une entrée
 */
typedef struct {

    // Pointeur vers la valeur cela permaus de lié l'entree du réseau au un autre objet
    double* value;

} NeuronalInput;

/**
 * Renvoie une nouvelle entrée
 * @param value Valeur de l'entrée
 * @return une nouvelle entrée
 */
NeuronalInput newNeuronalInput(double* value);

#endif //GENETIC_BOT_NEURONALINPUT_H
