#include <TFT_HX8357.h> // Hardware-specific library
#include <Wire.h>

TFT_HX8357 tft = TFT_HX8357(); // Invoke custom library

int buttonApin = 5;
int buttonBpin = 6;
int estado = 0;
String currentCity = "";
int currentTemp = 0;

void setup() {
 

  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);

  tft.begin();

  Serial.begin(115200);
  tft.setRotation(1);	// landscape
  tft.fillScreen(TFT_BLACK);
 
}

void loop() {
  // Comprueba si alguno de los botones ha sido presionado para cambiar el estado
  if (digitalRead(buttonBpin) == LOW || digitalRead(buttonApin) == LOW) {
    if (estado == 0) {
      estado = 1; // Cambia al estado que muestra la primera ciudad
      //mostrarCiudad(); // Llama a una función que muestra la información de la ciudad
      delay(500); // Debounce
    }
  }
}

