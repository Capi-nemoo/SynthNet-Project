
#include <WebServer.h>
#include <Wire.h>
// Load Wi-Fi library
#include <WiFi.h>
#include "htmlCity.h"  //CAMBIAR A .H ARCHI OJO IMPOPRTANTEEE
// Replace with your network credentials
const char* ssid = "18662675";
const char* password = "Aluna18662675*";
bool isDifferent = false;
String checklastCity = "xd";
String cityName = "xd";
// Set web server port number to 80
WebServer server(90);
//definicion de data variable a manda al arduino mega

// Variable to store the HTTP request
String header;
//sada,scl
#define SDA_PIN 18  // Define el número de pin para SDA
#define SCL_PIN 19  // Define el número de pin para SCL
void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(115200);
  Serial.println("\nWiFi connected.");
    Serial.println("\nWiFi connected.");
    delay(2000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.println("IP address: " + WiFi.localIP().toString());
  
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

void i2cCity() {
  //Tiene que mandar los datos del string al espAPI
  Serial.println("esdsdfsssssdffsdfdsfxitos");
  Wire.beginTransmission(2); //esclavo con dirección 2
  Wire.write(cityName.c_str()); // Convierte a string
  byte error = Wire.endTransmission(); // Finaliza la transmisión y checka
  if (error == 0) {
    Serial.println("exitos");
  } else {
    Serial.print("Error");
    Serial.println(error);
  }
}

void i2cUNO() {
  //tiene que recibir primero los datos del arduino UNO para mandarlos al mega2560
}
void i2cityReceive() {
  //Tiene que recibir lso datos del espAPI y mandarlos al mega
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
    i2cCity();
    Serial.println("funciono! Rena sos un crack, esto es que fue diferente , se ejecuta wire");
    delay(2000);
  }
  if (isDifferent == false) {
    Serial.println("funciono!");
    delay(500);
  }
}

void loop() {
  //Leer ciudad del website y excribir funcion wire de envio al ESP API OJOO
  //ira dentro de otro funcion dentro de otra funcion el wire para esp               ^
  server.handleClient();  //<--|
  checkCity();            //  <------_/

  //Obtener datos arduino UNO
  //tengo qu usar el truco de comodinloco que invente el otro diA
}

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