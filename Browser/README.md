#GA1 Browser code
To build the browser code on OS X and Linux:
* Run the common steps in the top level README file.
* Build, install and start the Arduino application on the Arduino device.
* On the command line, change your working directory to the Browder sub directory.
* Generate the javascript:
  `$ \<path-to-golgi-pkg\>/LATEST/javascript/golgen.sh -browser \<developer-key-from-portal\> \<application-key-from-portal\> \<path-to-root-GA1-directory-from-GitHub\>/GA1.thrift GA1Gen.js`
* In your browser, open the file GA1.html in the Browser directory. The javascript console should show some debug about the window size and hopefully a successful registration.
* Click on the bulb image to turn the LED on and off on the board.
  
Windows
  o [COMING SOON]
