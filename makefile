CFLAGS=-c
IFLAGS=-I ~/eigen

all: cutout 

cutout: cutout.o ensemble.o molecule.o atom.o
	g++ $(IFLAGS) cutout.o ensemble.o molecule.o atom.o -o cutout

cutout.o: cutout.cpp
	g++ $(CFLAGS) $(IFLAGS) cutout.cpp

ensemble.o: ensemble.cpp
	g++ $(CFLAGS) $(IFLAGS) ensemble.cpp

molecule.o: molecule.cpp
	g++ $(CFLAGS) $(IFLAGS) molecule.cpp

atom.o: atom.cpp
	g++ $(CFLAGS) $(IFLAGS) atom.cpp

clean:
	rm -rf *o test_*
