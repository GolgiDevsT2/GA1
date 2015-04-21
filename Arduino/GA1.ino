#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

#include <SPI.h>

#include <Arduino.h>
#include <libgolgi.h>
#include "GolgiGen.h"

#include "GOLGI_KEYS.h"

static GolgiAPIImpl *golgiAPIImpl;
static GolgiNetInterface *netIf = NULL;

byte mac[] = { 0x90, 0xa2, 0xda, 0x0e, 0xc7, 0x89 };

#define LED_PIN     8

#if 0
GolgiNetInterface *golgiNetworkSetup(void)
{

    Serial.print("Waiting for WiFi shield to spin up:");
    for(int i = 0; i < 5; i++){
        Serial.print(".");
        delay(1000);
    }
    Serial.println("DONE");
    Serial.println("Firmware Version: " + String(WiFi.firmwareVersion()));

    Serial.print("Attempting to connect to WPA network: ");

    int wifiStatus = WL_IDLE_STATUS;
    wifiStatus = WiFi.begin("GOLGI-G", "d0gb3rt08");

    // if you're not connected, stop here:

    if ( wifiStatus != WL_CONNECTED) {
        Serial.print("FAILED");
      Serial.println(String("Couldn't get a wifi connection ") + String(wifiStatus)) ;
      while(true);
    }
    Serial.print("SUCCESS");



    return  new GolgiNetWifi();
}
#endif


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
    

#if 1
    if(Ethernet.begin(mac) == 0){
        Serial.println("Couldn't setup Ethernet");
        while(true);
    }
    golgiAPIImpl = new GolgiAPIImpl(netIf = new GolgiNetEther(),
                                    GOLGI_APPKEY,
                                    GOLGI_DEVKEY,
                                    "HW");
#else
    golgiAPIImpl = new GolgiAPIImpl(netIf = golgiNetworkSetup(),
                                    GOLGI_APPKEY,
                                    GOLGI_DEVKEY,
                                    "HW");
#endif

     (new LEDControl())->registerReceivers();

}

void loop() {
    golgiAPIImpl->service();
    netIf->service();
}
