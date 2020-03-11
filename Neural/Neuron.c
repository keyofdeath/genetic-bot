#include <stdlib.h>
#include "Neuron.h"

//
// Created by no-code-team on 10/21/17.
//

/**
 * Renvoie un nouveau neuron
 * @param activationFonction Fonction d'activation
 * @return un nouveau neuron
 */
Neuron newNeuron(ActivationFonction activationFonction){

    Neuron n;
    n.activationFonction = activationFonction;
    n.newOutput = 0.0;
    n.output = 0.0;
    n.threshold = 0.0;
    n.tailleInput = 0;
    n.listInput = (NeuronalInput**)malloc(sizeof(NeuronalInput));
    n.listWeight = (double *)malloc(sizeof(double));
    n.tailleNeuronList = 0;
    n.listNeuron = (Neuron**)malloc(sizeof(Neuron));
    return n;
}

/**
 * Connect une entrée au neurone
 * @param neuron Neuron a modidfier
 * @param neuronalInput Entrée a connecter
 */
void connectInput(Neuron* neuron ,NeuronalInput* neuronalInput){

    if (neuron->tailleInput >= 1){

        neuron->listInput = realloc(neuron->listInput,
                                    (neuron->tailleInput + 1) * sizeof(NeuronalInput));

        neuron->listWeight = realloc(neuron->listWeight,
                                     //  neuron->tailleInput + neuron->tailleNeuronList + 1 car ce tableau
                                     // et en commun avec le tableau de sortie de neuron relier a l'entree de ce neuron
                                    (neuron->tailleInput + neuron->tailleNeuronList + 1) * sizeof(NeuronalInput));

    }

    neuron->listInput[neuron->tailleInput] = neuronalInput;
    neuron->listWeight[neuron->tailleInput++] = 0.0;
}

/**
 * Connect un neuron de la couche présédent a se neuron
 * @param neuron Neuron qui qui dois être connect
 * @param neuronToconnect Neuron de la couche précéden a connect
 */
void connectNeuron(Neuron* neuron, Neuron* neuronToconnect){

    if (neuron->tailleNeuronList >= 1){

        neuron->listNeuron = realloc(neuron->listNeuron,
                                    (neuron->tailleNeuronList + 1) * sizeof(Neuron));

        neuron->listWeight = realloc(neuron->listWeight,
                //  neuron->tailleInput + neuron->tailleNeuronList + 1 car ce tableau
                // et en commun avec le tableau de sortie de neuron relier a l'entree de ce neuron
                                     (neuron->tailleInput + neuron->tailleNeuronList + 1) * sizeof(NeuronalInput));
    }

    neuron->listNeuron[neuron->tailleNeuronList++] = neuronToconnect;
    neuron->listWeight[neuron->tailleInput++] = 0.0;

}

/**
 * Lance un calcule du neuronne
 * @param neuron
 */
void calculateNeuron(Neuron* neuron){

    if (neuron->tailleInput > 0 || neuron->tailleNeuronList > 0){

        double res = neuron->threshold * (-1);
        if (neuron->tailleInput > 0){

            for (int i = 0; i < neuron->tailleInput; ++i) {

                res += *neuron->listInput[i]->value * neuron->listWeight[i];
            }
        }

        if (neuron->tailleNeuronList > 0){

            for (int i = 0; i < neuron->tailleNeuronList; ++i) {
                res += neuron->listNeuron[i]->output * neuron->listWeight[i];
            }
        }

        neuron->newOutput = neuron->activationFonction(res);
        neuron->output = neuron->newOutput;

    }

}