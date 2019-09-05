CPPFLAGS=-g	-Wall	-pedantic	-Wextra
PROGRAM=kuznikos

all:	compile	doc

run:	compile
	./$(PROGRAM)

doc:	src/*
	doxygen	src/Doxyfile

compile:	src/main.o	src/Ant.o	src/AntClan.o	src/AntHome.o	src/Attack.o	src/Border.o	src/Coord.o src/Game.o  src/GameWindow.o    src/Menu.o  src/SearchRoute.o
	g++	$(CPPFLAGS)	$^	-lncurses   -o  $(PROGRAM)

clean:
	rm	-rf	$(PROGRAM)	src/*.o	*.a	doc/

%o:	*/%cpp
	g++	$(CPPFLAGS)	-c	-o	$@	$<

src/main.o:	src/main.cpp	src/GameWindow.h	src/Border.h	src/Game.h

src/Ant.o:	src/Ant.cpp src/Ant.h src/Coord.h    src/AntHome.h

src/AntClan.o:	src/AntClan.h   src/AntClan.cpp	src/AntHome.h   src/Ant.h

src/AntHome.o:	src/AntHome.cpp	src/AntHome.h	src/Ant.h   src/SearchRoute.h   src/Coord.h

src/Attack.o:	src/Attack.cpp	src/Attack.h	src/AntClan.h   src/Ant.h

src/Border.o:	src/Border.h	src/Border.cpp	src/Coord.h

src/Coord.o:	src/Coord.cpp	src/Coord.h

src/Game.o:	src/Game.cpp	src/Game.h  src/GameWindow.h    src/Border.h   src/Attack.h src/Menu.h

src/GameWindow.o:	src/GameWindow.h	src/GameWindow.cpp  src/AntHome.h    src/AntClan.h  src/Border.h    src/AntClan.h

src/Menu.o:	src/Menu.h	src/Menu.cpp  src/AntHome.h    src/Border.h  src/AntClan.h

src/SearchRoute.o:	src/SearchRoute.h	src/SearchRoute.cpp  src/Coord.h    src/Border.h    src/Attack.h