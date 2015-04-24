# GA1
GA1 is an example application using the Golgi Transport and Connectivity SDK. It's functionality is intentionally as simple as possible to allow it to showcase Golgi.

It is a simple solution that can turn on and off an LED on an Arduino board (connected to GPIO pin 8). This functionality (turning on and off the LED) can be controlled in one of three ways:
* A Web Application written in HTML and javascript
* An Android Application 
* An iOS Application

In turn, the Arduino can use one of four connectivity solutions:
* Ethernet: Uses an Arduino Ethernet Shield for IP connectivity
* WiFi: Uses an Arduino WiFi Shield for IP connectivity
* Serial: Uses a serial line (or serial over Bluetooth) via a gateway running on a local host to get IP connectivity.
* SMS: Uses a GSM Shield and SMS as a transport via a gateway connected to an GSM "dongle" that can send and receive SMS. The gateway then provides the IP connectivity.

There are four versions of the Arduino application, differing only in the transport solution that they use. These are in four sketchbook directories beneath the `Arduino` directory.

The Web Application is in the `Browser` directory, the Android and iOS Applications are in the `Android` and `iOS` directories respectively.

To build and run GA1 there are some common steps that must be taken:

* Install the latest version of the Golgi SDK somewhere (on OS X it will go under ~/Golgi-Pkg).
* In the developer portal at https://devs.golgi.io, create a new application, call it GA1.
* In this top level directory create two files:
  * `Golgi.DevKey`: a single line which has your Developer Key from the developer portal
  * `Golgi.AppKey` a single line which has your Appkication Key for GA1 from the developer portal.





