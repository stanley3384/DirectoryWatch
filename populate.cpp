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
extern GtkEntry *Status;

extern gchar	file2show[200];	//This should be set to the directories or errors to be shown in widget

void	populate()	{
char cmd[400];
char data[400];
char dir2do[400];
char temp[400];

//	Add a heading to Hasherr.log
	strcpy(cmd, "echo ");
	strcat(cmd, "Start of Hasherr.log file > ");
	strcat(cmd, WorkingProject);
	strcat(cmd, "/Hasherr.log");	
	system (cmd);

//	Get the directories that are to being watched.
	strcpy(cmd, "ls -l  ");
	strcat(cmd, WorkingProject);
	strcat (cmd, " > temp0.txt 2>&1");	//std error to file proj.txt
	if(0 == system(cmd))
	{	//	Using awk to remove the clutter from start of "ls -l."
		if(0 != system ("awk '{ print $9 }' temp0.txt > temp1.txt"))
			{
				gtk_entry_set_text(Status, "Failure finding directories.");
				std::cout << "cmd was okay have results for ls -l " << std::endl;
				return;
			} 

		std::ifstream infile; 
		infile.open("temp1.txt");
		infile >> data;		//data is an uncluttered line from "ls -l"
	while(!infile.eof() )	{
//		std::cout << data << std::endl;
//	Skip over non directories, I have watched directories starting with underscore.
		if(data[0] == '_')
			{
				strcpy(dir2do, WorkingProject);
				strcat(dir2do, "/");
				strcat(dir2do, data);

				strcpy(temp, data);
				strswap(temp, '_', '/');	//Mske it like unix file
//				gtk_entry_set_text(Status, data);
				strcpy(cmd, "md5deep -tr ");
				strcat(cmd, temp);
				strcat(cmd, "  > ");	//cat a space char
				strcat(cmd, dir2do);
				strcat(cmd, "/hash.log 2> ");

				strcat(cmd, dir2do);
				strcat(cmd, "/hash.err");
				std::cout  << "md5 populate cmd == " << cmd << std::endl;
				std::cout << "Populating ---" << temp << std::endl;
				if(0 != system(cmd))
				{
					gtk_entry_set_text(Status, "md5deep failing a directory.");
					return;	
				}
//	Add a sub heading to Hasherr.log
		strcpy(temp, "echo Next_Directory. >> ");
		strcat(temp, WorkingProject);
		strcat(temp, "/Hasherr.log");
		system(temp);
//	catinating all the hash.err files into Hasherr.log for display in another module.
		strcpy(cmd, "cat ");
		strcat(cmd, dir2do);
		strcat(cmd, "/hash.err >> ");

		strcat(cmd, WorkingProject);
		strcat(cmd, "/Hasherr.log");
		system(cmd);
std::cout << "catting = " << cmd << "\n\n" << std::endl;
			}
		infile >> data;
				}
	gtk_entry_set_text(Status, "MD5 operation terminated."); //just show activity.
	std::cout << "Populated all hashes for selected directories." << std::endl; 
	infile.close();
	}
	else
		{ std::cout << "cmd bobo" << std::endl; }

		strcpy(file2show, WorkingProject);
		strcat(file2show, "/Hasherr.log");
		directoryls(0, NULL);

	return;	}

void 	validate()	{
char cmd[400];
char data[400];
char dir2do[400];
char temp[400];

//	Add a heading to Deltaerr.log
	strcpy(cmd, "echo ");
	strcat(cmd, "Start of Deltaerr.log file > ");
	strcat(cmd, WorkingProject);
	strcat(cmd, "/Deltaerr.log");	
	system (cmd);

//	Get the directories that are to being watched.
	strcpy(cmd, "ls -l  ");
	strcat(cmd, WorkingProject);
	strcat (cmd, " > temp0.txt 2>&1");	//std error to file proj.txt
	if(0 == system(cmd))
	{	//	Using awk to remove the clutter from start of "ls -l."
		if(0 != system ("awk '{ print $9 }' temp0.txt > temp1.txt"))
			{
				gtk_entry_set_text(Status, "Failure finding directories.");
				std::cout << "cmd was okay have results for ls -l " << std::endl;
				return;
			} 

		std::ifstream infile; 
		infile.open("temp1.txt");
		infile >> data;
//		gtk_entry_set_text(Status, "This MD5 operation takes time."); //just show activity.
	while(!infile.eof() )	{
//		std::cout << "data is ==" << data << std::endl;.
		if(data[0] == '_')
//	Skip over non directories, I have watched directories starting with underscore
			{
				strcpy(dir2do, WorkingProject);
				strcat(dir2do, "/");
				strcat(dir2do, data);

				strcpy(temp, data);
				strswap(temp, '_', '/');	//Mske it like unix file
//				gtk_entry_set_text(Status, data);
				strcpy(cmd, " md5deep -rwX ");
				strcat(cmd, dir2do);
				strcat(cmd, "/hash.log ");


				strcat(cmd, temp);
				strcat(cmd, "  > ");	//cat a space char
				strcat(cmd, dir2do);
				strcat(cmd, "/delta.log 2> ");

				strcat(cmd, dir2do);
				strcat(cmd, "/delta.err");
				std::cout  << "md5 delta cmd == " << cmd << std::endl;
				std::cout << "Deltaating ---" << temp << std::endl;
int xyz = system(cmd);
std::cout << "xyz = " << xyz << std::endl;
/*
				if((0 || 1 || 2) != system(cmd))	//Match 0 or 1 or 2 okay.
				{
					gtk_entry_set_text(Status, "md5deep failing a directory.");
					return;
				} */
//	Add a sub heading to Deltaerr.log
		strcpy(temp, "echo Next_Directory. >> ");
		strcat(temp, WorkingProject);
		strcat(temp, "/Deltaerr.log");
		system(temp);
//	catinating all the delta.err files into Deltaerr.log for display in another module.
		strcpy(cmd, "cat ");
		strcat(cmd, dir2do);
		strcat(cmd, "/delta.err >> ");

		strcat(cmd, WorkingProject);
		strcat(cmd, "/Deltaerr.log");
		system(cmd);
std::cout << "catting = " << cmd << "\n\n" << std::endl;
			}
		infile >> data;
					}
	gtk_entry_set_text(Status, "MD5 operation terminated."); //just show activity.
	std::cout << "Deltad all deltas for selected directories." << std::endl; 
	infile.close();
	}
	else
		{ std::cout << "cmd bobo" << std::endl; }

		strcpy(file2show, WorkingProject);
		strcat(file2show, "/Deltaerr.log");
		directoryls(0, NULL);

	return;		}
