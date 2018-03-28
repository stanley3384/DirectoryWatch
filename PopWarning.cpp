#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"


static	GtkBuilder	*builder;
static	GtkWidget	*warning;
static	GtkButton	*yes, *no;
static  int	retval;

extern "C"
void on_PopWarningYes_clicked()	{
	retval = 1;
	gtk_widget_destroy (warning);
	gtk_main_quit();
	return;			}

extern "C"
void on_PopWarningNo_clicked()	{
	retval = 0;
	gtk_widget_destroy (warning);
	gtk_main_quit();
	return;			}



int Warning(int argc, char **argv)
{
	std::cout << "Warning start of." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        warning = GTK_WIDGET(gtk_builder_get_object (builder, "PopulateWarning"));
	yes  = GTK_BUTTON(gtk_builder_get_object (builder, "PopWarningYes"));
	no  = GTK_BUTTON(gtk_builder_get_object (builder, "PopWarningNo"));


        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        gtk_widget_show (warning);
	gtk_main ();

	std::cout << "Exiting Warning." << std::endl;
        return(retval) ;

}
