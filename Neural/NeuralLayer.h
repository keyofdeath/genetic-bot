//
// Created by no-code-team on 10/21/17.
//

#ifndef GENETIC_BOT_NEURALLAYER_H
#define GENETIC_BOT_NEURALLAYER_H

#include "Neuron.h"

/**
 * Structur d'une couche neuronal
 */
typedef struct {

    Neuron* neuronList;// List des neurons dans la couche
    int tailleNeuronList;// Taille de la liste des neurones

} NeuralLayer;

/**
 * Cree une nouvelle couche de neurone
 * @param neuralLayer Structur a initialiser
 * @param nbNeuron Nombre de neurone dans la couche
 * @param activationFonction Fonction d'activation pour les neuronje dans la couche
 */
void newNeuralLayer(NeuralLayer* neuralLayer, int nbNeuron, ActivationFonction activationFonction);

/**
 * Lance un calcule sur chaque neurone de la couche donnée
 * @param neuralLayer
 */
void calculateLayer(NeuralLayer* neuralLayer);

/**
 * Ajoue un neurone dans la couche
 * @param neuralLayer Structur de la couche
 * @param neuron Neuron a ajouter
 */
void addNeuron(NeuralLayer* neuralLayer, Neuron neuron);

#endif //GENETIC_BOT_NEURALLAYER_H
