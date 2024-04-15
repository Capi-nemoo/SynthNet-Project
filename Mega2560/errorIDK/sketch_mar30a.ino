/*
asdsa
a  Programarfacil https://programarfacil.com
  Autor: Luis del Valle @ldelvalleh
  Comunicación I2C entre dos Arduinos, maestro
*/

#include <Wire.h>
#include "IRremote.h"
int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin 11
IRrecv irrecv(receiver);  
  //String ciudad[] = {"Houston", "Lubbock", "Miami", "Berlin"};
byte Temp = 12;
byte var_ciudad = 0;
void setup() {
  // Unimos este dispositivo al bus I2C
  Wire.begin();
  Serial.begin(9600);
  irrecv.enableIRIn();
  
}
void loop() {

  if (irrecv.decode()) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
//byte ciudad[] = {1, 2, 3, 4};
  if (var_ciudad == 1)
  {
    // Comenzamos la transmisión al dispositivo 1
    Wire.beginTransmission(1);
    Wire.write(Temp);
    Wire.write(1);
    Wire.endTransmission();
    delay(100);
  }
  if (var_ciudad == 2)
  {
    Wire.beginTransmission(1);
    Wire.write(Temp);
    Wire.write(2);
    Wire.endTransmission();
    delay(100);
  }
  if (var_ciudad == 3)
  {
    Wire.beginTransmission(1);
    Wire.write(Temp);
    Wire.write(3);
    Wire.endTransmission();
    delay(00);
  }
  if (var_ciudad == 4)
  {
    Wire.beginTransmission(1);
    Wire.write(Temp);
    Wire.write(4);
    Wire.endTransmission();
    delay(200);
  }
}

void translateIR() // takes action based on IR code received
{ //map the IR code to the remote key
  switch (irrecv.decodedIRData.decodedRawData)
  {
    case 0xB946FF00: var_ciudad += 1; break;
    case 0xF807FF00: var_ciudad -= 1;    break;
    case 0xEA15FF00: var_ciudad -= 1;;    break;
    case 0xF609FF00: var_ciudad += 1;    break;
    case 0xE916FF00: var_ciudad = 0;  break; // Modificado para incrementar var_ciudad
    case 0xF30CFF00: var_ciudad = 1;  break; // Modificado para incrementar var_ciudad
    case 0xE718FF00: var_ciudad = 2;  break; // Modificado para incrementar var_ciudad
    case 0xA15EFF00: var_ciudad = 3;  break; // Modificado para incrementar var_ciudad
    case 0xF708FF00: var_ciudad = 4;   break; // Supuesto caso adicional para ilustrar
  }
  delay(500); // Do not get immediate repeat
} //END translateIR

