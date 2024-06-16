CPP = g++
CC = gcc
CFLAGS = -Wall


all: main.o getInfo.o
	$(CPP) $(CFLAGS) main.o getInfo.o -o Sniffer

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

getInfo.o: getInfo.cpp
	$(CPP) $(CFLAGS) -c getInfo.cpp

clean:
	rm -rf *.o
	rm -rf Sniffer

build: main.o getInfo.o

link: 
	$(CPP) $(CFLAGS) main.o getInfo.o -o Sniffer
