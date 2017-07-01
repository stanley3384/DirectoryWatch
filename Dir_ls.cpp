
/*	This module is to display all the directories being watched.*/

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
extern GtkEntry *Status;

extern gchar	file2show[200];	//This should be set to the directories or errors to be shown in widget


static	GtkBuilder	*builder;
static	GtkWidget	*DirWin;
static	GtkTextView	*lsdir;
static	GtkTextBuffer	*buffdir;
static	GtkTextIter	myiter;
static	gint	line, offset;

void buffload(GtkTextBuffer *token1, const char *token2);
void	get_dir_watched(void);

extern "C"
int on_Dir_Win_delete_event()	{
	std::cout << "Directory delete.\n" << std::endl;
	gtk_main_quit();
	return(FALSE);			}
//	=============================================================

void	get_dirs_watched()
{
char sp1[400];
	strcpy(sp1, "ls -l ");
	strcat(sp1, WorkingProject);
	strcat(sp1, " > temp.txt");
	system (sp1);
std::cout << "sp1 holds " << sp1 << std::endl;

	if(0 != system ("awk '{ print $9 }' temp.txt > temp2.txt"))
		{
			gtk_entry_set_text(Status, "Failure finding directories.");
			std::cout << "cmd was okay have results for ls -l " << std::endl;
			return;
		}
		system("grep ^_ temp2.txt > temp.txt");
		strcpy(file2show, "temp.txt");
		directoryls(0, NULL);

}



void	directoryls(int argc, char **argv) 
{
//	char sp1[400];
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        DirWin = GTK_WIDGET(gtk_builder_get_object (builder, "Dir_Win"));

	lsdir = GTK_TEXT_VIEW(gtk_builder_get_object (builder, "ls_dir"));

	buffdir	= gtk_text_view_get_buffer (GTK_TEXT_VIEW (lsdir));

        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));

//	get_dir_watched();

/*	strcpy(sp1, "ls -l ");
	strcat(sp1, WorkingProject);
	strcat(sp1, " > temp.txt");
	system (sp1);
std::cout << "sp1 holds " << sp1 << std::endl;

	if(0 != system ("awk '{ print $9 }' temp.txt > temp2.txt"))
		{
			gtk_entry_set_text(Status, "Failure finding directories.");
			std::cout << "cmd was okay have results for ls -l " << std::endl;
			return;
		}
		system("grep ^_ temp2.txt > temp.txt"); */



	buffload(buffdir, file2show);

	gtk_widget_show (DirWin);
	gtk_main ();

	std::cout << "Exiting Reporter." << std::endl;
        return ;
}


void buffload(GtkTextBuffer *token1, const char *token2) {
GtkTextIter	myiter;
char	data[400];
gint	line, offset;
std::cout << "in buffload\n" << std::endl;
	std::ifstream infile; 
	infile.open(token2, std::ifstream::in);
//	infile.open("temp.txt", std::ifstream::in);
	line = 0;
	offset = 0;
	gtk_text_buffer_get_start_iter (token1, &myiter);
	while(!infile.eof() )	{

std::cout << data << std::endl;
		infile.getline (data, 400);
		strcat(data, "\n");
//		gtk_text_buffer_get_iter_at_line_offset(token1, &myiter, line, offset);
		gtk_text_buffer_insert(token1, &myiter, data, -1);
std::cout << "line = " << line << " offset = " << offset << " data = " << data << " token2 = " << token2 << std::endl;
		line ++;
		if(20 < line)
			{ return; }
	}
		infile.close();
}



