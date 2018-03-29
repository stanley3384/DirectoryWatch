/*	Header file	*/
#include <gtk/gtk.h>

//	Header file
//void openfile (int argc, char **argv);

void	newproject(int argc, char **argv);
int cores(int argc, char **argv);
void	chooseproject(int argc, char **argv);
int	ConfirmProject(int argc, char **argv);
void	deleteproject(int argc, char **argv);
int	WarningDelete(int argc, char **argv);
void	projhelp(int argc, char **argv);


void 	rootpath(int argc, char **argv);
void	addmonitored(int argc, char **argv);
void	DeleteDirectory(int argc, char **argv);
void	dirhelp(int argc, char **argv);

/*	Functions, all odds and ends */
void	strswap(char *token, char vieux, char neuve);
void	populate();
int	Warning(int argc, char **argv);
void	validate();
void	checkhelp(int argc, char **argv);

void	reporter(int argc, char **argv);
void	get_dirs_watched();
void	directoryls(int argc, char **argv);
void	show(int argc, char **argv);
void	fillbuff(GtkTextBuffer *token1, const char *token2);
void	About1(int argc, char **argv);


