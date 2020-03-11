#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include "Neural/NeuralNetwork.h"
#include "Tool/Tool.h"
#include "Workers/Workers.h"

/**
 * @struct Contexte
 * Le contexte contient les informations utiles de l'interface pour
 * les algorithmes de géométrie algorithmique.
*/
typedef struct SContexte {
    int width;
    int height;
    GtkWidget* drawing_area;
    // Liste de Label pour avoir la valeur des entree du reseu de neuron
    GtkWidget** network_input;
    // label pour avoir la valeur des poids des liens du neuron 1
    GtkWidget** neural_1_weigth;
    // label pour avoir la valeur des poids des liens du neuron 1
    GtkWidget** neural_2_weigth;
    // Liste de label pour avoir la vakeur des sortie
    GtkWidget** neural_out;
    // Liste de label qui va contenir des info divers sur l'environement
    GtkWidget** label_info;
    GtkWidget* button_save;// sauvgarde
    GtkWidget* button_test;// mode test
    GtkWidget* button_normal;// mode normal
    GtkRange* gene_debug;// Reglette pour choisir un individu
    GtkWidget* window;// Fenêtres plrincipale
    Population population;// Population des robots
    Board board;// Plateau avec les obstacles
    Workers workers;// Thread
    int select_individu;// individu selectionner pour le debuger entre 1 et n
    int mode;// mode du programme voire fichier constante

} Contexte;

/**
 * @struct RGB
 * Struct pour les couleurs
 */
typedef struct{
    double r;
    double g;
    double b;
}RGB;

RGB COLOR_TARGET = {1, 1, 1};
RGB COLOR_ROBOT = {0, 0, 1};
RGB SELECT_ROBOT = {1, 0, 0};
RGB COLOR_DIRECTION = {0, 0, 0};
RGB COLOR_OBSTACLE = {0.2, 0.5, 0};
RGB COLOR_LASER = {0.2, 0.5, 1};

//                      _____________________
//_____________________/PARTIE ALGO GENERIQUE\_____________________


/**
 * Init la population
 * @param board
 * @return Population initialiser
 */
Population initSystem(Board* board){

    // creation de la population
    Population population;
    newPopulation(&population, POPULATION_SIZE, board);
    dispPopulation(population);
    return population;

}

/**
 * tick de dimualtion
 * Démare les threads pour fait un tic de calcul a toute la population
 * Mais a jours tout les labels de l'interface
 * @param pCtxt
 */
void tickSimulation(Contexte* pCtxt){
    char buffer[ 128 ];
    // on lance les workers pour qu'il déplasse les robot et les maites a jours
    launchWorkers(&pCtxt->workers);
    // on mais a jours les label du robot selectioner
    Robot* r_cc = &pCtxt->population.individualList[pCtxt->select_individu];
    // reseau du robot
    NeuronalNetwork* robo_netWork = &r_cc->neuralNetwork;
    // on mais les donnee des capteur du robot dans les entree du reseau
    for (int j = 0; j < NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE; ++j) {
        // mise a joute du label si c'est l'individu selectioner
        sprintf(buffer, "Input %d: %f", j + 1, *robo_netWork->neuronalInput[j].value);
        gtk_label_set_text(GTK_LABEL(pCtxt->network_input[j]), buffer);
        sprintf(buffer, "Weight %d neural 1: %f", j + 1, robo_netWork->neuralLayer[0].neuronList[0].listWeight[j]);
        gtk_label_set_text(GTK_LABEL(pCtxt->neural_1_weigth[j]), buffer);
        sprintf(buffer, "Weight %d neural 2: %f", j + 1, robo_netWork->neuralLayer[0].neuronList[1].listWeight[j]);
        gtk_label_set_text(GTK_LABEL(pCtxt->neural_2_weigth[j]), buffer);
    }
    sprintf( buffer, "Engine commande: %d", r_cc->engineCommand);
    gtk_label_set_text( GTK_LABEL(pCtxt->neural_out[0]), buffer);
    sprintf( buffer, "Wheel commande: %d", r_cc->wheelCommand);
    gtk_label_set_text( GTK_LABEL(pCtxt->neural_out[1]), buffer);
    sprintf( buffer, "Time spend: %d", pCtxt->board.time_spend);
    gtk_label_set_text( GTK_LABEL(pCtxt->label_info[0]), buffer);
    sprintf( buffer, "Generation: %d", pCtxt->population.generation);
    gtk_label_set_text( GTK_LABEL(pCtxt->label_info[1]), buffer);
    sprintf( buffer, "Nb obstacle toucher: %d", r_cc->individual.nb_hit_obstacle);
    gtk_label_set_text( GTK_LABEL(pCtxt->label_info[2]), buffer);

}


//                      _________
//_____________________/PARTIE UI\_____________________


//---------------------------DRAW TOOL---------------------------


/**
 * Converti l'angle donnée en radian
 * @param angle
 * @return un radian
 */
double toRand(double angle){
    return (G_PI * angle) / 180.0;
}

/**
 * Fonction de base qui affiche un disque de centre (x,y) et de rayon r via cairo.
 * @param cr
 * @param p point ou afficher
 * @param r rayon
 * @param color couleur du point
 */
void drawPoint(cairo_t* cr, Point p, double r, RGB color){
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_arc( cr, p.x[0], p.x[1], r, 0.0, 2.0 * G_PI);
    cairo_fill( cr );
}

/**
 * Desine une ligne de p a q
 * @param cr
 * @param p point de départ
 * @param q point de fin
 * @param color Couleur de la ligne
 * @param width épesseur de la ligne
 */
void drawLine(cairo_t* cr, Point p, Point q, RGB color, int width){
    static const double dashed[] = {1.0};
    cairo_set_dash(cr, dashed, 0, 1);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_set_line_width(cr, width);
    cairo_move_to(cr, p.x[0], p.x[1]);
    cairo_line_to(cr, q.x[0], q.x[1]);
    cairo_stroke( cr );
}

/**
 * Dessine un rectangle
 * @param cr
 * @param p point supèrieur gauche
 * @param width Largeur du rectangle
 * @param height Hauteur du rectangle
 * @param color Couleur
 */
void drawRec(cairo_t* cr, Point p, double width, double height, RGB color){

    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_rectangle(cr, p.x[0], p.x[1], width, height);
    cairo_fill( cr );
}

/**
 * Dessine une ligne d'une longeur donne et d'un angle donne
 * Si angle = 0 le train point dans se sense --->
 * Rotation cercle trigonometrique
 * @param cr
 * @param angle
 * @param p
 * @param length
 * @param color
 * @param width
 */
void drawLineAngle(cairo_t* cr, double angle, Point p, double length, RGB color, int width){

    double x1, y1, rad;
    Point q;
    x1 = p.x[0];
    y1 = p.x[1];
    rad = toRand(angle);
    q.x[0] = x1 + length * cos(rad);
    q.x[1] = y1 - length * sin(rad);
    drawLine(cr, p, q, color, width);
}

/**
 * Dessine un robot
 * @param cr
 * @param r Robot a afficher
 * @param select_robot 1 c'est le robot selection en debug il sera afficher d'une couleur différente
 */
void drawRobot(cairo_t* cr, Robot r, int select_robot){

    if (select_robot){
        drawPoint(cr, r.position, ROBOT_R, SELECT_ROBOT);
    } else{
        drawPoint(cr, r.position, ROBOT_R, COLOR_ROBOT);
    }
    //dessin des laser
    for (int i = 0; i < NUMBER_SENSOR_ROBOT; ++i) {
        // on cree un point au centre du robot
        Point laser_point = newPoint(r.position.x[0], r.position.x[1]);
        // puis on regard a quelle position il est a l'extrémiter du robot
        Point_add_angle(r.sensor[i].angle + r.angle, ROBOT_R, &laser_point);
        drawLineAngle(cr, r.sensor[i].angle + r.angle, laser_point, r.sensor[i].dist, COLOR_LASER, LASER_LINE_WIDTH);
    }
    // dessin la ligne qui montre la direction du robot
    drawLineAngle(cr, r.angle, r.position, ROBOT_R, COLOR_DIRECTION, ROBOT_DIRECTION_WIDTH);
}

/**
 * Dessine la popualtion
 * @param cr
 * @param population
 * @param select_individu index du robot choisi pour le debug
 */
void drawPopulation(cairo_t* cr, Population population, int select_individu){

    for (int i = 0; i < population.populationSize; ++i) {
        Robot r = population.individualList[i];
        drawRobot(cr, r, i == select_individu);
    }

}

/**
 * Dessine les obstacles
 * @param cr
 * @param board
 */
void drawObstacle(cairo_t* cr, Board board){

    for(int i = 0; i < board.nbObstacle; i++){

        drawRec(cr, board.obstacle[i].p1, board.obstacle[i].largeur, board.obstacle[i].hauteur, COLOR_OBSTACLE);
    }

    // puis on dessin la cible
    int step_r = TARGET_R / 5;
    RGB color_cc[] = {SELECT_ROBOT, COLOR_TARGET};
    int i_color_cc = 0;
    for (int r_cc = TARGET_R; r_cc >=step_r; r_cc -= step_r) {

        drawPoint(cr, board.target, r_cc, color_cc[i_color_cc]);
        i_color_cc ^= 1;
    }

}


//---------------------------TIC AFFICHAGE ET CALCUL---------------------------


/// Cette réaction est appelée à la création de la zone de dessin.
gboolean realize_evt_reaction( GtkWidget *widget, gpointer data ) {
    // force un événement "expose" juste derrière.
    gtk_widget_queue_draw(widget);
    return TRUE;
}

/// C'est la réaction principale qui est appelée pour redessiner la zone de dessin.
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data){
    Contexte* pCtxt = (Contexte*) data;
    int width, height;
    GtkStyleContext *context;
    context = gtk_widget_get_style_context (widget);
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);
    gtk_render_background (context, cr, 0, 0, width, height);
    drawPopulation(cr, pCtxt->population, pCtxt->select_individu);
    drawObstacle(cr, pCtxt->board);
    cairo_fill (cr);
    return TRUE;
}

/**
   Fonction appelée régulièrement (tous les DT secondes) et qui s'occupe de (presque tout):
   @param data correspond en fait au pointeur vers le Contexte.
*/
gint tic( gpointer data ){
    Contexte* pCtxt = (Contexte*) data;

    // Si on ateint notre limite de temps
    if (pCtxt->board.time_spend >= MAX_TIME){
        printf("***********************************\nEnd Time\n");
        pCtxt->board.time_spend = 0;
        newPopulationGeneration(&pCtxt->population);
    }

    pCtxt->board.time_spend += TICK_TIME*DT;
    tickSimulation(pCtxt);
    // Si c'est tjr en mode normal on relance un autre appel a un tic
    if (pCtxt->mode  == MODE_NORMAL)
        g_timeout_add (TICK_TIME*DT, tic, (gpointer) pCtxt ); // réenclenche le timer.
    return 0;
}

/// Tic de calcul en mode test d'adn
gint ticTestMod( gpointer data ){

    Contexte* pCtxt = (Contexte*) data;
    tickSimulation(pCtxt);
    // Si c'est tjr en mode normal on relance un autre appel a un tic
    if (pCtxt->mode  == MODE_TEST)
        g_timeout_add (TICK_TIME*DT, ticTestMod, (gpointer) pCtxt ); // réenclenche le timer.
    return 0;
}

/**
   Fonction appelée régulièrement (tous les DT_AFF secondes) et qui
   s'occupe de demander le réaffichage dela zone de dessin.
   @param data correspond en fait au pointeur vers le Contexte.
*/
gint ticAffichage( gpointer data ){

    Contexte* pCtxt = (Contexte*) data;
    // on call le draw_callback
    gtk_widget_queue_draw( pCtxt->drawing_area );
    g_timeout_add (TICK_TIME*DT_AFF, ticAffichage, (gpointer) pCtxt ); // réenclenche le timer.
    return 0;
}


//---------------------------EVENT DES OBJ DE L'INTERFACE---------------------------


/// Fcontion appeler qaund on bouge la regle pour choisir un robot
gboolean selectIndividu( GtkWidget *widget, gpointer data ){
    // Récupère le contexte.
    Contexte* pCtxt = (Contexte*) data;
    pCtxt->select_individu = (int)gtk_range_get_value(pCtxt->gene_debug);
    // -1 car dans notre liste de population on numérote de 0 a n
    pCtxt->select_individu--;
    return TRUE;
}

/**
 *  Événement lors se que on click dans la zone de dessin
 */
gboolean mouse_clic_reaction( GtkWidget *widget, GdkEventButton *event, gpointer data ){
    Contexte* pCtxt = (Contexte*) data;
    // Ajoue du seau
    double x = event->x;
    double y = event->y;
    int button = event->button;
    if (button == 1) {// Click gauche

        if (pCtxt->board.p1_set) {
            if (y > pCtxt->board.temp_y && x > pCtxt->board.temp_x){
                addObstacle(&pCtxt->board,
                            newObstacleP(newPoint(pCtxt->board.temp_x, pCtxt->board.temp_y), newPoint(x, y)));
                pCtxt->board.p1_set = 0;
            }else{
                printf("woring obstacle click\n");
            }

        } else {
            // premier click pour fair le premier point
            pCtxt->board.temp_x = x;
            pCtxt->board.temp_y = y;
            pCtxt->board.p1_set = 1;
        }
        printf("x = %f, y = %f\n", x, y);
    }else if(button == 3){// Click droit

        // on ne controle pas si le click et dans un obstacle car la fonction le fait déja
        suppObstacle(&pCtxt->board, newPoint(x, y));

    }
    return TRUE;
}

/// Mode normal applique un algorithme génétique a une population
void normalMod(GtkWidget *widget, gpointer data){

    // Récupère le contexte.
    Contexte* pCtxt = (Contexte*) data;
    pCtxt->population = initSystem(&pCtxt->board);
    if (pCtxt->mode == MODE_TEST){
        pCtxt->mode = MODE_NORMAL;
        gtk_range_set_range(pCtxt->gene_debug, 1, POPULATION_SIZE);
        g_timeout_add (TICK_TIME*DT, tic, (gpointer) pCtxt ); // on re démmare le timer du tic.
    }
}

/// Cree un mode test (rest le popualtion et charge le premier robot)
void newTestMod(Contexte* pCtxt){

    gchar *path;
    newPopulation(&pCtxt->population, 1, &pCtxt->board);
    gtk_range_set_range(pCtxt->gene_debug, 1, 1);
    path = get_dialog_path_selection("FILE", ".", "some_file.txt", pCtxt->window);
    // nouvelle population
    if( path!=NULL ) {
        if (loadDan(path, &pCtxt->population.individualList[0].individual.dnaNeuralNetwork) == -1)
            messageBox("Error", "Error to read the dna file", pCtxt->window);
        else
            g_timeout_add (TICK_TIME*DT, ticTestMod, (gpointer) pCtxt ); // réenclenche le timer.
        g_free(path);
    }
}

/// Ajoute un robot au test
void addRobotTestMod(Contexte* pCtxt){

    gchar *path;
    addIndividual(&pCtxt->population, &pCtxt->board);
    int lastIndividual = pCtxt->population.populationSize - 1;
    gtk_range_set_range(pCtxt->gene_debug, 1, pCtxt->population.populationSize);
    path = get_dialog_path_selection("FILE", ".", "some_file.txt", pCtxt->window);
    if( path!=NULL ) {
        if (loadDan(path, &pCtxt->population.individualList[lastIndividual].individual.dnaNeuralNetwork) == -1)
            messageBox("Error", "Error to read the dna file", pCtxt->window);
        g_free(path);
    }
}

/// Mode test pour charger notre adn dans un robot
void testMod(GtkWidget *widget, gpointer data){

    // Récupère le contexte.
    Contexte* pCtxt = (Contexte*) data;
    if (pCtxt->mode == MODE_NORMAL){
        pCtxt->mode = MODE_TEST;
        newTestMod(pCtxt);
    }else if (pCtxt->mode == MODE_TEST)
        addRobotTestMod(pCtxt);
}

/// Sauvgarde l'adn du robot selectioner
void saveMod(GtkWidget *widget, gpointer data){

    // Récupère le contexte.
    Contexte* pCtxt = (Contexte*) data;

    if (pCtxt->mode == MODE_SAVE){
        pCtxt->mode = MODE_NORMAL;
        gtk_button_set_label(GTK_BUTTON(pCtxt->button_save), "Save a robot");
        char buff[128];
        sprintf(buff, "%d.txt", pCtxt->select_individu + 1);
        if(saveDna(buff, pCtxt->population.individualList[pCtxt->select_individu].individual.dnaNeuralNetwork))
            messageBox("Save", "The robot dna was save", pCtxt->window);
        else
            messageBox("Error", "Error to save the robot dna", pCtxt->window);
        // on remais la simulation
        g_timeout_add (TICK_TIME*DT, tic, (gpointer) pCtxt ); // on re démmare le timer du tic.
    }else if (pCtxt->mode == MODE_NORMAL){
        pCtxt->mode = MODE_SAVE;
        gtk_button_set_label(GTK_BUTTON(pCtxt->button_save), "Save select robot");
    }
}

/// Deplasse la cible aléatoirement Si on est en mode Test cela reset tout les robot
void new_TargetPosition(GtkWidget *widget, gpointer data){

    // Récupère le contexte.
    Contexte* pCtxt = (Contexte*) data;
    newTargetPosition(&pCtxt->board);
    // Si on est en mode test on reset les robots
    if (pCtxt->mode == MODE_TEST)
        for (int i = 0; i < pCtxt->population.populationSize; ++i)
            resetRobot(&pCtxt->population.individualList[i]);
}

/// Cree tout l'interface
void creerIHM(Contexte* pCtxt){

    GtkWidget* debug;
    GtkWidget* vbox1;
    GtkWidget* vbox2;
    GtkWidget* vbox3;
    GtkWidget* vbox4;
    GtkWidget* hbox1;
    GtkWidget* button_quit;
    GtkWidget* button_newTargetPosition;

    /* Crée une fenêtre. */
    pCtxt->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    debug = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Crée un conteneur horitzontal box.
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    // Crée deux conteneurs vertical box.
    vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    //  + 1 ar il y a label d'entête
    vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, NB_NEURAL + NUMBER_SENSOR_ROBOT + NB_LABEL_INFO + 1);
    // +2 car il y a la vitesse du robot et un label d'entête
    vbox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE + 1);
    vbox4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE + 1);
    // Crée une zone de dessin
    pCtxt->drawing_area = gtk_drawing_area_new();
    pCtxt->width  = WIDTH;
    pCtxt->height = HEIGHT;
    gtk_widget_set_size_request (pCtxt->drawing_area, pCtxt->width, pCtxt->height);
    // Crée le pixbuf source et le pixbuf destination
    gtk_container_add(GTK_CONTAINER(hbox1), pCtxt->drawing_area);
    // ... votre zone de dessin s'appelle ici "drawing_area"
    g_signal_connect(G_OBJECT(pCtxt->drawing_area ), "realize",
                     G_CALLBACK(realize_evt_reaction), pCtxt);

    g_signal_connect( G_OBJECT( pCtxt->drawing_area ), "draw",
                      G_CALLBACK( draw_callback  ), pCtxt );

    // ajoute des label dans la box 2, 3, 4

    gtk_container_add( GTK_CONTAINER( vbox2 ), gtk_label_new("Input value"));
    gtk_container_add( GTK_CONTAINER( vbox3 ), gtk_label_new("Neural 1"));
    gtk_container_add( GTK_CONTAINER( vbox4 ), gtk_label_new("Neural 2"));
    for (int i = 0; i < NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE; ++i) {
        pCtxt->network_input[i] = gtk_label_new("Input: 0.0000");
        gtk_container_add( GTK_CONTAINER( vbox2 ), pCtxt->network_input[i] );
        pCtxt->neural_1_weigth[i] = gtk_label_new("Weight: 0.0000");
        gtk_container_add( GTK_CONTAINER( vbox3 ), pCtxt->neural_1_weigth[i]);
        pCtxt->neural_2_weigth[i] = gtk_label_new("Weight: 0.0000");
        gtk_container_add( GTK_CONTAINER( vbox4 ), pCtxt->neural_2_weigth[i]);
    }

    for (int i = 0; i < NB_NEURAL; ++i) {
        pCtxt->neural_out[i] = gtk_label_new("Neural out: 0.0000");
        gtk_container_add( GTK_CONTAINER( vbox2 ), pCtxt->neural_out[i] );
    }

    for(int i = 0; i < NB_LABEL_INFO; i++){

        pCtxt->label_info[i] = gtk_label_new("INFO");
        gtk_container_add( GTK_CONTAINER( vbox2 ), pCtxt->label_info[i] );
    }

    // Rajoute le 2eme vbox dans le conteneur hbox (pour mettre les boutons sélecteur de points
    gtk_container_add( GTK_CONTAINER( hbox1 ), vbox2 );
    gtk_container_add( GTK_CONTAINER( hbox1 ), vbox3 );
    gtk_container_add( GTK_CONTAINER( hbox1 ), vbox4 );

    // Crée le bouton quitter.
    button_quit = gtk_button_new_with_label( "Exit" );
    pCtxt->button_normal = gtk_button_new_with_label("Normal mode");
    pCtxt->button_test = gtk_button_new_with_label("Test mode");
    pCtxt->button_save = gtk_button_new_with_label("Save a robot");
    button_newTargetPosition = gtk_button_new_with_label("New Target position");
    // Connecte la réaction gtk_main_quit à l'événement "clic" sur ce bouton.
    g_signal_connect( button_quit, "clicked",
                      G_CALLBACK( gtk_main_quit ),
                      NULL);
    g_signal_connect( pCtxt->button_normal, "clicked",
                      G_CALLBACK( normalMod ),
                      pCtxt);
    g_signal_connect( pCtxt->button_test, "clicked",
                      G_CALLBACK( testMod ),
                      pCtxt);
    g_signal_connect( pCtxt->button_save, "clicked",
                      G_CALLBACK( saveMod ),
                      pCtxt);
    g_signal_connect( button_newTargetPosition, "clicked",
                      G_CALLBACK( new_TargetPosition ),
                      pCtxt);
    // Rajoute tout dans le conteneur vbox.
    gtk_container_add( GTK_CONTAINER( vbox1 ), hbox1 );

    // ajoue de la bare pour choisir sont debug
    GtkWidget* gene_debug = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, POPULATION_SIZE, 1);
    g_signal_connect(gene_debug, "value-changed",
                     G_CALLBACK(selectIndividu),
                     pCtxt);
    pCtxt->gene_debug = (GtkRange*)gene_debug;
    gtk_container_add( GTK_CONTAINER( vbox1 ), gene_debug );

    gtk_container_add( GTK_CONTAINER( vbox1 ), pCtxt->button_normal );
    gtk_container_add( GTK_CONTAINER( vbox1 ), pCtxt->button_test );
    gtk_container_add( GTK_CONTAINER( vbox1 ), pCtxt->button_save );
    gtk_container_add( GTK_CONTAINER( vbox1 ), button_newTargetPosition );
    gtk_container_add( GTK_CONTAINER( vbox1 ), button_quit );
    // Rajoute la vbox  dans le conteneur window.
    gtk_container_add( GTK_CONTAINER( pCtxt->window ), vbox1 );


    // ZONE CLIC POUR AJOUTER DES OBSTACLES DANS LA ZONE DE DESSIN


    g_signal_connect( G_OBJECT( pCtxt->drawing_area ), "button_press_event",
                      G_CALLBACK( mouse_clic_reaction ), pCtxt );

    gtk_widget_set_events ( pCtxt->drawing_area, GDK_EXPOSURE_MASK
                                                 | GDK_LEAVE_NOTIFY_MASK
                                                 | GDK_BUTTON_PRESS_MASK
                                                 | GDK_POINTER_MOTION_MASK
                                                 | GDK_POINTER_MOTION_HINT_MASK);

    // Rend tout visible
    gtk_widget_show_all( pCtxt->window );
    g_signal_connect (pCtxt->window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    // enclenche le timer pour se déclencher dans 5ms.
    g_timeout_add ( TICK_TIME*DT, tic, (gpointer) pCtxt );
    // enclenche le timer pour se déclencher dans 20ms.
    g_timeout_add ( TICK_TIME*DT_AFF, ticAffichage, (gpointer) pCtxt );

}


//                      ____
//_____________________/MAIN\_____________________


int main(int argc, char** argv){

    iniRand();
    // init de plateau des obstacle
    Contexte contexte;
    newBoard(&contexte.board , WIDTH, HEIGHT);
    // Init du reseau de neurone et de la population
    Population population = initSystem(&contexte.board);

    contexte.population = population;
    // Label pour afficher la valeur des entrée du robot choisi
    contexte.network_input = (GtkWidget**)malloc(sizeof(GtkWidget) * NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE);
    // Valeur des entrée du neuron 1 et 2
    contexte.neural_1_weigth = (GtkWidget**)malloc(sizeof(GtkWidget) * NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE);
    contexte.neural_2_weigth = (GtkWidget**)malloc(sizeof(GtkWidget) * NUMBER_SENSOR_ROBOT + NUMBER_OTHER_DIVICE);
    // Label pour avoir la valeur de sortie du reseu de neurone
    contexte.neural_out = (GtkWidget**)malloc(sizeof(GtkWidget) * NB_NEURAL);
    contexte.label_info = (GtkWidget**)malloc(sizeof(GtkWidget) * NB_LABEL_INFO);
    // par defaut on choisi le premier individu de notre population
    contexte.select_individu = 0;
    contexte.mode = 0;
    // Creation des threads workers
    newWorkers(&contexte.workers, &contexte.population, &contexte.board);
    gtk_init(&argc, &argv);
    creerIHM(&contexte);
    gtk_main();

    return 1;

}
