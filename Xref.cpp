 #include <gtk/gtk.h>

#include "main.h"
/*
The principal directories to watch are /bin, /var, /etc and /usr/local, ie not all of /usr.
*/

gchar WorkingPath[500] = {"/home/stan/Project.md5/" };	//Where the guts are.
gchar WorkingProject[500];	//The system we are testing
gchar RootPath[500];		//Path to the root directory / or /media/yourOS/
gchar MoniterDir[500];		//Path to a directory to be MD5 valitated
gchar	deldircmd[100];	//This is global used in other modules.'
