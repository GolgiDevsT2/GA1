#include <Arduino.h>
#include <libgolgi.h>
#include "GolgiGen.h"

#include "GOLGI_KEYS.h"

static GolgiAPIImpl *golgiAPIImpl;
static GolgiNetInterface *netIf = NULL;


/**************************************************/
//
// WiFi Initialisation
// 

/*
 * Create a file called WIFI-PARAMS.h that looks like this:

#ifndef __WIFI_PARAMS_H__
#define __WIFI_PARAMS_H__

#define WIFI_SSID "YOUR-WIFI-SSID";     //  your network SSID (name)
#define WIFI_PASS "YOUR-WIFI-PASSWORD"; // your network password

#endif
*/

#include "WIFI-PARAMS.h"

#if !defined(WIFI_SSID)
#error no WIFI SSID and PASSWORD defined
#endif

GolgiNetInterface *setupNetwork(){
    Serial.print("Waiting for WiFi shield to spin up:");
    for(int i = 0; i < 5; i++){
        Serial.print(".");
        delay(1000);
    }
    Serial.println("DONE");
    Serial.println("Firmware Version: " + String(WiFi.firmwareVersion()));

    Serial.println("Attempting to connect to WPA network: ");

    int wifiStatus = WL_IDLE_STATUS;
    wifiStatus = WiFi.begin(WIFI_SSID, WIFI_PASS);

    // if you're not connected, stop here:

    if ( wifiStatus != WL_CONNECTED) {
      Serial.println(String("Couldn't get a wifi connection ") + String(wifiStatus)) ;
      while(true);
    }

    return new GolgiNetWifi();
}

/**************************************************/


void memReport(void)
{
    void *addr = malloc(16);
    Serial.println("[" + String((long)addr, HEX) + "]");
    free(addr);
}

#define LED_PIN     8

class LEDControl: public GA1SetLEDRequestReceiver{
public:
    LEDControl(){
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
    };

    void registerReceivers(void){
      GA1RegisterSetLEDRequestReceiver(this);
    };
    
    void inboundSetLED(GA1SetLEDResultSender *resultSender, GA1_setLED_reqArg *arg){
	if(arg->getState() != 0){
	    digitalWrite(LED_PIN, HIGH);
	}
	else {
	    digitalWrite(LED_PIN, LOW);
	}
	resultSender->success();
    };
    
    ~LEDControl(){
    };
};


void setup() {
    Serial.begin(115200);
    Serial.println("***************");
    Serial.println("***** GA1 *****");
    Serial.println("***************");


    netIf = setupNetwork();

    golgiAPIImpl = new GolgiAPIImpl(netIf,
                                    GOLGI_APPKEY,
                                    GOLGI_DEVKEY,
                                    "HW");

     (new LEDControl())->registerReceivers();
}

long prev = 0;
long prev1 = 0;

void loop() {
    long now = millis() / 1000;
    if(now != prev){
        prev = now;
        Serial.print('.');
    }
    now /= 5;
    if(now != prev1){
       prev1 = now;
       memReport();
    }
    golgiAPIImpl->service();
    netIf->service();
}
