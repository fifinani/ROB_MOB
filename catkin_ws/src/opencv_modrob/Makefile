CC=g++
CXXFLAGS=`pkg-config --cflags opencv `
LDFLAGS=`pkg-config --libs opencv`
EXEC=start

all: $(EXEC)



start: rrt.o Btree.o
	$(CC) -o start  Btree.o rrt.o $(LDFLAGS)

Btree.o: Btree.cpp Btree.h
	$(CC) -o Btree.o -c Btree.cpp

rtt.o: rrt.cpp Btree.h
	$(CC) -o rrt.o -c rrt.cpp $(CXXFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
