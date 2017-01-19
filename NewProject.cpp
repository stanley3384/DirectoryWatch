/*	New Project.		*/

#include <gtk/gtk.h>
#include <iostream>
#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

#include "main.h"

extern gchar WorkingProject[];

static	GtkBuilder	*builder;
static	GtkWidget	*NewProjectDialog;
static	GtkLabel	*label1;
static	GtkEntry	*entry1;
static	GtkWidget	*button1, *button2, *button3;

extern "C"
int on_NewProjectDialog_delete_event(GObject *object, gpointer user_data)
{
	std::cout << "NewprojectDialog delete." << std::endl;
	gtk_main_quit();
	return(FALSE);
}

extern "C"
void on_button1_pressed() {
	std::cout << "button1 clicked." << std::endl;
	const gchar *cName_pt;
	cName_pt = gtk_entry_get_text (entry1);
	strcpy (WorkingProject, cName_pt);
	gtk_main_quit(); 
	std::cout <<"Exiting on open clicked." << std::endl;
	return ;  }
extern"C"
void on_button2_pressed()	{
	std::cout << "button2 pressed" << std::endl;
	gtk_main_quit();
	return;			}
extern"C"
void on_button3_pressed()	{
	std::cout << "help on the way." << std::endl;
	gtk_main_quit();
	return;			}

void newproject (int argc, char **argv)
{
	std::cout << "Newproject." << std::endl;        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        NewProjectDialog = GTK_WIDGET (gtk_builder_get_object (builder, "NewProjectDialog"));

	label1 = GTK_LABEL (gtk_builder_get_object (builder, "label1"));
        entry1 = GTK_ENTRY (gtk_builder_get_object (builder, "entry1"));
        button1 = GTK_WIDGET (gtk_builder_get_object (builder, "button1"));
        button2 = GTK_WIDGET (gtk_builder_get_object (builder, "button2"));
        button3 = GTK_WIDGET (gtk_builder_get_object (builder, "button3"));

        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
std::cout << "About to show NewProject." << std::endl;
        gtk_widget_show (NewProjectDialog);
std::cout << "Showing NewProject." << std::endl;
	gtk_main ();
	gtk_widget_destroy(NewProjectDialog); //destroys both windows same as little x in open
	std::cout << "Exiting NewProject." << std::endl;
        return ;
}
/*
void 
cancel_open () {
	std::cout << "Cancel button clicked." << std::endl;

gtk_entry_set_text(GTK_ENTRY(entry1), "NewProject cancel"); 

const char *txt_pt;
	txt_pt  = gtk_entry_get_text (entry1);
	std::cout << "txt_pt " << txt_pt << std::endl;

//        gtk_main_quit();
	return;  } */

