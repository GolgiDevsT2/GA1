#include <Arduino.h>
#include <libgolgi.h>
#include "GolgiGen.h"

#include "GOLGI_KEYS.h"

static GolgiAPIImpl *golgiAPIImpl;
static GolgiNetInterface *netIf = NULL;


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

class SerialIF : public GolgiSerialInterface
{
public:
    void begin(void){
        pinMode(19, INPUT_PULLUP);
        Serial1.begin(38400);
    };

    int available(void){
        return Serial1.available();
    };

    void write(const uint8_t *data, int len){
        Serial1.write(data, len);
    };

    int readBytes(char *buf, int max){
        return Serial1.readBytes(buf, max);
    };

};


void setup() {
    Serial.begin(115200);
    Serial.println(F("***************"));
    Serial.println(F("***** GA1 *****"));
    Serial.println(F("***************"));
    
    netIf = new GolgiNetSerial(new SerialIF());

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
