#include <VirtualWire.h>

const int transmit_pin = 11;
const int transmit_en_pin = 3;

void setup()
{
    Serial.begin(9600);
    vw_setup(2000);
    vw_set_tx_pin(11);
    pinMode(11, OUTPUT);
}

void loop()
{
    
    send("OLAAA");
    delay(2000);
}

void send(char *msg){
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();

}


