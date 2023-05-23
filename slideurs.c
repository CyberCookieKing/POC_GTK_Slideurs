/**************************************************************************************************/
/*                                                                                                */
/*                                   Application slideurs de texte                                */
/*                                     Auteur: CyberCookieKing                                    */
/*                                         Date: 23/05/2023                                       */
/*                                                                                                */
/* But:                                                                                           */
/*  Créer une pour une application de bureau en C avec GTK qui affiche une fenêtre avec une zone  */
/*  de texte éditable et des slideurs qui apparaissent lorsque le texte dépasse la taille de la   */
/*  zone de texte.                                                                                */
/*                                                                                                */
/* Instalation:                                                                                   */
/*  apt install libgtk-3-dev                                                                      */
/*                                                                                                */
/* Compilation:                                                                                   */
/*  gcc -o slideurs slideurs.c `pkg-config --cflags --libs gtk+-3.0`                              */
/*                                                                                                */
/* Utilisation:                                                                                   */
/*  - Lancez l'application                                                                        */
/*  - Une fenêtre s'ouvrira, affichant une zone de texte éditable.                                */
/*  - Si le texte dépasse la taille de la zone de texte, des slideurs apparaîtront.               */
/*                                                                                                */
/**************************************************************************************************/

#include <gtk/gtk.h>

/**************************************************************************************************/
/* Nom de la fonction: on_text_changed()                                                          */
/* But: Fonction de callback appelée lorsqu'un changement de texte se produit dans la zone de     */
/*      texte. Elle gère le dépassement de texte en affichant ou en masquant les slideurs.        */
/*                                                                                                */
/* Paramètre: buffer: Pointeur vers le GtkTextBuffer contenant le texte.                          */
/* Paramètre: text_view: Pointeur vers le widget GtkTextView.                                     */
/*                                                                                                */
/*                                     Auteur: CyberCookieKing                                    */
/*                                         Date: 23/05/2023                                       */
/**************************************************************************************************/
void on_text_changed(GtkTextBuffer *buffer, GtkWidget *text_view)
{
    // Obtient l'ajustement vertical du widget GtkTextView
    GtkAdjustment *vadj = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(text_view));
    
    // Récupère la hauteur totale du texte et la hauteur de la fenêtre
    double text_height = gtk_adjustment_get_upper(vadj);
    double window_height = gtk_adjustment_get_page_size(vadj);
    
    // Affiche ou masque les slideurs en fonction du dépassement de texte
    if (text_height > window_height)
        gtk_widget_show(GTK_WIDGET(vadj));
    else
        gtk_widget_hide(GTK_WIDGET(vadj));
}

/**************************************************************************************************/
/* Nom de la fonction: main()                                                                     */
/* But: Fonction principale du programme. Elle initialise GTK, crée la fenêtre principale avec    */
/*      une zone de texte éditable, configure les callbacks et affiche la fenêtre.                */
/*                                                                                                */
/* Paramètre: argc: Nombre d'arguments en ligne de commande.                                      */
/* Paramètre: argv: Tableau d'arguments en ligne de commande.                                     */
/*                                                                                                */
/*                                     Auteur: CyberCookieKing                                    */
/*                                         Date: 23/05/2023                                       */
/**************************************************************************************************/
int main(int argc, char *argv[])
{
    // Initialise GTK
    gtk_init(&argc, &argv);

    // Crée la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Application slideurs de texte");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crée une zone de texte éditable
    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    g_signal_connect(buffer, "changed", G_CALLBACK(on_text_changed), text_view);

    // Crée un conteneur pour la zone de texte
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), 
                                   GTK_POLICY_AUTOMATIC, 
                                   GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_container_add(GTK_CONTAINER(window), scroll);

    // Affiche les slideurs par défaut
    GtkAdjustment *vadj = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(text_view));
    gtk_adjustment_set_lower(vadj, 0);
    gtk_adjustment_set_upper(vadj, 0);
    gtk_widget_show(GTK_WIDGET(vadj));

    // Affiche la fenêtre principale
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
