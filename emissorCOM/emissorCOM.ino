#include <VirtualWire.h>

const int transmit_pin = 11;
const int transmit_en_pin = 3;

unsigned long time;

unsigned long ref = 0;

char _MSG[16];

void setup(){
    Serial.begin(9600);
  
    vw_setup(2000);
    vw_set_tx_pin(11);
    
    pinMode(5, INPUT);
    pinMode(11, OUTPUT);
    
}

void loop(){
  if( digitalRead(5) ){
    send("100000000000");
    ref = millis();
    delay(1000);
  }
  
  buildMsg("2A1").toCharArray(_MSG, 16);
  
//  for(int i=0; i<strlen(_MSG); ++i){
//    Serial.write(_MSG[i]);
//  }
//  Serial.println("");
  
  send(_MSG);
  delay(1000);
}

String buildMsg(String op){
  String time_ = String(millis()-ref);
  String msg_ = op;

  for(int i = 0; i<9-time_.length(); ++i){
    msg_ += "0";
  }
  msg_ += time_;

  return msg_;
}

void send(char *msg){
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
}


