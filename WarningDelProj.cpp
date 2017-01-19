#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"


static	GtkBuilder	*builder;
static	GtkWidget	*warning;
static	GtkEntry	*DelDirName;
static	GtkButton	*yes, *no;

static	int		retval;
extern	gchar	deldircmd[];

extern "C"
void on_WDP_yes_pressed()	{
	retval = 1;
	gtk_widget_destroy (warning);
	gtk_main_quit();
	return;			}

extern "C"
void on_WDP_no_pressed()	{
	retval = 0;
	gtk_widget_destroy (warning);
	gtk_main_quit();
	return;			}


int	WarningDelete  (int argc, char **argv)	//Try not too kill everything
{
	std::cout << "Warning Delete window start of." << std::endl; 
       
        gtk_init (&argc, &argv);
	std::cout << "I'm starting WarningDelete." << std::endl;
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        warning = GTK_WIDGET(gtk_builder_get_object (builder, "DeleteWarning"));
	DelDirName = GTK_ENTRY(gtk_builder_get_object (builder, "DelCmd"));
	yes  = GTK_BUTTON(gtk_builder_get_object (builder, "WDP_yes"));
	no  = GTK_BUTTON(gtk_builder_get_object (builder, "WDP_no"));



        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (warning);
	gtk_entry_set_text(DelDirName, deldircmd);


	gtk_main ();

	std::cout << "Exiting Delete Project warning." << std::endl;
        return(retval);
}
