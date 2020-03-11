//
// Created by no-code-team on 10/21/17.
//
#include <stdlib.h>
#include <stdio.h>
#include "NeuralNetwork.h"

/**
 * init le reseu de neurone
 * @param neuronalNetwork Structur a initialiser
 * @param maxValue
 */
void newNeuronalNetwork(NeuronalNetwork* neuronalNetwork, double maxValue){

    neuronalNetwork->maxValue = maxValue;

    // Init des couches
    neuronalNetwork->tailleNeuralLayer = 0;
    neuronalNetwork->neuralLayer = (NeuralLayer*) malloc(1 * sizeof(NeuralLayer));

    // Init de la liste des entrée
    neuronalNetwork->tailleNeuronalInput = 0;
    neuronalNetwork->neuronalInput = (NeuronalInput*) malloc(1 * sizeof(NeuronalInput));

}

/**
 * Ajoue une entree au reseu
 * @param neuronalNetwork Reseau a modifier
 * @param neuronalInput Entrée a ajouter
 */
void addInput(NeuronalNetwork* neuronalNetwork, NeuronalInput neuronalInput){

    // Si on a déja ajouter des elements on agrendi le tableau
    if (neuronalNetwork->tailleNeuronalInput >= 1){
        // on agrandi l'alocation
        neuronalNetwork->neuronalInput = realloc(neuronalNetwork->neuronalInput,
                                                 (neuronalNetwork->tailleNeuronalInput + 1) * sizeof(NeuronalInput));
    }

    neuronalNetwork->neuronalInput[neuronalNetwork->tailleNeuronalInput++] = neuronalInput;

}

/**
 * Ajoute une couche au reseau
 * @param neuronalNetwork Reseau a modifier
 * @param neuralLayer couche neuronal a ajouter
 */
void addLayer(NeuronalNetwork* neuronalNetwork, NeuralLayer neuralLayer){

    // Si on a déja ajouter des elements on agrendi le tableau
    if (neuronalNetwork->tailleNeuralLayer >= 1){
        // on agrandi l'alocation
        neuronalNetwork->neuralLayer = realloc(neuronalNetwork->neuralLayer,
                                                 (neuronalNetwork->tailleNeuralLayer + 1) * sizeof(NeuralLayer));
    }

    neuronalNetwork->neuralLayer[neuronalNetwork->tailleNeuralLayer++] = neuralLayer;

}

/**
 * Connect tout les entrée du reseau a la prtemière couche de neurone
 * @param neuronalNetwork Reseau a modifier
 */
void connectAllInputOnFirstLayer(NeuronalNetwork* neuronalNetwork){

    if (neuronalNetwork->tailleNeuralLayer >= 1){

        // on parcour notre liste de neurone de la première couche
        for (int i = 0; i < neuronalNetwork->neuralLayer[0].tailleNeuronList; ++i) {

            // notre list d'entree
            for (int j = 0; j < neuronalNetwork->tailleNeuronalInput; ++j) {

                // on connect les entrees
                connectInput(&neuronalNetwork->neuralLayer[0].neuronList[i], &neuronalNetwork->neuronalInput[j]);
            }
        }
    }
}

/**
 * Connect les sortie de la couche de neuron a celle qui est apres
 * @param neuronalNetwork Reseau a modifier
 * @param couche couche a connecter a la couche d'après (Les couche sont numéroter de 1 a n)
 * Exemple: Si couche = 1 alors la sortie des neurons de la couche 1 seron connect a l'entree des neurons de la couche 2
 * @return 1 couche connecter -1 erreur
 */
int connectLayer(NeuronalNetwork* neuronalNetwork, int couche){

    if (neuronalNetwork->tailleNeuralLayer > 1 && couche >= 1 && couche <= neuronalNetwork->tailleNeuralLayer){
        // enlève 1 cra les liste index de 0 a n et nous c'est de 1 a n
        couche--;

        // On parcour la couche suivent la var couche
        for (int i = 0; i < neuronalNetwork->neuralLayer[couche + 1].tailleNeuronList; ++i) {

            // on parcour la var couche
            for (int j = 0; j < neuronalNetwork->neuralLayer[couche].tailleNeuronList; ++j) {

                // Enfon on connect le neuron de la couche suivent a selui de la couche demander
                connectNeuron(&neuronalNetwork->neuralLayer[couche + 1].neuronList[i],
                              &neuronalNetwork->neuralLayer[couche].neuronList[j]);
            }
        }
        return 1;

    }
    return -1;
}

/**
 * Genère un adn qui corespon au nombre d'entree du reseau
 * @param neuronalNetwork Reseau
 * @return Un ADN
 */
DnaNeuralNetwork generateDnaModel(NeuronalNetwork neuronalNetwork){

    int nbLayer = neuronalNetwork.tailleNeuralLayer;
    int nbEntree = 0;
    for (int i = 0; i < nbLayer; ++i) {
        int nbNeuron = neuronalNetwork.neuralLayer[i].tailleNeuronList;
        for (int j = 0; j < nbNeuron; ++j) {
            //  + 1 car il y a le bias node
            nbEntree += neuronalNetwork.neuralLayer[i].neuronList[j].tailleInput + 1;
        }
    }
    DnaNeuralNetwork dnaNeuralNetwork;
    newDnaNeuralNetwork(&dnaNeuralNetwork, neuronalNetwork.maxValue * (-1), neuronalNetwork.maxValue, 1, nbEntree);
    return dnaNeuralNetwork;

}

/**
 * Ajoute au reseu de neurone l'adn donee
 * @param neuronalNetwork
 * @param dnaNeuralNetwork adn a ajouter
 */
void initFromDna(NeuronalNetwork* neuronalNetwork, DnaNeuralNetwork dnaNeuralNetwork){

    int nbCouhe = neuronalNetwork->tailleNeuralLayer;
    // Chaque input aurat un poid différent
    int geneIndex = 0;
    // Parcour la liste des couches
    for (int couche = 0; couche < nbCouhe; ++couche) {
        int nbNeuron = neuronalNetwork->neuralLayer[couche].tailleNeuronList;
        // On parcour tout les neurone de la couche
        for (int neuronI = 0; neuronI < nbNeuron; ++neuronI) {
            Neuron* neuron = &neuronalNetwork->neuralLayer[couche].neuronList[neuronI];
            int nbWeight = neuron->tailleInput;
            // On parcour la liste des poids des entree pour les inites de l'adn donee
            for (int k = 0; k < nbWeight; ++k) {
                // Enfin on ajoute le poid a l'entree on donne un pointeur comme sa sir le gene change le spoins aussi
                //                                        list des genes            0 car il y a que une valeur par gene
                neuron->listWeight[k] = dnaNeuralNetwork.listGeneDouble[geneIndex++].codeGene[0];
            }
            // on set sa fonction d'activation
            GeneDouble geneDouble = dnaNeuralNetwork.listGeneDouble[geneIndex++];
            neuron->threshold = geneDouble.codeGene[0] * neuron->tailleInput;
        }
    }
}

/**
 * Lance un calcule du reseu de neurone
 * @param neuronalNetwork
 */
void calculateNetwork(NeuronalNetwork* neuronalNetwork){

    for(int i = 0; i < neuronalNetwork->tailleNeuralLayer; i++){
        calculateLayer(&neuronalNetwork->neuralLayer[i]);
    }

}

/**
 * Recupaire la sortie des neurone de la derrnier couche du reseau
 * @param neuronalNetwork
 * @param res Liste des sortie des neurones de la derrnier couche
 */
void getNetworkResultList(NeuronalNetwork* neuronalNetwork, double* res){

    int lastLayer = neuronalNetwork->tailleNeuralLayer - 1;
    NeuralLayer* layer = &neuronalNetwork->neuralLayer[lastLayer];
    //res = (double*)malloc(layer->tailleNeuronList * sizeof(double));
    for (int i = 0; i < layer->tailleNeuronList; ++i) {
        res[i] = layer->neuronList[i].output;
    }
    // printf("\n ok 1 = %f, 2 = %f\n", res[0], res[1]);

}

/**
 * Affiche un resumer de l'eta du reseu util pour un debug
 * @param neuronalNetwork Reseau a afficher
 */
void dispNetwork(NeuronalNetwork neuronalNetwork){

    int nbInput = neuronalNetwork.tailleNeuronalInput;
    int nbCouhe = neuronalNetwork.tailleNeuralLayer;

    printf("Input of the network:\n");
    for (int i = 0; i < nbInput; ++i) {
        printf("\tInput %d: value = %f\n", i + 1, *neuronalNetwork.neuronalInput[i].value);
    }

    // Couche
    printf("\nLayer of the network:\n");
    for (int i = 0; i < nbCouhe; ++i) {

        // Neurone de la couche
        printf("\tLayer %d:\n", i + 1);
        int nbNeuron = neuronalNetwork.neuralLayer[i].tailleNeuronList;
        for (int j = 0; j < nbNeuron; ++j) {

            Neuron neuronCC = neuronalNetwork.neuralLayer[i].neuronList[j];
            printf("\t\tNeural %d: output = %f threshold=  %f\n", j + 1, neuronCC.output, neuronCC.threshold);

            printf("\t\t\t Input value:\n");
            // Input du neuron
            for (int k = 0; k < neuronCC.tailleInput; ++k) {
                printf("\t\t\t\t input %d: value %f weight %f\n", k + 1, *neuronCC.listInput[k]->value, neuronCC.listWeight[k]);
            }

            printf("\t\t\t Connection neural:\n");
            for (int k = 0; k < neuronCC.tailleNeuronList; ++k) {
                printf("\t\t\t\t neural connect output %d: %f\n", k + 1, neuronCC.listNeuron[k]->output);
            }
        }
        printf("\n");
    }

}