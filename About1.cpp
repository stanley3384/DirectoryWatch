#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

static	GtkBuilder	*builder;
static	GtkWidget	*About_Win;
static	GtkAboutDialog	*About2;
//static	GtkButton	*Okay, *Cancel;

extern "C"
int on_About_delete_event()	{
	gtk_main_quit ();
	return(FALSE);		} 

extern "C"
void on_About_response() {	//This is the Close Button signal? 
	gtk_widget_destroy (About_Win);
	gtk_main_quit ();
	return;
}

void	About1(int argc, char **argv)
{
std::cout << "About_Win start of." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        About_Win = GTK_WIDGET(gtk_builder_get_object (builder, "About"));

	About2 = GTK_ABOUT_DIALOG(gtk_builder_get_object (builder, "About"));

        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (About_Win);
	gtk_main ();

	std::cout << "Exiting About1." << std::endl;
        return ;
}
