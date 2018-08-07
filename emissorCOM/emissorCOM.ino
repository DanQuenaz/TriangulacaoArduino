#include <VirtualWire.h>

const int transmit_pin = 11;
const int transmit_en_pin = 3;

unsigned long time;

void setup()
{
    Serial.begin(9600);
    vw_setup(2000);
    vw_set_tx_pin(11);
    pinMode(11, OUTPUT);
    pinMode(5, INPUT);
}

void loop(){
//    Serial.print("Time: ");
//    time = millis();
//    Serial.println(time);    //prints time since program started
//    delay(1000);
    if( digitalRead(5) ){
      send("1000000000");
      delay(1000);
    }
}

void send(char *msg){
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
}


