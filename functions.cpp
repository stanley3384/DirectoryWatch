/*	Functions, odda and sods	*/

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "main.h"

void	strswap(char *token, char vieux, char neuve)
{
int i = 0;
	while(token[i] != '\0')
		{
			if(token[i] == vieux)
				{ token[i] = neuve; }
				i++;
		}
	return;
}
//	---------------------------------------------------------------

void fillbuff(GtkTextBuffer *token1, const char *token2) {
GtkTextIter	myiter;
extern gchar WorkingProject[];
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
		infile.getline (data, 400);
		strcat(data, "\n");
//		gtk_text_buffer_get_iter_at_line_offset(token1, &myiter, line, offset);
		gtk_text_buffer_insert(token1, &myiter, data, -1);
//std::cout << "line = " << line << " data = " << data << " cmd =" << cmd << std::endl;
		line ++;
	}
		infile.close();
std::cout << "Quiting fillbuff." << std::endl;
}
