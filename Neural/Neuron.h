//
// Created by no-code-team on 10/21/17.
//

#ifndef GENETIC_BOT_NEURON_H
#define GENETIC_BOT_NEURON_H

#include "NeuronalInput.h"

// Fonction d'activation du neurone
typedef double (*ActivationFonction)(double);

typedef struct NeuronS Neuron;

/**
 * Structur d'un neuron
 */
struct NeuronS{

    double threshold;// Seuil d'activation par defaut a 0.0
    double output;
    double newOutput;
    ActivationFonction activationFonction;

    NeuronalInput** listInput;// Liste des entrées connectée au neurone
    // Lists Poids des entrées
    double* listWeight;
    int tailleInput;

    // Un neurone peut avoir la sortie d'un autre neuron comme entrée
    Neuron** listNeuron;
    int tailleNeuronList;

};

/**
 * Renvoie un nouveau neuron
 * @param activationFonction Fonction d'activation
 * @return un nouveau neuron
 */
Neuron newNeuron(ActivationFonction activationFonction);

/**
 * Connect une entrée au neurone
 * @param neuron Neuron a modidfier
 * @param neuronalInput Entrée a connecter
 */
void connectInput(Neuron* neuron ,NeuronalInput* neuronalInput);

/**
 * Connect un neuron de la couche présédent a se neuron
 * @param neuron Neuron qui qui dois être connect
 * @param neuronToconnect Neuron de la couche précéden a connect
 */
void connectNeuron(Neuron* neuron, Neuron* neuronToconnect);

/**
 * Lance un calcule du neuronne
 * @param neuron
 */
void calculateNeuron(Neuron* neuron);

#endif //GENETIC_BOT_NEURON_H
