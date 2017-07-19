CC=gcc
CXX = g++
CFLAGS=-I. -g `pkg-config --libs gtk+-3.0 gmodule-2.0 glib-2.0 --cflags`
# CFLAGS=-I. -g `pkg-config --libs gtk+-3.0 gmodule-2.0 glib-2.0 --cflags` -lbluetooth -g

SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include 

CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)

DEPS = MainScreen.glade main.h

OBJ = main.o NewProject.o Xref.o ChooseProject.o ConfirmProject.o RootPath.o DeleteProject.o DeleteProject.o WarningDelProj.o AddMonitored.o populate.o PopWarning.o functions.o DeleteDirectory.o Reporter.o Dir_ls.o About1.o projhelp.o dirhelp.o checkhelp.o cores.o

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lGLEW -lGL

DirectoryWatch: $(OBJ)
	$(CXX) -o $@.elf $^ $(CFLAGS) $(LDFLAGS) $(LINKER_FLAGS)


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

projhelp.o : projhelp.cpp $(DEPS)
	$(CXX) -c projhelp.cpp $(CFLAGS)

DeleteDirectory.o : DeleteDirectory.cpp $(DEPS)
	$(CXX) -c DeleteDirectory.cpp $(CFLAGS)

WarningDelProj.o : WarningDelProj.cpp $(DEPS)
	$(CXX) -c WarningDelProj.cpp $(CFLAGS)

AddMonitored.o : AddMonitored.cpp $(DEPS)
	$(CXX) -c AddMonitored.cpp $(CFLAGS)

dirhelp.o : dirhelp.cpp $(DEPS)
	$(CXX) -c dirhelp.cpp $(CFLAGS)

populate.o : populate.cpp $(DEPS)
	$(CXX) -c populate.cpp $(CFLAGS)

checkhelp.o : checkhelp.cpp $(DEPS)
	$(CXX) -c checkhelp.cpp $(CFLAGS)

PopWarning.o : PopWarning.cpp $(DEPS)
	$(CXX) -c PopWarning.cpp $(CFLAGS)

functions.o : functions.cpp $(DEPS)
	$(CXX) -c functions.cpp $(CFLAGS)

Reporter.o : Reporter.cpp $(DEPS)
	$(CXX) -c Reporter.cpp $(CFLAGS)

Dir_ls.o : Dir_ls.cpp $(DEPS)
	$(CXX) -c Dir_ls.cpp $(CFLAGS)

About1.o : About1.cpp $(DEPS)
	$(CXX) -c About1.cpp $(CFLAGS)

cores.o : cores.cpp $(DEPS)
	$(CXX) -c cores.cpp $(CFLAGS)

.PHONY: zipper
zipper:
	-rm dirwatch.tar.gz
	tar -cf dirwatch.tar *.cpp main.h MainScreen.glade Makefile start.sh watch.jpg backend.pl *.desktop *.menu *.directory DirectoryWatch.odt
	gzip -c dirwatch.tar > dirwatch.tar.gz
	-rm dirwatch.tar

.PHONY: update
update:
	cd ~/DirectoryWatch
#	-rm *.o
	cp DirectoryWatch.elf ~/DirectoryWatch/DirectoryWatch.elf
	chmod +x ~/DirectoryWatch/DirectoryWatch.elf
	cp start.sh ~/DirectoryWatch/start.sh
	chmod +x ~/DirectoryWatch/start.sh
	cp backend.pl ~/DirectoryWatch/backend.pl
	chmod +x ~/DirectoryWatch/backend.pl
	cp watch.jpg ~/DirectoryWatch/watch.jpg
	cp MainScreen.glade ~/DirectoryWatch/MainScreen.glade

.PHONY: install
install:
#	-rm *.o
	if ! test -d ~/DirecdtoryWatch; then \
	mkdir ~/DirectoryWatch; fi;
	cp DirectoryWatch.elf ~/DirectoryWatch/DirectoryWatch.elf
	chmod +x ~/DirectoryWatch/DirectoryWatch.elf
	cp start.sh ~/DirectoryWatch/start.sh
	chmod +x ~/DirectoryWatch/start.sh
	cp backend.pl ~/DirectoryWatch/backend.pl
	chmod +x ~/DirectoryWatch/backend.pl
	cp watch.jpg ~/DirectoryWatch/watch.jpg
	cp MainScreen.glade ~/DirectoryWatch/MainScreen.glade

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
	if ! test -d ~/.local/share/applications; then \
	mkdir ~/.local/share/applications; fi;

	-cp DirectoryWatch.desktop         ~/.local/share/applications/DirectoryWatch.desktop
	-cp DirectoryWatch.directory       ~/.local/share/desktop-directories/DirectoryWatch.directory
	-cp DirectoryWatch.menu            ~/.config/menus/applications-merged/DirectoryWatch.menu


.PHONY: uninstall
uninstall:
	-rm -r ~/DirectoryWatch
	-rm -r ~/ProjDirWatch
	-rm ~/.local/share/applications/DirectoryWatch.desktop
	-rm ~/.local/share/desktop-directories/DirectoryWatch.directory
	-rm ~/.config/menus/applications-merged/DirectoryWatch.menu

