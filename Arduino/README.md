#GA1 Arduino code

GA1 is a simple solution that can turn on and off an LED on an Arduino
board (connected to GPIO pin 8). There are four solutions in this directory
using four different transports:
* Ethernet: Uses an Arduino Ethernet Shield for IP connectivity
* WiFi: Uses an Arduino WiFi Shield for IP connectivity
* Serial: Uses a serial line (or serial over Bluetooth) via a gateway running on a local host to get IP connectivity.
* SMS: Uses a GSM Shield and SMS as a transport via a gateway connected to an GSM "dongle" that can send and receive SMS. The gateway then provides the IP connectivity.

Each transport has its own Sketchbook location.

There are three different clients to control the Arduino board. These clients are in directories adjacent to this Arduino directory:
* A HTML file to control the LED
* An Android Application to control the LED
* An iOS Application to control the LED.



To Build On OS X, Linux and Windows in the Arduino IDE (at least version 1.6.3):

* Install the latest version of the Golgi SDK somewhere (on OS X it will
   go under ~/Golgi-Pkg, on Linux and Windows it will go wherever you untar/unzip it).
* In the developer portal at devs.golgi.io, create a new application, call
   it GA1
* Change your IDE sketchbook location to point at appropriate sketchbook location for the transport you wish to use (Ethernet/WiFi/Serial/SMS). 
* Generate the needed files by invoking the tool to create them:
  * On OS X/Linux: `$ <path-to-golgi-pkg>/LATEST/Arduino/golgen.sh <developer-key-from-portal> <application-key-from-portal> ../../../GA1.thrift GolgiGen`
  * On Windows `$ <path-to-latest-golgi-pkg>\Arduino\golgen.bat <developer-key-from-portal> <application-key-from-portal> ..\..\..\GA1.thrift GolgiGen`
* Import the appropriate Golgi library into the IDE by going to Sketch/Include Library/Add .ZIP Library, navigate to the Golgi-Pkg install directory, select LATEST/Arduino and pick the appropriate library.
* If you are using WiFi or SMS, look at the GA1.ino file for directions on how to supply the necessary supplemental information (SSID and password for WiFi, phone number of the SMS gateway). 
* If you are using Ethernet, add the SPI and Ethernet libraries to your sketch via the Sketch/Library menu item
* If you are using WiFi, add the SPI and WiFi libraries to your sketch via the Sketch/Library menu item

