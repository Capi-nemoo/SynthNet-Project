#include <config.h>

void setup() 
{
 //I2C
  Wire.begin(4); // Inicia I2C con dirección 4, ajusta según tu configuración
  Wire.onReceive(receiveEvent); // Registra el evento de recepción I2C


  //Display TFTLCD arduinomega 
  tft.begin();
  Serial.begin(9600);
  drawUHlogo();
  delay(7000);
  tft.setTextColor(TFT_WHITE);
}

void loop() {
 delay(300);
}

void receiveEvent(int howMany) {
  if (howMany <= 0) return;
  
  displayLayer = Wire.read(); // Lee el primer byte de lo que envió el maestro
  
  // Puedes agregar un chequeo aquí para asegurarte que displayLayer es válido
  if (displayLayer < 1 || displayLayer > 4) {
    Serial.println("Display layer out of range.");
    tft.fillScreen(TFT_BLACK);  // Pantalla en negro si la capa no es válida
    return;
  }
  selection_Layer();  // Procesa la capa recibida
}

void selection_Layer() {
  switch (displayLayer) {
    case 1:
      handleTemperatureRoomData();
      break;
    case 2:
      handleWeatherData();
      break;
    case 3:
      handleUHData();
      break;
    case 4:
      handleTasklistData();
      break;
    default:
      tft.fillScreen(TFT_BLACK); // Limpia la pantalla si ninguna opción coincide
      break;
  }
}

// Ejemplo de función modular para manejar datos de temperatura del cuarto
void handleTemperatureRoomData() {
  // Código específico para manejar la temperatura del cuarto
}

// Continúa con funciones similares para otros casos
String receiveString() {
  int length = Wire.read();  // Leer la longitud de la cadena
  char str[length + 1];      // Crear buffer para almacenar la cadena
  Wire.readBytes(str, length);
  str[length] = '\0';        // Terminar la cadena correctamente
  return String(str);
}

void handleWeatherData()
{

  // Leer los datos de tipo double directamente en las variables de la estructura
  Wire.readBytes((char*)&cityData.temp, sizeof(cityData.temp));
  Wire.readBytes((char*)&cityData.feels_like, sizeof(cityData.feels_like));
  Wire.readBytes((char*)&cityData.temp_min, sizeof(cityData.temp_min));
  Wire.readBytes((char*)&cityData.temp_max, sizeof(cityData.temp_max));
  Wire.readBytes((char*)&cityData.humidity, sizeof(cityData.humidity));

  // Leer las cadenas
  cityData.country = receiveString();
  cityData.clima_condicion = receiveString();

  printReceivecitydData(cityData);
}
  
void handleTasklistData()
{
  /*code*/  
}

void handleUHData()
{
  /*code*/  
}

  void selection1() 
{
  if (selection == 1) 
  {
    blinkText("HOUSTON              ", 50, 100);
  } 
  else 
  {
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(50, 100);
    tft.print("HOUSTON");
  }
}
  void selection2() 
{
  if (selection == 2) 
  {
    blinkText("TEXAS                ", 50, 200);
  } 
  else 
  {
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(50, 200);
    tft.print("TEXAS");
  }
}
  void selection3() 
{
  if (selection == 3) 
  {
    blinkText("UNIVERSITY OF HOUSTON", 50, 300);
  } 
  else 
  {
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(50, 300);
    tft.print("UNIVERSITY OF HOUSTON");
  }
}

void blinkText(const String &text, int x, int y) 
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis; // Actualiza el tiempo del ultimo cambio

    // ve si el texto estaa actualmente visible y lo alterna
    static bool isVisible = false;
    isVisible = !isVisible;

    if (isVisible) 
    {
      tft.setTextColor(TFT_WHITE, TFT_BLACK); // Texto visible
    } 
    else 
    {
      tft.setTextColor(TFT_BLACK, TFT_WHITE); // Texto oculto (mismo color que el fondo)
    }
    //posicion
    tft.setCursor(x, y);
    tft.print(text);
  }
}

void printReceivecitydData(const CityData& cityData) {
  // Print the received data for verification
  Serial.println("Received Data:");
  Serial.println("Temperature: " + String(cityData.temp));
  Serial.println("Feels Like: " + String(cityData.feels_like));
  Serial.println("Minimum Temperature: " + String(cityData.temp_min));
  Serial.println("Maximum Temperature: " + String(cityData.temp_max));
  Serial.println("Humidity: " + String(cityData.humidity));
  Serial.println("Country: " + cityData.country);
  Serial.println("Weather Condition: " + cityData.clima_condicion);
}

void drawUHlogo()
{
  tft.setRotation(0);	
  tft.fillScreen(TFT_RED);
  //llama funciones de dibujo logo UH
  drawThickH(175, 120, TFT_WHITE, 35);
  drawThickHWithBorder2(164, 221, TFT_BLACK, 10);
  drawThickHWithBorder(165, 120, TFT_BLACK, 10);
  drawThickU(35, 120, TFT_WHITE, 35);
  drawThickUWithBorder(25, 120, TFT_BLACK, 10);
  //Escribe mi nombra esquina inferior derecha
  tft.setTextSize(2); // Asume un tamaño de texto
  tft.setCursor(144, 445);
  tft.setTextColor(TFT_BLACK);    
  tft.println("Renato Ramirez");
}
  void drawThickH(int x, int y, uint16_t color, int thickness) 
{
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
    for (int j = 0; j < bottomThickness; j++)
    {
      tft.drawFastHLine(x, y + 65 + j, 65 + thickness, color); // Ajusta el inicio y el largo si es necesario
    }
}
  void drawThickU(int x, int y, uint16_t color, int thickness) 
{
  // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado,
  // asegurándote de que el valor sea al menos 1 para que se dibuje algo.
  int bottomThickness = max(1, thickness / 1.2);

  for (int i = 0; i < thickness; i++) 
  {
    // Dibuja la parte izquierda de la U
      tft.drawFastVLine(x + i, y, 175, color); // Ajusta la altura según sea necesario

    // Dibuja la parte derecha de la U
      tft.drawFastVLine(x + 65 + i, y, 175, color);
  }

  // Ahora, dibuja la parte inferior de la U con el nuevo grosor calculado.
  // Centra esta parte más delgada ajustando el inicio y el largo de acuerdo al grosor.
  for (int j = 0; j < bottomThickness; j++) 
  {
    tft.drawFastHLine(x, y + 150 + j, 65 + thickness, color); // Ajusta el inicio y el largo si es necesario
  }
}
  void drawThickUWithBorder(int x, int y, uint16_t color, int thickness) 
{
  // El grosor del borde; ajústalo según sea necesario.
  int borderThickness = 1; // Puedes cambiar esto según el grosor deseado del borde.

  // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado.
  int bottomThickness = max(1, thickness / 1.2);

  // Primero, dibuja el borde negro alrededor de la U.
  for (int i = -borderThickness; i < thickness + borderThickness; i++) 
  {
    // Borde izquierdo
    tft.drawFastVLine(x + i - borderThickness, y - borderThickness, 179 + 2 * borderThickness, TFT_BLACK);
    // Borde derecho
    tft.drawFastVLine(x + 65 + i, y - borderThickness, 149 + 2 * borderThickness, TFT_BLACK);
  }
}
  void drawThickHWithBorder(int x, int y, uint16_t color, int thickness) 
{
  int borderThickness = 1; 
  int bottomThickness = max(1, thickness / 1.2);

  //borde negro alrededor de la U.
  for (int i = -borderThickness; i < thickness + borderThickness; i++) {
    // Borde izquierdo
    tft.drawFastVLine(x + i - borderThickness, y - borderThickness, 179 + 2 * borderThickness, TFT_BLACK);
    // Borde derecho
    tft.drawFastVLine(x + 65 + i, y - borderThickness, 64 + 2 * borderThickness, TFT_BLACK);
  }
}
  void drawThickHWithBorder2(int x, int y, uint16_t color, int thickness) 
{
  // El grosor del borde
  int borderThickness = 1;
  int bottomThickness = max(1, thickness / 1.2);
  for (int i = -borderThickness; i < thickness + borderThickness; i++) 
  {
    tft.drawFastVLine(x + 65 + i, y - borderThickness, 80 + 2 * borderThickness, TFT_BLACK);
  }
}

//temlates (solo pruebas visuales sin variables )
void run_Template()
{ 
  // variables templates no matters
  const long duracion_template = 10000;
  int selection_template = 0;
  long previousMillistemplate = 0;
  int supervisor_template = 1;
  unsigned long tiempo_template = millis();

  loopScreen(); //loop para que pase por todas las capas

  if (tiempo_template - previousMillistemplate >= duracion_template && selection_template < 5)
  { 
    switch (selection_template) 
    {
      case 1:
        template_capa1();
        break;
      case 2:
        template_capa2();
        break;
      case 3:
        template_capa3(); // si causa un prvbleam es porque quite el tftBLACK de aqui y el else if con templatea capa3 al final pero, pero no deberia unha puta mierda
        break;
      case 4:
        template_capa4();
        break;          
    }
  }
}

void template_capa1()
{ 
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(20, 15);
  tft.setTextColor(TFT_WHITE);
  tft.println("  University of "); //University of houston
      tft.println("      Houston");
  tft.println(" ");
  tft.println(" ");
  tft.setTextSize(2.8);
  tft.setCursor(0, 80);
  tft.println("*  Sensor1 Temp: 28.0 F");//temperatura sensor 1
  tft.println(" ");
  tft.println("*  Sensor2 Temp: 24.0 F");//temperatura sensor 2
  tft.println(" ");
  tft.println("*  Avg Temp:     26.0 F");//temperatura promedio entre senso1 y sensor2("");
  tft.println(" ");
  tft.println("*  Humidity:     80  %");//humedad habitacion

}

void template_capa2()
{
  capa2prints();
}
  void capa2prints()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(35, 10);;
  tft.print("    Houston");//idea: crear funcion para que mida que tantas letras tiene la ciudad para centrarla 
  tft.println();
  tft.setTextSize(2.2);
  tft.setCursor(0, 50);
  tft.print("Temperatura:    75.5  F                 ");
  tft.println("   ");
  tft.print("     lluvia:     2.3  mm            ");
  tft.println("   ");
  tft.print("     Viento:    15.5  km/h           ");
  tft.println("   ");
  tft.print("Visibilidad:   10000  m             ");
  tft.println();
  tft.print("    Humedad:      80  %                 ");
  tft.println();
  tft.print("  Indice UV:       5  H                 ");
  tft.println();
}

void template_capa3()
{
  comodinloco();
  selection1();
  selection2();
  selection3();
}
  void loopScreen()
{
  previousMillistemplate = tiempo_template;

  if (selection_template == 4) //hasta el template n`4
  {
    supervisor_template = -1;
  }
  else if (selection_template == 1) //cuando llegue a 1 el proximo suma psr que vuelva a 2
  {
    supervisor_template = 1;
  }
  selection_template += supervisor_template;
}
void comodinloco()
{
  if (comodin == 1)
  {
    tft.fillScreen(TFT_BLACK);
    comodin = 0;
  }

}

void template_capa4()
{
  drawUHlogo();
}

/*void ideasoCosas(){


/*
void selection_Layer()
{
  if (displayLayer == 1)/*capa datos de temperatura del cuarto
  {   
   /*code
  }
  else if (displayLayer == 2) /*capa 2 = ciudad que uno quiera datos meteorologicos
  {
    /*code
  }
  else if (displayLayer == 3) /*capa 3 = Datos curiosos de UH, Houston, Texas
  {
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_WHITE); 
    selection1();
    selection2();
    selection3();
  }
  else if (displayLayer == 4) capa = 4 Tasklist Miscrosoft task
  {
    /* code 
  }
  else {
    tft.fillScreen(TFT_BLACK);
  }
}
*/

/*Capa 1 <------ Datos de modulos arduino UNO <----- (Temperatura, humedad etc... del cuarto)
  void room_updateDisplay() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.print("University of Hoston"); //University of houston
    tft.print("Sensor1 Temp: ");//temperatura sensor 1
    //tft.println(megaSensor1);
    tft.println(" F");
    tft.print("Sensor2 Temp: ");//temperatura sensor 2
    //tft.println(megaSensor2);
    tft.println(" F");
    tft.print("Avg Temp: ");//temperatura promedio entre senso1 y sensor2
    //int avgtemp = (megaSensor1 + megaSenso2)/2;
    //tft.println(avgtemp);
    tft.println(" F");
    tft.print("Humidity:");//humedad habitacion
    //tft.println(megaHumedad);
    tft.println("%");
}

idea para capa 2 en selection_layer
      char c;
      String receivedMsg = "";
      while (Wire.available()) 
      {
      //c = Wire.read();
      //receivedMsg += c; //carga todo el estring de c a recievedmsg, ahora msg tiene el (ciudadtemperatura)
      }
      // Asume formato "Ciudad,Temperatura"
      int separatorIndex = receivedMsg.indexOf(',');
      if (separatorIndex != -1) 
      {
      megaCity = receivedMsg.substring(0, separatorIndex); //se guarda parte antes de la coma como string "city"
      megaTemp = receivedMsg.substring(separatorIndex + 1).toInt();//se guarda parte despues de la coma como entero "temp"
      //Ahora que tienes los nuevos valores, actualiza la pantalla
      //city_updateDisplay();
     
}*/