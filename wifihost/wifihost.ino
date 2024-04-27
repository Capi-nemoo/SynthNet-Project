//master
#include <WebServer.h>
#include <Wire.h>
#include <WiFi.h> // Load Wi-Fi library
#include "htmlCity.h"  //CAMBIAR A .H ARCHI OJO IMPOPRTANTEEE

//Network credentials
const char* ssid = "Renaplex";
const char* password = "12345678";

//variable de cehckcity cada 5segundos
unsigned long tiempoAnterior = 0; // Almacena la última vez que se ejecutó la acción
const unsigned long intervalo = 5000; // Intervalo deseado de 5 segundos

bool isDifferent = false;
String checklastCity = "xd";
String cityName = "xd";
// Set web server port number to 80
WebServer server(90);
//definicion de data variable a manda al arduino mega

// Variable to store the HTTP request
String header;
void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Wire.begin();
  //hotspot
  Serial.print("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  //website
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", HTML_PAGE);
  });
  // datos del formulario
  server.on("/submit", HTTP_GET, []() {
    cityName = server.arg("cityName");  // Obtener el valor del parámetro cityName
    Serial.println("Received city name: " + cityName);
    //checkCity = cityName;
    server.send(200, "text/plain", "Received city name: " + cityName);
  });
  server.begin();

}


void sendcityName() {
  //primera variable es la que decide el case en el master
  String toEsp = "A" + cityName;
  //Tiene que mandar los datos del string al espAPI
  Serial.println("se va a enviar la info");
  Wire.beginTransmission(2); //esclavo con dirección 2
  Wire.write(toEsp.c_str()); // Convierte a string
  byte error = Wire.endTransmission(); // Finaliza la transmisión y checka
  if (error == 0) {
    Serial.println("exitosamente se envio");

  } 
  else 
  {
    Serial.print("Error");
    Serial.println(error);
  }
}

void i2cityReceive() {
  //Tiene que recibir lso datos del espAPI y mandarlos al mega
  // Maestro solicitando el tamaño del mensaje
  Serial.println("Se ejecuta hasta i2city");
  Wire.requestFrom(2, 1); // Solicitar 1 byte que indica la longitud del mensaje
  int length = 0;
  if (Wire.available()) {
      length = Wire.read(); // Leer la longitud del mensaje
      Serial.println("el tamano del mensaje es de : ");
      Serial.print(length);
      Serial.print(" bytes");
  }
  
 String climaFinal = "";
  // Maestro solicitando el mensaje basado en la longitud recibida
  Wire.requestFrom(2, length);
  while (Wire.available()) {
      char c = Wire.read();
      climaFinal += c;
      // Procesar cada byte del mensaje
}
  Serial.print(climaFinal);
}

void i2cUNO() {
    //tiene que recibir primero los datos del arduino UNO para mandarlos al mega2560
  Wire.requestFrom(3, 10);
  Serial.println("Se envia peticion al ArduinoUNO de 10bytes")
  
  char c = Wire.read();//se lee el primer byte
  datosUno += c; // Agrega cada byte a la cadena
  Serial.print("comienza ahora a reenviar los datos al mega2560")
  Serial.print(datosUno)
  Wire.beginTransmission(4); //esclavo con dirección 2
  Wire.write(datosUno)


}


void i2cAPItodolist() {
  //recibir los datos del espAPI y mandarlos al MEGA250
}

void checkCity() {

  if (cityName == checklastCity) {
    isDifferent = false;
  }

  if (cityName != checklastCity) {
    isDifferent = true;
    checklastCity = cityName;
    delay(4000);
  }


  if (isDifferent == true) {
    sendcityName
  ();
    Serial.println("se ejecuta funcion I2c");
    delay(2000);
  }
}


void loop() {
  server.handleClient();  // Mueve esto fuera de la condición
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    Serial.println("Pasaron 5s");
    checkCity();
  }
}


              //  <------_/

  //Obtener datos arduino UNO
  //tengo qu usar el truco de comodinloco que invente el otro diA


//codigo examples
//void loop(){


/*WiFiClient client = server.available();   // Listen for incoming clients
  int estado = 0;
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      estado = 0;
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("deberia estar en 1");
              digitalWrite(output27, HIGH);
              output26State = "on";
              estado = 1;
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "deberia estar en 2";
              estado = 2;
              digitalWrite(output27, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("deberia estar en 3");
              digitalWrite(output27, HIGH);
              estado = 3;
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("deberia estar en 4");
              output27State = 4;
              estado = 4;
              digitalWrite(output27, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ANA TIENE EL CULO GRANDE Y LAS TETAS GRANDES <3</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }*/
//}