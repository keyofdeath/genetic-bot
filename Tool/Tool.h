//
// Created by no-code-team on 10/22/17.
//

#ifndef GENETIC_BOT_RANDOM_H
#define GENETIC_BOT_RANDOM_H
#include <gtk/gtk.h>
#include "../Genetic/Population.h"

/**
 * Initialise les fonctions aléatoire
 */
void iniRand();

/**
 * Renvoie un chiffre aléatoire flotan entre le min et max inclu
 * @param min
 * @param max
 * @return
 */
double rand_min_max(double min, double max);

/**
 * Chiffre aleatoire entre a et b exclu
 * @param a
 * @param b chiffre max exclu
 * @return
 */
int int_rand_min_max(int a, int b);

/**
 * Calcule l'écart type de la liste de valeur donnée
 * @param dataList Liste de valeur a traiter
 * @param length longeur de la liste donnée
 * @return L'écart type de la liste donnée
 */
double std(const double* dataList, int length);

/**
 * Fonction et enregistre l'adn dans un fichier
 * PS: Vue que notre code gene double de fait que de 1 double cette fontion n'écrira que le premier double
 * Donc si vous rajouter un double dans GeneDouble pensser a la modifire en conséquence
 * @param name
 * @param dna
 * @return 1 pas erreur sinon -1
 */
int saveDna(const char* name, DnaNeuralNetwork dna);

/**
 * Charche un adn d'un fichier donnée
 * @param name chemin et nom du fichier a lire
 * @param dna adn a initialiser
 * @return 1 pas erreur sinon -1
 */
int loadDan(const char* name, DnaNeuralNetwork* dna);

/**
 * Simple boite de dialog
 * @param title tire de la boite
 * @param text message
 * @param window fenêtre pêre
 */
void messageBox(gchar* title, gchar* text, GtkWidget* window);

/**
 * Boite de dialog pour explorer les dossiers
 * @param type type de recherche
 *        DIR pour choisire un dossier
 *        FILE pou choisire un fichier
 * @param initial_dir Dossier de recherche a l'ouverur
 * @param initial_file Fichier par defaut a l'ouverur
 * @param window
 * @return Chemin du fichier ou dossier choisi
 */
gchar *get_dialog_path_selection(gchar *type, gchar *initial_dir, gchar *initial_file, GtkWidget* window);
#endif //GENETIC_BOT_RANDOM_H
