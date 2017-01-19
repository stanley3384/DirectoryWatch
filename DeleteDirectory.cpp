#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

extern gchar WorkingProject[];
extern gchar WorkingPath[];
extern gchar MoniterDir[];


static	GtkBuilder	*builder;
static	GtkWidget	*DeleteDirDialog;
static	GtkFileChooser	*filechooser;
static	GtkEntry	*DelDirName;
static	GtkButton	*Select, Cancel;

//gchar	*cName_pt;
/*==================================================================*/
extern "C"
int on_DeleteDirDialog_delete_event()	{
	std::cout << "DeleteDirectoryDialog delete." << std::endl;
	gtk_main_quit();
	return(FALSE);			}
extern "C"
void on_DirDeleteCancel_pressed (void) 	{ 
	std::cout << "Delete Cancel button pressed" << std::endl;
	strcpy(MoniterDir, "\0");	//Do not delete, it's null
	gtk_widget_destroy (DeleteDirDialog);
	gtk_main_quit ();
	return;				} 
extern "C"
void on_DirDelete_pressed()	{
	gtk_widget_destroy (DeleteDirDialog);
	gtk_main_quit();
	return;			}			
extern "C"
void on_DeleteDirectoryDialog_current_folder_changed(GtkFileChooser *fs)  {
	std::cout << "Delete folder selection changed." << std::endl;
	gchar* cName_pt = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fs));
	std::cout << "\n DelDir cName_pt = " << cName_pt << std::endl;
	if (cName_pt != NULL) //Check for good pointer
		{
			strcpy(MoniterDir, cName_pt);  //Okay now.
			std::cout << "Choose2b selected = " << MoniterDir << std::endl;
			gtk_entry_set_text(DelDirName, cName_pt);
		}
	return;  } 

void DeleteDirectory (int argc, char **argv)
{
	std::cout << "Delete Directory window start of." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        DeleteDirDialog = GTK_WIDGET(gtk_builder_get_object (builder, "DeleteDirectoryDialog"));
	filechooser = GTK_FILE_CHOOSER(gtk_builder_get_object (builder, "DeleteDirectoryDialog"));
	DelDirName = GTK_ENTRY(gtk_builder_get_object (builder, "DelDirName"));
	Select  = GTK_BUTTON(gtk_builder_get_object (builder, "Select"));



        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (DeleteDirDialog);
	gtk_file_chooser_set_current_folder(filechooser, WorkingProject);

	gtk_main ();

	std::cout << "Exiting Delete Project." << std::endl;
        return ;
}
