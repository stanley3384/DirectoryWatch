/*	Path to directories to be checked.	*/
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

extern gchar RootPath[];
extern gchar WorkingPath[];
extern gchar WorkingProject[]; 
extern gchar MoniterDir[];

static	GtkBuilder	*builder;
static	GtkWidget	*RootPathDialog;
static	GtkFileChooser	*pathchooser;
static	GtkEntry	*PathName;
static	GtkButton	*Select, Cancel;

/*==================================================================*/
extern "C"
void on_RootPathDialog_delete_event()	{
	std::cout << "RootPthDialog delete." << std::endl;
	gtk_main_quit();
	return;			}
extern "C"
void on_RootCancel_clicked (void) 	{ 
	strcpy(RootPath, "\0");	//Clear any provious stuff.
	gtk_widget_destroy (RootPathDialog);
	gtk_main_quit ();
	return;				}
extern "C"
void on_RootOkay_clicked()	{
	gtk_widget_destroy (RootPathDialog);
	gtk_main_quit ();
	return;			}
extern "C"
void on_RootPathDialog_current_folder_changed(GtkFileChooser *fs)  {
	std::cout << "Root Current folder changed." << std::endl;
	gchar* ptr = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fs));
	if (ptr != NULL) //Check for good pointer
		{
			strcpy(RootPath, ptr);  //Okay now.
			std::cout << "The Root3b file selected = " << RootPath << std::endl;
			gtk_entry_set_text(PathName, ptr);
		}
	return;  } 
extern "C"
void on_RootPathDialog_current_selection_changed(GtkFileChooser *fs)  {
	std::cout << "Root Current selection changed." << std::endl;
	gchar* ptr = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(fs));
	if (ptr != NULL) //Check for good pointer
		{
			strcpy(RootPath, ptr);  //Okay now.
			std::cout << "The Root3b file selected = " << RootPath << std::endl;
			gtk_entry_set_text(PathName, ptr);
		}
	return;  }

/*	=======================================================================*/


void rootpath (int argc, char **argv)
{
	std::cout << "RootPath window start of." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        RootPathDialog = GTK_WIDGET(gtk_builder_get_object (builder, "RootPathDialog"));
	pathchooser = GTK_FILE_CHOOSER(gtk_builder_get_object (builder, "RootPathDialog"));
	PathName = GTK_ENTRY(gtk_builder_get_object (builder, "PathName"));
	Select  = GTK_BUTTON(gtk_builder_get_object (builder, "Select"));


        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (RootPathDialog);
	gtk_file_chooser_set_current_folder(pathchooser, "/");

	gtk_main ();

	std::cout << "Exiting RootPath." << std::endl;
        return ;
}
