#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

extern gchar WorkingProject[];
extern gchar WorkingPath[];

extern 	GtkWidget *add_dir, *del_dir, *show_dir, *ck_pop, *ck_val, *ck_rep_gen, *ck_rep;


static	GtkBuilder	*builder;
static	GtkWidget	*ChooseProjectDialog;
static	GtkFileChooser	*filechooser;
static	GtkEntry	*ProjectName;
static	GtkButton	*Select, *Cancel;

/*==================================================================*/
extern "C"
int on_ChooseProjectDialog_delete_event()	{
	std::cout << "ChooseprojectDialog delete." << std::endl;
	gtk_main_quit();
	return(FALSE);			}

extern "C"
void on_ChooseProjectDialog_selection_changed(GtkFileChooser *fs)  {
	std::cout << "Choose selection changed." << std::endl;
	gchar* cName_pt = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fs));
	if (cName_pt != NULL) //Check for good pointer
		{
			strcpy(WorkingProject, cName_pt);  //Okay now.
			std::cout << "Choose2b selected = " << WorkingProject << std::endl;
			gtk_entry_set_text(ProjectName, cName_pt);
		}
	return;  } 
extern "C"
void on_ChooseProjectOkay_pressed()	{
int sp1;
	if(1 == ConfirmProject(0, NULL))	//Confirm selection.
//sp1 = ConfirmProject(0, NULL);
//std::cout << "sp1 is = " << sp1 << std::endl;
//	if(1 == sp1)
		{
		gtk_widget_set_sensitive(add_dir, TRUE);
		gtk_widget_set_sensitive(del_dir, TRUE);
		gtk_widget_set_sensitive(show_dir, TRUE);
		gtk_widget_set_sensitive(ck_pop, TRUE);
		gtk_widget_set_sensitive(ck_val, TRUE);
		gtk_widget_set_sensitive(ck_rep_gen, TRUE);
		gtk_widget_set_sensitive(ck_rep, TRUE);

		gtk_widget_destroy (ChooseProjectDialog);
		gtk_main_quit();
		}
	return;				}
extern "C"
void on_ChooseProjectCancel_pressed (void) 	{ 
	std::cout << "Choose Cancel button pressed" << std::endl;
	strcpy(WorkingProject, "\0");	//Clear project
	gtk_widget_destroy (ChooseProjectDialog);
	gtk_main_quit ();
	return;					}


void chooseproject (int argc, char **argv)
{
	std::cout << "ChooseProject window start of." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        ChooseProjectDialog = GTK_WIDGET(gtk_builder_get_object (builder, "ChooseProjectDialog"));
	filechooser = GTK_FILE_CHOOSER(gtk_builder_get_object (builder, "ChooseProjectDialog"));
	ProjectName = GTK_ENTRY(gtk_builder_get_object (builder, "ProjectName"));
	Select  = GTK_BUTTON(gtk_builder_get_object (builder, "Select"));

        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (ChooseProjectDialog);
	gtk_file_chooser_set_current_folder(filechooser, WorkingPath);

	gtk_main ();

	std::cout << "Exiting ChooseProject." << std::endl;
        return ;
}
