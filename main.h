/*	Header file	*/
//#include <gtk/gtk.h>

//	Header file
//void openfile (int argc, char **argv);

void	newproject(int argc, char **argv);
void	chooseproject(int argc, char **argv);
int	ConfirmProject(int argc, char **argv);
void	deleteproject(int argc, char **argv);
int	WarningDelete(int argc, char **argv);

void 	rootpath(int argc, char **argv);
void	addmonitored(int argc, char **argv);
void	DeleteDirectory(int argc, char **argv);


/*	Functions, all odds and ends */
void	strswap(char *token, char vieux, char neuve);
void	populate();
int	Warning(int argc, char **argv);
void	validate();

void	reporter(int argc, char **argv);

void	About1(int argc, char **argv);


