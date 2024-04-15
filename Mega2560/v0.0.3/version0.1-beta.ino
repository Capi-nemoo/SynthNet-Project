
//librerias
  #include <Arduino_BuiltIn.h>
  #include <User_Setup.h>
  #include <TFT_HX8357.h> // Hardware-specific library
  #include <Wire.h>
  TFT_HX8357 tft = TFT_HX8357(); // Invoke custom library

//variable selection layer
  int maestro_Capa = 0;
  int mega_Capa = 0;

//Variables capa 1 <--------------"TEMPERATURA HABITACION"
  /*CODE*/

// Variables capa 2 <-------------"CLIMA CIUDADES"
  String megaCity = ""; // modificar variable en un futuro....
  String direccionViento; // N, NE, E...
  String condicionesActuales; // Descripción textual

  float temperatura; //Fahrenheit
  float precipitacion; // mm
  float velocidadViento; //km/h

  int megaTemp = 0; // modificar variable en un futuro....
  int visibilidad; // metros
  int humedad; // porcentaje
  int coberturaNubosa; // porcentaje, 0 a 100%
  int indiceUV; // índice UV, generalmente un valor entero de 0 en adelante

//variables capa 3 <----------"efecto blinking"
  unsigned long previousMillis = 0; // Almacena la última vez que actualizamos el estado de parpadeo OJO unsigned 
  const long interval = 500; // Intervalo de parpadeo en milisegundos
  int selection = 1

//Variables capa 4 <--------"To-do list Microsoft"
 /*code*/

//setup!!!!!!
  void setup() 
  {
    //I2C
      Wire.begin(4); // Inicia I2C con dirección 4, ajusta según tu configuración
      Wire.onReceive(receiveEvent); // Registra el evento de recepción I2C


    //Display TFTLCD arduinomega 
      tft.begin();
      Serial.begin(115200);
      tft.setRotation(0);	
      tft.fillScreen(TFT_RED);
      //llama funciones de dibujo logo UH
        drawThickH(175, 120, TFT_WHITE, 35);
        drawThickHWithBorder2(164, 221, colorNegro, 10);
        drawThickHWithBorder(165, 120, colorNegro, 10);
        drawThickU(35, 120, TFT_WHITE, 35);
        drawThickUWithBorder(25, 120, colorNegro, 10);
      //Escribe mi nombra esquina inferior derecha
        tft.setTextSize(2); // Asume un tamaño de texto
        tft.setCursor(144, 445);
        tft.setTextColor(TFT_BLACK);    
        tft.println("Renato Ramirez"); // Imprime el nombre de la ciudad
        delay(2000);
        tft.fillScreen(TFT_BLACK);
  }
  
//Dibujo logo UH
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
  //Bordes del logo UH
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
    void drawThickHWithBorder2(int x, int y, uint16_t color, int thickness) 
    {
      // El grosor del borde; ajústalo según sea necesario.
        int borderThickness = 1; // Puedes cambiar esto según el grosor deseado del borde.
      
      // Calcula el nuevo grosor de la parte inferior como un cuarto del grosor especificado.
        int bottomThickness = max(1, thickness / 1.2);

      // Primero, dibuja el borde negro alrededor de la U.
        for (int i = -borderThickness; i < thickness + borderThickness; i++) 
        {
          // Borde derecho
          tft.drawFastVLine(x + 65 + i, y - borderThickness, 80 + 2 * borderThickness, TFT_BLACK);
        }
    }
//

//Capa 1 <------ Datos de modulos arduino UNO <----- (Temperatura, humedad etc... del cuarto)
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
//

//Capa 2 <------ Datos de API ESP-32(esclavo o maestro aun no e pensado eso) <------- (Datos climatologicos de la ciudad deseada)
  void yourCity(){
  /**/
}
//

//capa 3 <--- selector de texto y efecto de seleccion bliking <------(Base de datos creada por mi)<----(FunFacts de UH TX y HTN )
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
      //posición 
      tft.setCursor(x, y);
      tft.print(text);
    }
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
  void fnfacts_updatedisplay() //mostrar los funfacts  
  {   
  /*code*/
  }
//

//Capa 4 <------- Datos API(microsoft to-do list) ESP-32(esclavo o maestro aun no e pensado eso)

//templates (solo pruebas visuales sin variables )
  void template_capa1()
  {
    tft.setTextColor(TFT_WHITE);
    tft.print("University of Houston"); //University of houston
    tft.print("Sensor1 Temp: ");//temperatura sensor 1
    tft.println("24.0");
    tft.println(" °F");
    tft.print("Sensor2 Temp: ");//temperatura sensor 2
    tft.println("28.0");
    tft.println(" °F");
    tft.print("Avg Temp: ");//temperatura promedio entre senso1 y sensor2
    tft.println("26");
    tft.println(" °F");
    tft.print("Humidity: ");//humedad habitacion
    tft.println("80%");
    tft.println("%");

  }
  void template_capa2()
  {
    tft.print("MegaCity: Metropolis");
    tft.println();
    tft.print("Direccion Viento: NE");
    tft.println();
    tft.print("Condiciones Actuales: Parcialmente nublado");
    tft.println();
    tft.print("Temperatura: 75.5 °F");
    tft.println();
    tft.print("Precipitacion: 2.3 mm");
    tft.println();
    tft.print("Velocidad Viento: 15.5 km/h");
    tft.println();
    tft.print("MegaTemp: 76 °F");
    tft.println();
    tft.print("Visibilidad: 10000 metros");
    tft.println();
    tft.print("Humedad: 80%");
    tft.println();
    tft.print("Cobertura Nubosa: 40%");
    tft.println();
    tft.print("Indice UV: 5");
    tft.println();
  }
  void template_capa3()
  {
    unsigned long tiempo_prueba = milis()
    if (tiempo_prueba >= 7000 && selection <= 5){
      selection++;
      selection1();
      selection2();
      selection3();
    }
    if (selection >= 5)
    {
      selection = 1
    }

  }
  void template_capa4()
{
  
}
  void run_Template()
  { 
    int selection_template;
    unsigned long tiempo_template = milis()
    if (tiempo_template >= 7000 && selection_template < 5)
    {
      selection_template++;
      switch (selection_template) 
      {
        case 1:
          void template_capa1();
          break;
        case 2:
          void template_capa2();
          break;
        case 3:
          void template_capa3();
          break;
        case 3:
          void template_capa4();
          break;          
      }
    }
    else if (selection >= 5)
    {
      selection_template = 1
    }
  }
//


//funcion important
  void receiveEvent(int howMany) {
    if(howMany <= 0) return;
    tft.setTextColor(TFT_WHITE);
    int maestro_Capa = wire.read();//lee el primer byte de lo que envio el maestro y lo guarda en maestro capa /de esta manera comiensa el ciclo de if
    //mega_Capa = maestro_Capa  // iguala mega capa a maestro capa de esta manera en el ciclo loop se actualizara el template de los datos o las capas 

    if (maestro_Capa == 1)/*capa datos de temperatura del cuarto*/ {    
    /*aun no se que escribire en el arduino uno pero vamos a suponer que voy a recibir un strin de numeros y para diferenciar*/
    /*entre cual sera cada uno llegaran con una coma entre cada uno, tal que el orden esperado seria...*/
    /*ejem: 23.5,25.5,80*/
    /*en la  |    |    |*/
    /*    temp1  temp2  humidity
    el 
    primero temp1 
    segundo temp2 
    tercero humidity
    luego en la misma variable en que las guarde las guardo en float, decimales               */
    //templatedecomo se veria
    //room_updateDisplay();


    
    }
    
    else if (maestro_Capa == 2) //capa 2 = ciudad que uno quiera datos meteorologicos
    {
      
      char c;
      String receivedMsg = "";



      while (Wire.available()) 
      {
      //c = Wire.read();
      receivedMsg += c; //carga todo el estring de c a recievedmsg, ahora msg tiene el (ciudadtemperatura)
      }
      // Asume formato "Ciudad,Temperatura"
      int separatorIndex = receivedMsg.indexOf(',');
      if (separatorIndex != -1) 
      {
      megaCity = receivedMsg.substring(0, separatorIndex); //se guarda parte antes de la coma como string "city"
      megaTemp = receivedMsg.substring(separatorIndex + 1).toInt();//se guarda parte despues de la coma como entero "temp"
      //Ahora que tienes los nuevos valores, actualiza la pantalla
      //city_updateDisplay();
      }
    }

    else if (maestro_Capa == 3) //capa de datos curiosos de UH, Houston, Texas
    {
      /*primero logica para saber el valor de selection que comienza con uno enviado deauflt por el master
      
      
    una vez ya tenga la logica voy a llamar 3 FUNCIONES que se encargen de hacer titilitear o no tal que 
      */
    
    tft.setCursor(0, 0);
    tft.println("LAYER Three 3");
    tft.setTextColor(TFT_WHITE); 
    selection1();
    selection2();
    selection3();
      delay(4000);
      tft.fillScreen(TFT_BLACK);
    }

    else if (maestro_Capa == 4) //Tasklist Miscrosoft task
    {
      tft.setCursor(0, 0);
      tft.println("LAYER FOUR 4");
      /* code */
    }
  }
//

void loop() {
    receiveEvent(2);
   }
