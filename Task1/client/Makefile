CC = g++
CFLAGS = -Wall

all:
	$(CC) $(CFLAGS) main.cpp ClientTCP.cpp -o Client
	x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++ main.cpp ClientTCP.cpp -o ClientEXE.exe -lwsock32
	
lin: 
	$(CC) $(CFLAGS) main.cpp ClientTCP.cpp -o Client

win:
	x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++ main.cpp ClientTCP.cpp -o ClientEXE.exe -lwsock32
