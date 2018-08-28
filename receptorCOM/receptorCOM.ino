#include <VirtualWire.h>

byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;


double dA = 23.1821;
double aX = 38.5; // coordenada X da referência A
double aY = 23.7; // coordenada Y da referência A

double dB = 17.5354;
double bX = 41.2; // coordenada X da referência B
double bY = 62.8; // coordenada Y da referência B

double dC = 14.1524;
double cX = 52.5; // coordenada X da referência C
double cY = 58.1; // coordenada Y da referência C

double velocidade = 300.0;

double erro = 0.2; //Margem de erro aceitável

unsigned long ref = 0;

void setup(){
  Serial.begin(9600);
  
  vw_setup(2000);
  vw_set_rx_pin(12);
  pinMode(12, INPUT);
  
  vw_rx_start();
}

void loop(){
  if(vw_get_message(message, &messageLength)){
    if(message[0] == '1'){
      ref = millis();
      Serial.println(millis() - ref);
    }else if(message[0] == '2' ){
      for(int i=0; i<messageLength; ++i){
        Serial.write(message[i]);
      }
      Serial.println("");
        unsigned long aux = atoi(message+3);
        Serial.println(millis()-ref);
        //Serial.println(aux);
    }
  }
  
  
//  
//  Serial.write('\n');
//  double pX = 0.0;
//  double pY = 0.0;
//
//  calcPontos(pX, pY);
//  Serial.println(pX);
//  Serial.println(pY);
  
  
}

void calcPontos(double &pX, double &pY){ 
   double k1 = ( (dA*dA) - (dB*dB) - (aX*aX) - (aY*aY) + (bY*bY) + (bX*bX) )/( 2 * (bX - aX) );
   double k2 = (-(bY - aY))/(bX-aX);

   double a = (k2*k2) + 1;
   double b = (2*k1*k2)-(2*aX*k2)-(2*aY);
   double c = (aY*aY) + (k1*k1) - (2*aX*k1) + (aX*aX) - (dA*dA);
   double pY1, pY2;

   if(calcRaiz( a, b, c, pY1, pY2 )){
     double pX1 = ((dA*dA) - (dB*dB) - (aX*aX) - (aY*aY) + (bY*bY) + (bX*bX)) / ( 2*(bX-aX)) - (pY1*(bY-aY)/(bX-aX)) ;
     double pX2 = ((dA*dA) - (dB*dB) - (aX*aX) - (aY*aY) + (bY*bY) + (bX*bX)) / ( 2*(bX-aX)) - (pY2*(bY-aY)/(bX-aX)) ;

     double aux = ( (pX1 - cX)*(pX1 - cX) + (pY1 - cY)*(pY1 - cY) - (dC*dC));
     
     if( aux >= -erro && aux <= erro){
       pX = pX1;
       pY = pY1;
     }else{
       pX = pX2;
       pY = pY2;
     }
   }
}

bool calcRaiz(double a, double b, double c, double &r1, double &r2){
  double delta = (b*b) - (4*a*c);
  if(delta > 0.0){
    r1 = (-b + sqrt(delta))/(2*a);
    r2 = (-b - sqrt(delta))/(2*a);
    return true;
  }
  return false;
}


