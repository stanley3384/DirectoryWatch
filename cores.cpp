
/*	This module is to get the number of cores available to speed up md5deep using -jn flag.*/

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "main.h"


extern	gchar	No_of_cores[5];		//No of cores on system motherboard.
extern 	GtkEntry *CoresNo;

int cores(int argc, char **argv)
{
std::string line;
system("cat /proc/cpuinfo | grep processor | wc -l > cor.txt");
std::ifstream infile("cor.txt");
std::getline(infile, line);
const char *data = line.c_str();	//convert std::string to c_str.
strcpy(No_of_cores, data);
std::cout << "There are " << No_of_cores << " cores on this system" << std::endl;
	gtk_entry_set_text(CoresNo, No_of_cores);
return(1);
}
//	--------------------------------------------------------------
/*//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int cores(int argc, char **argv)
{
   FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
   char *arg = 0;
   size_t size = 0;
   while(getdelim(&arg, &size, 0, cpuinfo) != -1)
   {
      puts(arg);
   }
   free(arg);
   fclose(cpuinfo);
   return 0;
} */




/*
#include <stdio.h>#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
   char *arg = 0;
   size_t size = 0;
   while(getdelim(&arg, &size, 0, cpuinfo) != -1)
   {
      puts(arg);
   }
   free(arg);
   fclose(cpuinfo);
   return 0;
}
#include <libcpuid.h>

#include <libcpuid/libcpuid.h>

int main(void)
{
    struct cpu_raw_data_t raw;
    struct cpu_id_t data;

    cpuid_get_raw_data(&raw);
    cpu_identify(&raw, &data);
    printf("No. of Physical Core(s) : %d\n", data.num_cores);
    return 0;
} */




// use boost to get number of cores on the processor
// compile with : g++ -o cores cores.cpp -lboost_system -lboost_thread
/*
#include <iostream>
#include <boost/thread.hpp>

int main ()
{
    std::cout << "No. of Physical Core(s) : " << boost::thread::physical_concurrency() << std::endl;
    std::cout << "No. of Logical Core(s) : " << boost::thread::hardware_concurrency() << std::endl;
    return 0;
} */
