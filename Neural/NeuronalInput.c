//
// Created by no-code-team on 10/21/17.
//
#include "NeuronalInput.h"

/**
 * Renvoie une nouvelle entrée
 * @param value Valeur de l'entrée
 * @return une nouvelle entrée
 */
NeuronalInput newNeuronalInput(double* value){

    NeuronalInput r;
    r.value = value;
    return r;
}
