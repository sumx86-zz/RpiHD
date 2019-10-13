GODIR=cd src
FLAGS=-lpcap -lnet -lpthread

all:
	$(GODIR);\
	gcc -Wall server/server.c net.c log.c -o /usr/bin/rpi_server
	gcc -Wall main.c rpi.c rpi_rcv.c net.c log.c -o rpi $(FLAGS)