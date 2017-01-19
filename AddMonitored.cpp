#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

extern gchar MoniterDir[];
extern gchar WorkingPath[];
extern gchar RootPath[];
extern gchar WorkingProject[];


static	GtkBuilder	*builder;
static	GtkWidget	*AddMonitored;
static	GtkFileChooser	*filechooser;
static	GtkEntry	*Monitored;
static	GtkButton	*SaveMonitored, CanMonitored;
//gchar	*cName_pt;
/*==================================================================*/
extern "C"
int on_AddMonitored_delete_event()	{
	std::cout << "AddMonitoredDialog delete." << std::endl;
	gtk_main_quit();
	return(FALSE);			}
extern "C"
void on_CanMonitored_pressed (void) 	{ 
	std::cout << "AddMonitored Cancel button pressed" << std::endl;
	strcpy(MoniterDir, "\0");	//Clear project
	gtk_widget_destroy (AddMonitored);
	gtk_main_quit ();
	return;				} 

extern "C"
void on_AddMonitored_current_folder_changed(GtkFileChooser *fs)  {
	std::cout << "AddMonitored selection changed." << std::endl;
	gchar* cName_pt = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fs));
	std::cout << "AddMonitored cName_pt = " << cName_pt << std::endl;
	if (cName_pt != NULL) //Check for good pointer
		{
			strcpy(MoniterDir, cName_pt);  //Okay now.
			std::cout << "AddMonitored2b selected = " << MoniterDir << std::endl;
			gtk_entry_set_text(Monitored, cName_pt);
		}

	return;  } 
extern "C"
void on_SaveMonitored_pressed()	{
	gtk_widget_destroy (AddMonitored);
	gtk_main_quit();
	return;				}


void addmonitored (int argc, char **argv)
{
	std::cout << "Monitor Directory." << WorkingProject << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        AddMonitored = GTK_WIDGET(gtk_builder_get_object (builder, "AddMonitored"));
	filechooser = GTK_FILE_CHOOSER(gtk_builder_get_object (builder, "AddMonitored"));
	Monitored = GTK_ENTRY(gtk_builder_get_object (builder, "Monitored"));
	SaveMonitored  = GTK_BUTTON(gtk_builder_get_object (builder, "SaveMonitored"));
//	CanMonitored  = GTK_BUTTON(gtk_builder_get_object (builder, "CanMonitored"));


        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (AddMonitored);
	gtk_file_chooser_set_current_folder(filechooser, RootPath);

	gtk_main ();

	std::cout << "Exiting AddMonitored." << std::endl;
        return ;
}
