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
int DirHelp_delete_event()	{
	std::cout << "Quit DirHelp widget little x." << std::endl;
	gtk_main_quit ();
	return(FALSE);		} 

extern "C"
void on_DirHelpQuit_clicked()	{
	gtk_widget_destroy (help);
	gtk_main_quit();
	return;			}

void	dirhelp (int argc, char **argv)	//Try not too kill everything
{
	std::cout << "Start of directory help." << std::endl; 
       
        gtk_init (&argc, &argv);
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        help = GTK_WIDGET(gtk_builder_get_object (builder, "WinDirHelp"));

	quit  = GTK_BUTTON(gtk_builder_get_object (builder, "DirHelpQuit"));

        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (help);
	gtk_main ();
	std::cout << "Exiting Directory help." << std::endl;
        return;
}
