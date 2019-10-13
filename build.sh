#!/bin/bash

export ROOT_ID=0

logdir=/var/log
rpidir=rpihd

if [ $UID -ne $ROOT_ID ]; then
	echo "Run it as root!"
	exit 2
fi

if [ ! -d $logdir/$rpidir ]; then
	cd $logdir
	mkdir $rpidir
else
	echo "$logdir/$rpidir - already exists!"
fi

# build server
gcc -Wall src/server/server.c src/net.c src/log.c -o /usr/bin/rpi_server