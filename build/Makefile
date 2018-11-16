CC=g++
CXXFLAGS=-I$(IDIR) -std=c++11 -g -lncurses

ODIR=../src
IDIR=../include


_OBJ = menu.o terrain.o main.o menu.o iatester.o path.o node.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all:main

$(ODIR)/menu.o: $(ODIR)/menu.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/terrain.o: $(ODIR)/terrain.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/iatester.o: $(ODIR)/iatester.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/node.o: $(ODIR)/node.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/path.o: $(ODIR)/path.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)


main.o: $(ODIR)/main.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

menu.o: $(ODIR)/menu.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
