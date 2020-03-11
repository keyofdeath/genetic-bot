//
// Created by no-code-team on 10/21/17.
//
#ifndef GENETIC_BOT_NEURALNETWORK_H
#define GENETIC_BOT_NEURALNETWORK_H

#include "NeuronalInput.h"
#include "NeuralLayer.h"
#include "NeuralActivation.h"
#include "../Genetic/DnaNeuralNetwork.h"

/**
 * Structur du reseau de neurone
 */
typedef struct{

    NeuronalInput* neuronalInput;// List des entrées du réseau de neurone
    int tailleNeuronalInput;

    // Les couche sont numéroter de 1 a n
    NeuralLayer* neuralLayer;// List des couches du réseau de neurone
    int tailleNeuralLayer;

    double maxValue;// Valuer max que peut resevoir le reseau de neuron

} NeuronalNetwork;

/**
 * init le reseu de neurone
 * @param neuronalNetwork Structur a initialiser
 * @param maxValue Valuer max que peut resevoir le reseau de neuron
 */
void newNeuronalNetwork(NeuronalNetwork* neuronalNetwork, double maxValue);

/**
 * Ajoue une entree au reseu
 * @param neuronalNetwork Reseau a modifier
 * @param neuronalInput Entrée a ajouter
 */
void addInput(NeuronalNetwork* neuronalNetwork, NeuronalInput neuronalInput);

/**
 * Ajoute une couche au reseau
 * @param neuronalNetwork Reseau a modifier
 * @param neuralLayer couche neuronal a ajouter
 */
void addLayer(NeuronalNetwork* neuronalNetwork, NeuralLayer neuralLayer);

/**
 * Connect tout les entrée du reseau a la prtemière couche de neurone
 * @param neuronalNetwork Reseau a modifier
 */
void connectAllInputOnFirstLayer(NeuronalNetwork* neuronalNetwork);

/**
 * Connect les sortie de la couche de neuron a celle qui est apres
 * @param neuronalNetwork Reseau a modifier
 * @param couche couche a connecter a la couche d'après (Les couche sont numéroter de 1 a n)
 * Exemple: Si couche = 1 alors la sortie des neurons de la couche 1 seron connect a l'entree des neurons de la couche 2
 * @return 1 couche connecter -1 erreur
 */
int connectLayer(NeuronalNetwork* neuronalNetwork, int couche);

/**
 * Genère un adn qui corespon au nombre d'entree du reseau
 * @param neuronalNetwork Reseau
 * @return Un ADN
 */
DnaNeuralNetwork generateDnaModel(NeuronalNetwork neuronalNetwork);

/**
 * Ajoute au reseu de neurone l'adn donee
 * @param neuronalNetwork
 * @param dnaNeuralNetwork adn a ajouter
 */
void initFromDna(NeuronalNetwork* neuronalNetwork, DnaNeuralNetwork dnaNeuralNetwork);

/**
 * Affiche un resumer de l'eta du reseu util pour un debug
 * @param neuronalNetwork Reseau a afficher
 */
void dispNetwork(NeuronalNetwork neuronalNetwork);

/**
 * Lance un calcule du reseu de neurone
 * @param neuronalNetwork
 */
void calculateNetwork(NeuronalNetwork* neuronalNetwork);

/**
 * Recupaire la sortie des neurone de la derrnier couche du reseau
 * @param neuronalNetwork
 * @param res Liste des sortie des neurones de la derrnier couche
 */
void getNetworkResultList(NeuronalNetwork* neuronalNetwork, double* res);
#endif //GENETIC_BOT_NEURALNETWORK_H
