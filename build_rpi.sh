#!/bin/bash

export ROOT_ID=0

if [ $UID -ne $ROOT_ID ]; then
	echo "Run it as root!"
	exit 2
fi

# install needed packages
sudo apt install libpcap-dev
sudo apt install libnet-dev  # http://launchpadlibrarian.net/355752893/libnet1_1.1.6+dfsg-3.1_amd64.deb

#build RPI
gcc -Wall src/main.c src/rpi.c src/rpi_rcv.c src/net.c src/log.c -o rpi -lpcap -lnet -lpthread
mv rpi /usr/bin