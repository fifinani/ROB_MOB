CC=g++
CXXFLAGS=`pkg-config --cflags opencv `
LDFLAGS=`pkg-config --libs opencv`
EXEC=start

all: $(EXEC)

start: rrt.o
	$(CC) -o start  rrt.o $(LDFLAGS)

btree.o: btree.cpp
	$(CC) -o bree.o -c btree.cpp

rtt.o: rrt.cpp
	$(CC) -o rrt.o -c rrt.cpp $(CXXFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
