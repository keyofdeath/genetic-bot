//
// Created by no-code-team on 10/22/17.
//
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Tool.h"

/**
 * Initialise les fonctions aléatoire
 */
void iniRand(){
    srand(time(NULL));
}

/**
 * Renvoie un chiffre aléatoire flotan entre le min et max inclu
 * @param min
 * @param max
 * @return
 */
double rand_min_max(double min, double max){
    return min + (rand() / (RAND_MAX / (max - min)));
}

/**
 * Chiffre aleatoire entre a et b exclu
 * @param a
 * @param b chiffre max exclu
 * @return
 */
int int_rand_min_max(int a, int b){
    return rand()%(b-a) +a;
}

/**
 * Calcule l'écart type de la liste de valeur donnée
 * @param dataList Liste de valeur a traiter
 * @param length longeur de la liste donnée
 * @return L'écart type de la liste donnée
 */
double std(const double* dataList, int length){

    double sum = 0.0;
    // Somme
    for (int i = 0; i < length; ++i)
        sum += dataList[i];
    // Moyene
    double mean = sum / (double)length;
    double diff, varsum = 0.0;
    // Variance
    for (int i = 0; i < length; ++i) {
        diff = dataList[i] - mean;
        varsum += pow(diff, 2);
    }
    // Ecart tipe
    return sqrt(varsum / (double)length);
}

/**
 * Convertisseur chaine de character vers double
 * @param input Chaine a converir
 * @param output double converti
 * @return 1 pas erreur sinon -1
 */
int stringToDouble(const char * input, double* output){

    char *end;

    *output = strtod (input, &end);

    if (end == input) {
        printf("is not a valid number.\n");
        return -1;
    }else{
        return 1;
    }
}

/**
 * Fonction et enregistre l'adn dans un fichier
 * PS: Vue que notre code gene double de fait que de 1 double cette fontion n'écrira que le premier double
 * Donc si vous rajouter un double dans GeneDouble pensser a la modifire en conséquence
 * @param name
 * @param dna
 * @return 1 pas erreur sinon -1
 */
int saveDna(const char* name, DnaNeuralNetwork dna){


    FILE* fichier;

    fichier = fopen(name, "w");

    if (fichier != NULL){

        for (int i = 0; i < dna.tailleGeneDouble; i++)//On parcoure notre scructure
        {
            fprintf(fichier, "%f\n", dna.listGeneDouble[i].codeGene[0]);//Ecriture du score
        }

        fclose(fichier);

        return 1;

    }
    else{
        printf("Erreur ouverture du ficher score!\n");
    }

    return 0;

}

/**
 * Charche un adn d'un fichier donnée
 * @param name chemin et nom du fichier a lire
 * @param dna adn a initialiser
 * @return 1 pas erreur sinon -1
 */
int loadDan(const char* name, DnaNeuralNetwork* dna){

    FILE* fichier;
    char buffer[128];
    double gene;
    fichier = fopen(name, "r");

    if (fichier != NULL){
        for (int i = 0; i < dna->tailleGeneDouble; ++i) {

            if (fgets(buffer, 128, fichier) == NULL)
                return -1;

            if (stringToDouble(buffer, &gene) == -1)
                return -1;

            dna->listGeneDouble[i].codeGene[0] = gene;
        }
        fclose(fichier);

        return 1;
    }
    else{

        printf("Erreur ouverture du ficher score!\n");
        return -1;
    }

}

/**
 * Simple boite de dialog
 * @param title tire de la boite
 * @param text message
 * @param window fenêtre pêre
 */
void messageBox(gchar* title, gchar* text, GtkWidget* window){

    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons (title,
                                          GTK_WINDOW(window),
                                          flags,
                                          "_OK",
                                          GTK_RESPONSE_NONE,
                                          NULL);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new (text);

    // Ensure that the dialog box is destroyed when the user responds

    g_signal_connect_swapped (dialog,
                              "response",
                              G_CALLBACK (gtk_widget_destroy),
                              dialog);

    // Add the label, and show everything we’ve added

    gtk_container_add (GTK_CONTAINER (content_area), label);
    gtk_widget_show_all (dialog);

}

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
gchar *get_dialog_path_selection(gchar *type, gchar *initial_dir, gchar *initial_file, GtkWidget* window){
    GtkWidget *dialog;
    gboolean ret = 0;
    int dlg_ret = 0;
    gchar *path;

    if( strstr(type, "DIR") )
    {
        dialog = gtk_file_chooser_dialog_new("Select directory",
                                             GTK_WINDOW(window),
                                             GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                             "_Cancel", GTK_RESPONSE_CANCEL,
                                             "_Open", GTK_RESPONSE_ACCEPT,
                                             NULL);

        /* Set initial directory. If it doesnt exist "/" is used. */
        ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), initial_dir);
        if( ! ret )
            ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "/");
    }
    else
    if( strstr(type, "FILE") )
    {
        dialog = gtk_file_chooser_dialog_new("Select file",
                                             GTK_WINDOW(window),
                                             GTK_FILE_CHOOSER_ACTION_OPEN,
                                             "_Cancel", GTK_RESPONSE_CANCEL,
                                             "_Open", GTK_RESPONSE_ACCEPT,
                                             NULL);

        /* Set initial directory. If it doesnt exist "/" is used. */
        ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), initial_dir);
        if( ! ret )
            ret = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "/");

        /* It complains if the file doesnt exist, ignore it. */
        gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), initial_file);
    }
    else
    {
        printf("Path selection: Input TYPE error.\n");
        return NULL;
    }

    dlg_ret = gtk_dialog_run(GTK_DIALOG(dialog));

    if( dlg_ret == GTK_RESPONSE_ACCEPT )
    {
        path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }

    if( dlg_ret == GTK_RESPONSE_CANCEL )
    {
        printf("Path selection: Canceled.\n");
        path = NULL;
    }

    gtk_widget_destroy(dialog);

    return path;
}