#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

extern gchar WorkingProject[];
extern gchar WorkingPath[];


static	GtkBuilder	*builder;
static	GtkWidget	*DeleteProjectDialog;
static	GtkFileChooser	*filechooser;
static	GtkEntry	*DelProjName;
static	GtkButton	*Select, Cancel;

//gchar	*cName_pt;
/*==================================================================*/
extern "C"
int on_DeleteProjectDialog_delete_event()	{
	std::cout << "DeleteprojectDialog delete." << std::endl;
	gtk_main_quit();
	return(FALSE);			}
extern "C"
void on_ProjectDeleteCancel_pressed (void) 	{ 
	std::cout << "Delete Cancel button pressed" << std::endl;
	strcpy(WorkingProject, "\0");	//Do not delete, it's null
	gtk_widget_destroy (DeleteProjectDialog);
	gtk_main_quit ();
	return;				} 
extern "C"
void on_ProjectDelete_pressed()	{
	gtk_widget_destroy (DeleteProjectDialog);
	gtk_main_quit();
	return;			}			
extern "C"
void on_DeleteProjectDialog_current_folder_changed(GtkFileChooser *fs)  {
	std::cout << "Delete folder selection changed." << std::endl;
	gchar* cName_pt = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fs));
	std::cout << "\n cName_pt = " << cName_pt << std::endl;
	if (cName_pt != NULL) //Check for good pointer
		{
			strcpy(WorkingProject, cName_pt);  //Okay now.
			std::cout << "Choose2b selected = " << WorkingProject << std::endl;
			gtk_entry_set_text(DelProjName, cName_pt);
		}
//	gtk_entry_set_text(DelProjName, cName_pt);
//	strcpy(WorkingProject, cName_pt);
	return;  } 

void deleteproject (int argc, char **argv)
{
	std::cout << "DeleteProject window start of." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        DeleteProjectDialog = GTK_WIDGET(gtk_builder_get_object (builder, "DeleteProjectDialog"));
	filechooser = GTK_FILE_CHOOSER(gtk_builder_get_object (builder, "DeleteProjectDialog"));
	DelProjName = GTK_ENTRY(gtk_builder_get_object (builder, "DelProjName"));
	Select  = GTK_BUTTON(gtk_builder_get_object (builder, "Select"));



        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (DeleteProjectDialog);
	gtk_file_chooser_set_current_folder(filechooser, WorkingPath);

	gtk_main ();

	std::cout << "Exiting Delete Project." << std::endl;
        return ;
}
