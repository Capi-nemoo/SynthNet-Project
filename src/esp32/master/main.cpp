#include <config.h>
#include <html.h>

void setup(){
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

void loop() {
  server.handleClient();  // Mueve esto fuera de la condición
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    Serial.println("Pasaron 5s");
    checkCity();
  }
}

void sendcityName() {
  //primera variable es la que decide el case del espAPI
  String toEsp = "A" + cityName;
  //manda los datos del string al espAPI
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

void receive_citydataSize() {
  Wire.write(10); //my requestform the slave personalizado
    //Wire.requestFrom(2, 245); // Solicita 1 byte del esclavo con dirección 2
    Serial.println("Se envía petición al esclavo para recibir 1 byte");
    if (Wire.available()) {
        int sizeCityData = Wire.read(); // Lee el byte recibido
        Serial.print("numero de Bytes recibido del esclavo: ");
        Serial.println(sizeCityData); // Imprime el valor entero
        Serial.println("Se reinicia la interfaz I2C");
        Serial.print("termina la funcion de recibir el tamaño de la estructura del esclavo:");
        recieve_cityData();
    } else {
        Serial.println("No se recibieron datos del esclavo.");
    }
}

void recieve_cityData(){
  Wire.requestFrom(2, sizeCityData); // Solicita la estructura completa.
  Serial.print(sizeCityData);
  Serial.println("Solicitando datos de la estructura al esclavo...");

  // Espera hasta que todos los datos estén disponibles.
  while(Wire.available() < sizeCityData) {
    delay(100);
    Serial.println("Esperando datos completos de la estructura...");
  }

  // Lee los datos directamente en la estructura.
  uint8_t *dataPtr = (uint8_t *)&cityData;
  for (int i = 0; i < sizeCityData; i++) {
    if (Wire.available()) {
      dataPtr[i] = Wire.read();
    }
  }
  // Aquí puedes verificar la estructura recibida.
  printCityData(cityData);
  // Reenviar los datos al mega2560
  //reenviar_cityData(cityData);


}

void printCityData(const CityData& data) {
  Serial.println("Received weather data:");
  Serial.print("Current temperature: ");
  Serial.println(data.temp, 2);  // Display with two decimal places.
  
  Serial.print("Feels like temperature: ");
  Serial.println(data.feels_like, 2);
  
  Serial.print("Minimum temperature: ");
  Serial.println(data.temp_min, 2);
  
  Serial.print("Maximum temperature: ");
  Serial.println(data.temp_max, 2);
  
  Serial.print("Humidity: ");
  Serial.println(data.humidity, 2);
  
  Serial.print("Country: ");
  Serial.println(data.country);
  
  Serial.print("Weather condition: ");
  Serial.println(data.clima_condicion);
}

void reenviar_cityData(const CityData& data) {
  // Reenviar los datos al mega2560 con dirección 4
  ///sendCasetomega(); //manda el case al megalocoooo

  Wire.beginTransmission(4); // Inicia comunicación con esclavo en dirección 4
  Wire.write(1); // Primero envía el byte de la capa

  // Serializar y enviar cada campo de la estructura CityData
  Wire.write((byte*)&data.temp, sizeof(data.temp));         // Envia temperatura actual
  Wire.write((byte*)&data.feels_like, sizeof(data.feels_like)); // Envia sensación térmica
  Wire.write((byte*)&data.temp_min, sizeof(data.temp_min));     // Envia temperatura mínima
  Wire.write((byte*)&data.temp_max, sizeof(data.temp_max));     // Envia temperatura máxima
  Wire.write((byte*)&data.humidity, sizeof(data.humidity));     // Envia humedad

  // Convertir las cadenas String a c-string para enviar
  const char* country = data.country.c_str();
  Wire.write((const uint8_t*)country, data.country.length() + 1);  // Envia país

  const char* clima = data.clima_condicion.c_str();
  Wire.write((const uint8_t*)clima, data.clima_condicion.length() + 1); // Envia condición climática

  byte error = Wire.endTransmission(); // Finaliza la transmisión y verifica errores

  if (error == 0) {
    Serial.println("Datos enviados exitosamente.");
  } else {
    Serial.print("Error en transmisión: ");
    Serial.println(error);
  }
}

void requestDataFromSlave(int slaveAddress, int count) { // Función para leer la cantidad de bytes a recibir y realizar el request
    if (count > 0) {
        Wire.requestFrom(slaveAddress, count);
        while (Wire.available()) {
            char c = Wire.read();
            //meter donde se guarda el dato
            Serial.print(c);
        }
        Serial.println();
    } else {
        Serial.println("Cantidad de datos solicitada no válida.");
    }
}

void handleDataRequest() {// Función que maneja la lógica de interpretación del primer byte y los bytes de tamaño
  
    if (Wire.available() > 0) {  // Asegurarse de que hay al menos 3 bytes disponibles
        byte identifier = Wire.read();  // Primer byte: identificador del tipo y esclavo
        int count = Wire.read() | (Wire.read() << 8);  // Siguientes dos bytes: tamaño de los datos
        Serial.print("Identificador: ");
        Serial.print(identifier);
        Serial.print(", bytes a leer: ");
        Serial.println(count);

        // Decidir cuál esclavo es según el identificador
        switch (identifier) {
            case 1:
                requestDataFromSlave(arduino1, count);
                break;
            case 2:
                requestDataFromSlave(espslave, count);
                break;
            case 3:
                requestDataFromSlave(espslave, count);
                break;
            case 4:
                requestDataFromSlave(mega2560, count);
                break;  
            default:
                Serial.println("Identificador no reconocido.");
                break;
        }
    } else {
        waitForData();
    }
}

void waitForData() {
    Serial.println("Esperando a recibir un byte...");
    while (Wire.available() == 0) { // Mientras no haya bytes disponibles
        delay(500);
        Serial.print("."); // Imprime un punto cada 500 ms para indicar la espera
    }
    Serial.println("\nByte recibido!");
}

void checkCity() {

  if (cityName == checklastCity) {
    isDifferent = false;
  }

  if (cityName != checklastCity) {
    isDifferent = true;
    checklastCity = cityName;
   
  }


  if (isDifferent == true) {
    Serial.println("se ejecuta funcion para enviar el NOMBRE de la ciudad");
    sendcityName();
    Serial.println("ya termino de enviar el nombre de la ciudad");
    Serial.println("ahora comienza funcion para pedir cantidad de bytes y luego solicitar esos bytes");
    delay(10000);
    receive_citydataSize();
    delay(1000);
  }
}

