#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

static	GtkBuilder	*builder;
static	GtkWidget	*ProjectConfirm;
static	GtkFileChooser	*filechooser;
static	GtkEntry	*ProjectName;
static	GtkButton	*Okay, *Cancel;

extern gchar WorkingProject[];

static	gint	retval;

extern "C"
int on_ProjectConfirm_delete_event()	{
	std::cout << "ProjectConfirm delete." << std::endl;
	gtk_main_quit();
	return(FALSE);			}

extern "C"
void	on_ProjConOkay_pressed(void)	{
	std::cout << "Proj Okay pressed" << std::endl; 
	retval = 1;
	gtk_widget_destroy (ProjectConfirm);
	gtk_main_quit ();
	return;				}

extern "C"
void	on_ProjConCan_pressed(void)	{
	std::cout << "Proj can pressed." << std::endl;
	retval = 0;
	gtk_widget_destroy (ProjectConfirm);
	gtk_main_quit ();
	return;

					}

int	ConfirmProject(int argc, char **argv)
{
std::cout << "ConfirmProject window start of." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        ProjectConfirm = GTK_WIDGET(gtk_builder_get_object (builder, "ProjectConfirm"));
//	filechooser = GTK_FILE_CHOOSER(gtk_builder_get_object (builder, "ProjectConfirm"));
	ProjectName = GTK_ENTRY(gtk_builder_get_object (builder, "ProjConf"));
	Okay  = GTK_BUTTON(gtk_builder_get_object (builder, "ProjCanOkay"));
	Cancel  = GTK_BUTTON(gtk_builder_get_object (builder, "ProjCanCan"));


        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (ProjectConfirm);
	gtk_entry_set_text(ProjectName, WorkingProject);
	gtk_main ();

	std::cout << "Exiting ChooseProject." << std::endl;
        return(retval) ;
}
