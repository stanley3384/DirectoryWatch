#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"


static	GtkBuilder	*builder;
static	GtkWidget	*help;
static	GtkButton	*quit;

extern "C"
int ProjHelp_delete_event()	{
	std::cout << "Quit ProjHelp widget little x." << std::endl;
	gtk_main_quit ();
	return(FALSE);		} 

extern "C"
void on_ProjHelpQuit_pressed()	{
	gtk_widget_destroy (help);
	gtk_main_quit();
	return;			}

void	projhelp (int argc, char **argv)	//Try not too kill everything
{
	std::cout << "Start of project help." << std::endl; 
       
        gtk_init (&argc, &argv);
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        help = GTK_WIDGET(gtk_builder_get_object (builder, "WinProjHelp"));

	quit  = GTK_BUTTON(gtk_builder_get_object (builder, "ProjHelpQuit"));

        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (help);
	gtk_main ();
	std::cout << "Exiting Project help." << std::endl;
        return;
}
