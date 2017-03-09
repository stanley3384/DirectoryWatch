#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h" 

extern gchar WorkingPath[];		//to directory with all projects.
extern gchar WorkingProject[];
extern gchar RootPath[];
extern gchar MoniterDir[];
extern GtkEntry *Status;

void	populate()	{
char cmd[400];
char data[400];
char temp[400];
	strcpy(cmd, "ls -l  ");
	strcat(cmd, WorkingProject);
	strcat (cmd, " > temp0.txt 2>&1");	//std error to file proj.txt
	if(0 == system(cmd))	{
		system ("awk '{ print $9 }' temp0.txt > temp1.txt");
		std::cout << "cmd was okay have results for ls -l " << std::endl; 

		std::ifstream infile; 
		infile.open("temp1.txt");
		infile >> data;
	while(!infile.eof() )	{
//		std::cout << data << std::endl;
		if(data[0] == '_')
			{	strcpy(temp, data);
				strswap(temp, '_', '/');	//Mske it like unix file
				gtk_entry_set_text(Status, data);
				strcpy(cmd, "md5deep -tr ");
				strcat(cmd, temp);
				strcat(cmd, "  > ");	//cat a space char
				strcat(cmd, WorkingProject);
				strcat(cmd, "/");
				strcat(cmd, data);
				strcat(cmd, "/hash.log 2> ");
				strcat(cmd, WorkingProject);
				strcat(cmd, "/");
				strcat(cmd, data);
				strcat(cmd, "/hash.err");
//				std::cout  << "md5 populate cmd == " << cmd << std::endl;
				gtk_entry_set_text(Status, temp); //just show activity.
				std::cout << "Populating ---" << temp << std::endl;
				system(cmd);
			}

		infile >> data;
				}
	gtk_entry_set_text(Status, "MD5 operation terminated."); //just show activity.
	std::cout << "Populated all hashes for selected directories." << std::endl; 
	infile.close();		}
	else
		{ std::cout << "cmd bobo" << std::endl; }
	


	return;	}

void 	validate()	{
char cmd[400];
char data[400];
char temp[400];
	strcpy(cmd, "ls -l  ");
	strcat(cmd, WorkingProject);
	strcat (cmd, " > temp0.txt 2>&1");	//std error to file proj.txt
	std::cout << "cmd is = " << cmd << std::endl;
	if(0 == system(cmd))	{
		system ("awk '{ print $9 }' temp0.txt > temp1.txt");
		std::cout << "cmd was okay have results for ls -l " << std::endl; 

		std::ifstream infile; 
		infile.open("temp1.txt");
		infile >> data;
//		gtk_entry_set_text(Status, "This MD5 operation takes time."); //just show activity.
	while(!infile.eof() )	{
//		std::cout << "data is ==" << data << std::endl;
		if(data[0] == '_')
			{	strcpy(temp, data);
				strswap(temp, '_', '/');	//Mske it like unix file
				gtk_entry_set_text(Status, data);
				strcpy(cmd, " md5deep -rwX ");
//				strcat(cmd, WorkingPath);
				strcat(cmd, WorkingProject);
				strcat(cmd, "/");
				strcat(cmd, data);
				strcat(cmd, "/");
				strcat(cmd, "hash.log ");

//				strcat(cmd, RootPath);
				strcat(cmd, temp);
				strcat(cmd, "/*");
				strcat(cmd, "  > ");	//cat a space char
				strcat(cmd, WorkingProject);
				strcat(cmd, "/");
				strcat(cmd, data);
				strcat(cmd, "/delta.log 2> ");
				strcat(cmd, WorkingProject);
				strcat(cmd, "/");
				strcat(cmd, data);
				strcat(cmd, "/delta.err");
//				std::cout  << "md5 validate cmd == " << cmd << std::endl;
				system(cmd);
			}
		infile >> data;
				}
	gtk_entry_set_text(Status, "MD5 operation terminated."); //just show activity. 
	infile.close();		}
	else
		{ std::cout << "cmd bobo" << std::endl; }

	return;		}
