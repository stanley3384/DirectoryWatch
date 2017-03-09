CC=gcc
CXX = g++
CFLAGS=-I. -g `pkg-config --libs gtk+-3.0 gmodule-2.0 glib-2.0 --cflags`
# CFLAGS=-I. -g `pkg-config --libs gtk+-3.0 gmodule-2.0 glib-2.0 --cflags` -lbluetooth -g

SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include 

CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)

DEPS = MainScreen.glade main.h

OBJ = main.o NewProject.o Xref.o ChooseProject.o ConfirmProject.o RootPath.o DeleteProject.o DeleteProject.o WarningDelProj.o AddMonitored.o populate.o PopWarning.o functions.o DeleteDirectory.o Reporter.o About1.o 

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lGLEW -lGL

DirectoryWatch: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LINKER_FLAGS)


main.o : main.cpp $(DEPS)
	$(CXX) -c main.cpp $(CFLAGS)

NewProject.o : NewProject.cpp $(DEPS)
	$(CXX) -c NewProject.cpp $(CFLAGS)

Xref.o : Xref.cpp $(DEPS)
	$(CXX) -c Xref.cpp $(CFLAGS)

ChooseProject.o : ChooseProject.cpp $(DEPS)
	$(CXX) -c ChooseProject.cpp $(CFLAGS)

ConfirmProject.o : ConfirmProject.cpp $(DEPS)
	$(CXX) -c ConfirmProject.cpp $(CFLAGS)

RootPath.o : RootPath.cpp $(DEPS)
	$(CXX) -c RootPath.cpp $(CFLAGS)

DeleteProject.o : DeleteProject.cpp $(DEPS)
	$(CXX) -c DeleteProject.cpp $(CFLAGS)

DeleteDirectory.o : DeleteDirectory.cpp $(DEPS)
	$(CXX) -c DeleteDirectory.cpp $(CFLAGS)

WarningDelProj.o : WarningDelProj.cpp $(DEPS)
	$(CXX) -c WarningDelProj.cpp $(CFLAGS)

AddMonitored.o : AddMonitored.cpp $(DEPS)
	$(CXX) -c AddMonitored.cpp $(CFLAGS)

populate.o : populate.cpp $(DEPS)
	$(CXX) -c populate.cpp $(CFLAGS)

PopWarning.o : PopWarning.cpp $(DEPS)
	$(CXX) -c PopWarning.cpp $(CFLAGS)

functions.o : functions.cpp $(DEPS)
	$(CXX) -c functions.cpp $(CFLAGS)

Reporter.o : Reporter.cpp $(DEPS)
	$(CXX) -c Reporter.cpp $(CFLAGS)

About1.o : About1.cpp $(DEPS)
	$(CXX) -c About1.cpp $(CFLAGS)

.PHONY: zipper
zipper:
	-rm dirwatch.tar
	-rm dirwatch.tar.gz
	tar -cf dirwatch.tar *.cpp main.h MainScreen.glade Makefile start.sh watch.jpg backend.pl Utility*
	gzip -c dirwatch.tar > dirwatch.tar.gz

.PHONY: install
install:
	-rm *.o
	if ! test -d ~/DirecdtoryWatch; then \
	mkdir ~/DirectoryWatch; fi;
	cp DirectoryWatch ~/DirectoryWatch/DirectoryWatch
	cp start.sh ~/DirectoryWatch/start.sh
	cp watch.jpg ~/DirectoryWatch/watch.jpg
	cp MainScreen.glade ~/DirectoryWatch/MainScreen.glade
	cp backend.pl ~/DirectoryWatch/backend.pl
	if ! test -d  ~/ProjDirWatch; then \
	mkdir ~/ProjDirWatch; fi;
#Now for the fun stuff, setting up the menu but only for the local user not all users.
#If the following directories do not exist make them.
	if ! test -d ~/.local/share/desktop-directories; then \
	mkdir ~/.local/share/desktop-directories; fi;
#
	if ! test -d ~/.config/menus/applications-merged; then \
	mkdir ~/.config/menus/applications-merged; fi;
#
	-cp Utility-DirectoryWatch.desktop         ~/.local/share/applications/Utility-DirectoryWatch.desktop
	-cp Utility-DirectoryWatch-admin.desktop   ~/.local/share/applications/Utility-DirectoryWatch-admin.desktop
	-cp Utility-DirectoryWatch.directory       ~/.local/share/desktop-directories/Utility-DirectoryWatch.directory
	-cp Utility-DirectoryWatch.menu            ~/.config/menus/applications-merged/Utility-DirectoryWatch.men


.PHONY: uninstall
uninstall:
	-rm -r ~/DirectoryWatch
	-rm -r ~/ProjDirWatch
	-rm ~/.local/share/applications/Utility-DirectoryWatch.desktop
	-rm ~/.local/share/applications/Utility-DirectoryWatch-admin.desktop
	-rm ~/.local/share/desktop-directories/Utility-DirectoryWatch.directory
	-rm ~/.config/menus/applications-merged/Utility-DirectoryWatch.menu

