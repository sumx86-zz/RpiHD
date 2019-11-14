# RpiHD

Raspberry Pi Host Discovery
### Pi model is 3 B+
### Development platform was Linux mint.

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
    # Also creates the directory /var/log/rpihd which is used by the server and another executable called rpilog to display server log
    ```

* On the raspberry pi:
    ```
    chmod +x build_rpi.sh
    sudo ./build_rpi.sh

    # This creates the rpi executable /usr/bin/rpi and another executable called rpilogtmp to display the rpi log (this is a temporary file)
    ```
