CC=g++
CXXFLAGS=`pkg-config --cflags opencv `
LDFLAGS=`pkg-config --libs opencv`
EXEC=start

all: $(EXEC)

start: rrt.o Tree.o Noeud.o
	$(CC) -o start  Tree.o Noeud.o rrt.o $(LDFLAGS)

Tree.o: Tree.cpp Tree.h Noeud.h
	$(CC) -o Tree.o -c Tree.cpp $(CXXFLAGS)

Noeud.o: Noeud.cpp Noeud.h
	$(CC) -o Noeud.o -c Noeud.cpp $(CXXFLAGS)

rtt.o: rrt.cpp Tree.h Noeud.h
	$(CC) -o rrt.o -c rrt.cpp $(CXXFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
