# RpiHD

Raspberry Pi Host Discovery
### Pi model is 3 B+ but it should work on others as well
### Development platform was Linux mint. It should work on Ubuntu and Kali too

## Intro
* RpiHD consists of two programs:
* -- One that runs on your local machine (the server)
* -- One that runs on the raspberry pi (rpi)
* The one that runs on the rapberry pi performs the host discovery and each time it receives a reply from a host it sends that information to the server

## Installation

* On the local machine:
    ```
    chmod +x build.sh
    sudo ./build.sh
        
    # This creates the server executable /usr/bin/rpi_server
    # Also creates the directory /var/log/rpihd which is used by the server
    ```

* On the raspberry pi:
    ```
    chmod +x build_rpi.sh
    sudo ./build_rpi.sh

    # This creates the rpi executable /usr/bin/rpi
    ```

## Usage

```
    rpi_server -h
    rpi -h
```