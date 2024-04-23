CC = g++
CFLAGS = -Wall

all:
	$(CC) $(CFLAGS) main.cpp SendHDDInfo.cpp ServerTCP.cpp -o Server
	x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++  main.cpp SendHDDInfo.cpp ServerTCP.cpp -o ServerEXE.exe -lwsock32

lin: 
	$(CC) $(CFLAGS) main.cpp SendHDDInfo.cpp ServerTCP.cpp -o Server

win:
	x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++  main.cpp SendHDDInfo.cpp ServerTCP.cpp -o ServerEXE.exe -lwsock32
