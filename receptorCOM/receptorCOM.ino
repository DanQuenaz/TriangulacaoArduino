#include <VirtualWire.h>

byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;

void setup(){
  Serial.begin(9600);
  
  vw_setup(2000);
  vw_set_rx_pin(12);
  pinMode(12, INPUT);
  vw_rx_start();
}

void loop(){
  if(vw_get_message(message, &messageLength)){
    Serial.println("Receveid: ");
    for(int i=0; i<messageLength; ++i){
      Serial.write(message[i]);
    }
    Serial.write('\n');
  }
}


