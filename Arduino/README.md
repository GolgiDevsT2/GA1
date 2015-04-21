#GA1 Arduino code

GA1 is a simple solution that can turn on and off an LED on an Arduino
board (connected to GPIO pin 8) using an Ardino Ethernet Shield for IP
connectivity. The Arduino is controlled via some javascript in 
a HTML file (in the Browser directory adjacent to this directory).

This directory contains the Arduino code. 

To Build On OS X, Linux and Windows in the Arduino IDE (at least version 1.6.3):

OS X/Linux
* Install the latest version of the Golgi SDK somewhere (on OS X it will
   go under ~/Golgi-Pkg)
* In the developer portal at devs.golgi.io, create a new application, call
   it GA1
* In your IDE sketchbook location, create a directory called GA1

    `$ mkdir \<path-to-sketchbook-location\>/GA1`

* Copy everything from this directory to that directory

    `$ cp \<path-to-this-directory\>/* \<path-to-sketchbook-location\>/GA1`

* Change directory to the newly created directory

    `$ cd \<path-to-sketchbook-location\>/GA`

* Generate the needed files by invoking the tool to create them:

    `$ \<path-to-golgi-pkg\>/LATEST/Arduino/golgen.sh \<developer-key-from-portal\> \<application-key-from-portal\> \<path-to-root-GA1-directory-from-GitHub\>/GA1.thrift GolgiGen`

* Import the Golgi Ethernet library into the IDE by going to Sketch/Include Library/Add .ZIP Library, navigate to the Golgi-Pkg install directory, select LATEST/Arduino and pick the Ethernet library.
* Add the SPI library and the Ethernet library from the Sketch/Include Library menu dropdown.
* Build the sketch, install it, start it.
  
Windows
  o [COMING SOON]
