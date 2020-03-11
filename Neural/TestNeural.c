//
// Created by no-code-team on 10/22/17.
//
#include "NeuralNetwork.h"
#include "TestNeural.h"
#include <stdio.h>

void testNeural(){

    double input_val = 10;
    printf("**************TEST FUNCTION**************\n\n");

    NeuronalNetwork neuronalNetwork;
    NeuralLayer neuralLayer, neuralLayer2;// Seul couche de notre réseau

    // creation du reseu
    newNeuronalNetwork(&neuronalNetwork, 5.0);

    // ajoue des entree
    for (int i = 0; i < 10; ++i) {
        addInput(&neuronalNetwork, newNeuronalInput(&input_val));
    }

    // On cree une couche qui est composer de 2 neuron qui on comme fonction d'activatio sigmoid
    newNeuralLayer(&neuralLayer, 2, sigmoid);
    // puis une couche de 1 neuron
    newNeuralLayer(&neuralLayer2, 1, sigmoid);

    // on lajout au réseau
    addLayer(&neuronalNetwork, neuralLayer);
    addLayer(&neuronalNetwork, neuralLayer2);

    // on connect tout les entrée a la premère couche du reseau
    connectAllInputOnFirstLayer(&neuronalNetwork);
    // connnect les deux couche entre elle (la sortie de la 1 a l'entree de la 2)
    connectLayer(&neuronalNetwork, 1);

    printf("Affichage du reseau\n");

    dispNetwork(neuronalNetwork);

    printf("Modification de l'input ver la valeur 42.42\n");
    input_val = 42.42;

    printf("Modification output du neuron 1 couche 1 vers 142.42");
    neuronalNetwork.neuralLayer[0].neuronList[0].output = 142.42;

    printf("\nAffichage du reseau modifier\n");

    dispNetwork(neuronalNetwork);

}
