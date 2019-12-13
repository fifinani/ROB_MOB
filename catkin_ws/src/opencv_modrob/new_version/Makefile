CC=g++
CXXFLAGS=`pkg-config --cflags opencv `
LDFLAGS=`pkg-config --libs opencv`
EXEC=start

all: $(EXEC)



start: rrt.o Tree.o Node.o
	$(CC) -o start  Tree.o Node.o rrt.o $(LDFLAGS)

Tree.o: Tree.cpp Tree.h Node.h
	$(CC) -o Tree.o -c Tree.cpp $(CXXFLAGS)

Node.o: Node.cpp Node.h
	$(CC) -o Node.o -c Node.cpp $(CXXFLAGS)

rtt.o: rrt.cpp Tree.h Node.h
	$(CC) -o rrt.o -c rrt.cpp $(CXXFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
