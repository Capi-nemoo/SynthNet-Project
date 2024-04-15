
#include <TFT_HX8357.h> // Hardware-specific library
#include <Wire.h>

TFT_HX8357 tft = TFT_HX8357(); // Invoke custom library

int mega_Capa = 0;
int megaTemp = 0;
String megaCity = "";

void setup() {

//I2C
  Wire.begin(4); // Inicia I2C con dirección 4, ajusta según tu configuración
  Wire.onReceive(receiveEvent); // Registra el evento de recepción I2C


//Display TFTLCD arduinomega 
  tft.begin();
  Serial.begin(115200);
  tft.setRotation(0);	
  uint16_t colorNegro = 0x0000;
  tft.fillScreen(colorNegro);
  uint16_t brightRed = ((25 << 11) | (0 << 5) | 0);
  tft.fillScreen(TFT_RED);
  drawThickH(175, 120, TFT_WHITE, 35);
  drawThickHWithBorder2(164, 221, colorNegro, 10);
  drawThickHWithBorder(165, 120, colorNegro, 10);
  drawThickU(35, 120, TFT_WHITE, 35);
  drawThickUWithBorder(25, 120, colorNegro, 10);
  tft.setTextSize(2); // Asume un tamaño de texto
  tft.setCursor(144, 445);
  tft.setTextColor(TFT_BLACK);    
  tft.println("Renato Ramirez"); // Imprime el nombre de la ciudad

// Usa el color para dibujar una forma, por ejemplo, llenar la pantalla

}


void drawThickUWithBorder(int x, int y, uint16_t color, int thickness) {
  // El grosor del borde; ajústalo según sea necesario.
  int borderThickness = 1; // Puedes cambiar esto según el grosor deseado del borde.
  
  // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado.
  int bottomThickness = max(1, thickness / 1.2);

  // Primero, dibuja el borde negro alrededor de la U.
  for (int i = -borderThickness; i < thickness + borderThickness; i++) {
    // Borde izquierdo
    tft.drawFastVLine(x + i - borderThickness, y - borderThickness, 179 + 2 * borderThickness, TFT_BLACK);
    // Borde derecho
    tft.drawFastVLine(x + 65 + i, y - borderThickness, 149 + 2 * borderThickness, TFT_BLACK);
  }
}

void drawThickHWithBorder(int x, int y, uint16_t color, int thickness) {
  // El grosor del borde; ajústalo según sea necesario.
  int borderThickness = 1; // Puedes cambiar esto según el grosor deseado del borde.
  
  // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado.
  int bottomThickness = max(1, thickness / 1.2);

  // Primero, dibuja el borde negro alrededor de la U.
  for (int i = -borderThickness; i < thickness + borderThickness; i++) {
    // Borde izquierdo
    tft.drawFastVLine(x + i - borderThickness, y - borderThickness, 179 + 2 * borderThickness, TFT_BLACK);
    // Borde derecho
    tft.drawFastVLine(x + 65 + i, y - borderThickness, 64 + 2 * borderThickness, TFT_BLACK);
  }
}

void drawThickHWithBorder2(int x, int y, uint16_t color, int thickness) {
  // El grosor del borde; ajústalo según sea necesario.
  int borderThickness = 1; // Puedes cambiar esto según el grosor deseado del borde.
  
  // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado.
  int bottomThickness = max(1, thickness / 1.2);

  // Primero, dibuja el borde negro alrededor de la U.
  for (int i = -borderThickness; i < thickness + borderThickness; i++) {
    // Borde derecho
    tft.drawFastVLine(x + 65 + i, y - borderThickness, 80 + 2 * borderThickness, TFT_BLACK);
  }
}


void drawThickH(int x, int y, uint16_t color, int thickness) {
  // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado,
  // asegurándote de que el valor sea al menos 1 para que se dibuje algo.
  int bottomThickness = max(1, thickness / 1);

  for (int i = 0; i < thickness; i++) {
    // Dibuja la parte izquierda de la U
    tft.drawFastVLine(x + i, y, 180, color); // Ajusta la altura según sea necesario

    // Dibuja la parte derecha de la U
    tft.drawFastVLine(x + 65 + i, y, 180, color);
  }

  // Ahora, dibuja la parte inferior de la U con el nuevo grosor calculado.
  // Centra esta parte más delgada ajustando el inicio y el largo de acuerdo al grosor.
  for (int j = 0; j < bottomThickness; j++) {
    tft.drawFastHLine(x, y + 65 + j, 65 + thickness, color); // Ajusta el inicio y el largo si es necesario
  }
}


void drawThickU(int x, int y, uint16_t color, int thickness) {
  // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado,
  // asegurándote de que el valor sea al menos 1 para que se dibuje algo.
  int bottomThickness = max(1, thickness / 1.2);

  for (int i = 0; i < thickness; i++) {
    // Dibuja la parte izquierda de la U
    tft.drawFastVLine(x + i, y, 175, color); // Ajusta la altura según sea necesario

    // Dibuja la parte derecha de la U
    tft.drawFastVLine(x + 65 + i, y, 175, color);
  }

  // Ahora, dibuja la parte inferior de la U con el nuevo grosor calculado.
  // Centra esta parte más delgada ajustando el inicio y el largo de acuerdo al grosor.
  for (int j = 0; j < bottomThickness; j++) {
    tft.drawFastHLine(x, y + 150 + j, 65 + thickness, color); // Ajusta el inicio y el largo si es necesario
  }
}
 



void receiveEvent(int howMany) {
  if(howMany <= 0) return;
  int maestro_Capa;//== Wire.read();
  mega_Capa =+ 1;
  if (maestro_Capa == 1);
  { 
    mega_Capa = maestro_Capa;
    String receivedMsg = "";

    while (Wire.available()) 
    {
      char c;
    c = Wire.read();
    receivedMsg += c;
    }
  // Asume formato "Ciudad,Temperatura"
  int separatorIndex = receivedMsg.indexOf(',');
    if (separatorIndex != -1) {
      megaCity = receivedMsg.substring(0, separatorIndex);
      megaTemp = receivedMsg.substring(separatorIndex + 1).toInt();
      //Ahora que tienes los nuevos valores, actualiza la pantalla
      //updateDisplay();
    }
    else if (maestro_Capa == 2)
  {
    /* code */
    mega_Capa = maestro_Capa;
  }
    else if (maestro_Capa == 3)
  {
    /* code */
    mega_Capa == maestro_Capa;
  }
    else if (maestro_Capa == 4)
  {
    /* code */
    mega_Capa = maestro_Capa;
  }
 }
}


void city_updateDisplay() {

  tft.fillScreen(TFT_BLACK); // Limpia la pantalla
  tft.setCursor(0, 40); // Establece el cursor
  tft.print("City: ");
  tft.println(megaCity);
  tft.print("Temp: ");
  tft.println(megaTemp);
  tft.println(" F");
}

void loop() {
  void receiveEvent();
  delay(5000);
  mega_Capa = 3;
      switch (mega_Capa) {
    case 1:
    tft.fillScreen(TFT_BLACK); 
    tft.print("estado 1!");
    delay(1000)
    //city_updateDisplay();
      break;
    case 2:
    tft.fillScreen(TFT_BLACK);
    tft.print("estado 2!"); 
   //temperature, etc of the room    
      break;
    case 3:
  tft.println("ENO Ramirez");
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(144, 445);
  tft.setTextColor(TFT_WHITE);  
  tft.println("Renato Ramirez");
  delay(1000)
  //mega_Capa = 0;
    //Base de datos UHHH!
      break;
    case 4:
    tft.fillScreen(TFT_BLACK);
    tft.print("estado 4!"); 
     //aun nose jaja
      break;
    }    
   }
 //} 

