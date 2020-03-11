//
// Created by no-code-team on 10/21/17.
//

#include <stdlib.h>
#include "NeuralLayer.h"

/**
 * Cree une nouvelle couche de neurone
 * @param neuralLayer Structur a initialiser
 * @param nbNeuron Nombre de neurone dans la couche
 * @param activationFonction Fonction d'activation pour les neuronje dans la couche
 */
void newNeuralLayer(NeuralLayer* neuralLayer, int nbNeuron, ActivationFonction activationFonction){

    neuralLayer->tailleNeuronList = nbNeuron;
    neuralLayer->neuronList = (Neuron*) malloc(nbNeuron * sizeof(Neuron));

    for (int i = 0; i < nbNeuron; ++i) {
        neuralLayer->neuronList[i] = newNeuron(activationFonction);
    }

}

/**
 * Lance un calcule sur chaque neurone de la couche donnée
 * @param neuralLayer
 */
void calculateLayer(NeuralLayer* neuralLayer){

    for (int i = 0; i < neuralLayer->tailleNeuronList; ++i)
        calculateNeuron(&neuralLayer->neuronList[i]);
}

/**
 * Ajoue un neurone dans la couche
 * @param neuralLayer Structur de la couche
 * @param neuron Neuron a ajouter
 */
void addNeuron(NeuralLayer* neuralLayer, Neuron neuron){

    if (neuralLayer->tailleNeuronList >= 1){

        neuralLayer->neuronList = realloc(neuralLayer->neuronList,
                                          (neuralLayer->tailleNeuronList + 1) * sizeof(Neuron));
    }
    neuralLayer->neuronList[neuralLayer->tailleNeuronList++] = neuron;
}