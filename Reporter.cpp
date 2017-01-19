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
static	GtkWidget	*Reportwin;
static	GtkTextView	*changedview, *newview, *missingview;
static	GtkTextBuffer	*buffchanged, *buffnew, *buffmissing;
static	GtkTextIter	myiter;
gint	line, offset;

void fillbuff(GtkTextBuffer *token1, const char *token2);

extern "C"
int on_Report_win_delete_event()	{
	std::cout << "Report delete.\n" << std::endl;
	gtk_main_quit();
	return(FALSE);			}

void	reporter(int argc, char **argv) 
{

//std::cout << "In reporter1.\n"<< std::endl;
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "MainScreen.glade", NULL);
        Reportwin = GTK_WIDGET(gtk_builder_get_object (builder, "Report_win"));

	changedview = GTK_TEXT_VIEW(gtk_builder_get_object (builder, "ChangedView"));
	newview = GTK_TEXT_VIEW(gtk_builder_get_object (builder, "NewView"));
	missingview = GTK_TEXT_VIEW(gtk_builder_get_object (builder, "MissingView"));

	buffchanged	= gtk_text_view_get_buffer (GTK_TEXT_VIEW (changedview));
	buffnew		= gtk_text_view_get_buffer (GTK_TEXT_VIEW (newview));
	buffmissing	= gtk_text_view_get_buffer (GTK_TEXT_VIEW (missingview));

        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
/*
	strcpy(cmd, WorkingProject);
	strcat(cmd, "/changed.log");
	std::ifstream infile; 
	infile.open(cmd, std::ifstream::in);
	line = 0;
	offset = 0;
	gtk_text_buffer_get_start_iter (buffchanged, &myiter);
	while(!infile.eof() )	{
std::cout << data << std::endl;
		infile.getline (data, 400);
		strcat(data, "\n");
		gtk_text_buffer_get_iter_at_line_offset(buffchanged, &myiter, line, offset);

				} */
fillbuff(buffchanged, "/changed.log");
fillbuff(buffnew, "/new.log");
fillbuff(buffmissing, "/missing.log");

//	infile.close();	
	gtk_widget_show (Reportwin);
	gtk_main ();

	std::cout << "Exiting Reporter." << std::endl;
        return ;
}

void fillbuff(GtkTextBuffer *token1, const char *token2) {
GtkTextIter	myiter;
char	data[400];
char	cmd[400];
gint	line, offset;
std::cout << "in fillbuff\n" << std::endl;

	strcpy(cmd, WorkingProject);
	strcat(cmd, token2);
	std::ifstream infile; 
	infile.open(cmd, std::ifstream::in);
	line = 0;
	offset = 0;
	gtk_text_buffer_get_start_iter (token1, &myiter);
	while(!infile.eof() )	{

//std::cout << data << std::endl;
		infile.getline (data, 400);
		strcat(data, "\n");
//		gtk_text_buffer_get_iter_at_line_offset(token1, &myiter, line, offset);
		gtk_text_buffer_insert(token1, &myiter, data, -1);
//std::cout << "line = " << line << " data = " << data << " cmd =" << cmd << std::endl;
		line ++;
	}
		infile.close();
}



