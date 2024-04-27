
//espSlave
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <ArduinoHttpClient.h>
#include <Wire.h>
#include <WiFi.h>

int howMany;
const char* ssid = "18662675";
const char* password = "Aluna18662675*";

String firstByte = "";
//variables api weather cordenadas
double latitude;
double longitude;

struct DatosClimaticos {
    double temp;
    double feels_like;
    double temp_min;
    double temp_max;
    double humidity;
    String country;
    String clima_condicion;
};

int sizeOfData;
int length;

void setup() 
{
  Wire.begin(2);
  Serial.begin(19200); // Comienza la comunicación serial 
 // conexion a wifi seetup
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);   // Inicia la conexión a la red WiFi
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  
  receiveEvent(int howMany);
  Wire.requestEvent();

  Serial.print("Termino el setup"); 
  delay(2000);
 // recibedatosUNO();
  //length = mensaje.length();

}

void loop() {
  delay(1000);
  // El loop está vacío porque la recepción de datos se maneja por interrupción.
}

void requestEvent(const String& ciudad, DatosClimaticos& clima, byte& totalSize) {
  if (firstByte == "A")
  {  Serial.println("Se recibio una peticion de 1 byte del host");//este dira cuantos bytes hay en la variable de clima final

     Serial.print(totalSize);
     Serial.println("bytes");
     Serial.print("ahora se van a regresar al host la respuesta de su peticion con el tamano de size of");
    /* if (Wire.available == )
     {
      /* code */
     //}
     Wire.write(totalSize);
  }
}  
  // Envía primero la longitud del mensaje como un byte
 

  // Envía el mensaje caracter por caracter
  //for (int i = 0; i < length; i++) 
  //{
  //  Wire.write(mensaje[i]);
  //}
//}

//recepcion de datos del master
void receiveEvent(int howMany)
{
  if (howMany > 0) 
  {
    Serial.print("Hay algo para leer, bytes recibidos: ");
    //numero de bytes (max 32)
    Serial.println(howMany);
    if (Wire.available()) 
    {
      char firstByte = Wire.read(); // Lee el primer byte (laprimera letra)
      Serial.print("Primer byte: ");
      Serial.println(firstByte);

        //casos capas ets Str
      switch (firstByte) 
      {
        case 'A': 
        {// ciudad desde pagina web
          String ciudad;
          Serial.println("Ejecutando condicion A == ciudad");
          // Leer y almacena
          while (Wire.available()) 
          {
            char c = Wire.read();
            ciudad += c; // Agrega cada byte a la cadena
          }
          Serial.print("ciudad recibida para enviar a API: ");
          Serial.println(ciudad);
          cordenadasCiudad(ciudad);
          DatosClimaticos clima;
          climaCiudad(ciudad, clima);
          toMaster(ciudad, clima);
          break;
        }
        case 'B':
        {  // servidor web funfacts
            Serial.println("Ejecutando código para B == funfacts" );
            // Coloca aquí el código específico para cuando el primer byte es 'B'
          break;
        }
        case 'C':
        {
            Serial.println("Código predeterminado C == miscrosoft api");
          break;
        }
        default: 
        { // microsoft to do list
            Serial.println("Código predeterminado C == miscrosoft api");
            // Coloca aquí el código predeterminado
          break;  
        }
      } 
    } 
  
    while (Wire.available()) 
    {
    char c = Wire.read(); // Lee un byte como carácter
    Serial.print(c); // Imprime el carácter recibido
    }
    Serial.println(); // Nueva línea después de la recepción de todos los datos
  }
}


//obtiene datos del clima
void climaCiudad(const String& ciudad, DatosClimaticos& clima)
{
  /*
  https://api.openweathermap.org
  data/2.5/weather?lat={lat}&lon={lon}&appid={API key}*/
  Serial.print("Comenzo ahora la funcion para pedir los datos de la ciudad...");
  HTTPClient http;
  String serverPath = "https://api.openweathermap.org/data/2.5/weather?lat=";
  serverPath += latitude;
  serverPath += "&lon=";
  serverPath += longitude;
  serverPath += "&appid=3699819ba4b0f30b31a12cb5a11217b2&units=imperial";

  http.begin(serverPath.c_str());  // Comienza la conexión con la URL
  int httpCode = http.GET();  // Envía la solicitud GET y recibe el código de estado

  if (httpCode == HTTP_CODE_OK) 
  {
    String response = http.getString();  // Obtiene la respuesta
    Serial.println("Respuesta recibida:");
    Serial.println(response);

      // Parsea la respuesta JSON
     DynamicJsonDocument doc(1024); // Ajusta el tamaño según necesidad
     deserializeJson(doc, response);
    //definicion  de variables

    // Extrae la información específica de clima


    clima.temp = doc["main"]["temp"];
    clima.feels_like = doc["main"]["feels_like"];
    clima.temp_min = doc["main"]["temp_min"];
    clima.temp_max = doc["main"]["temp_max"];
    clima.humidity = doc["main"]["humidity"];
    clima.country = doc["sys"]["country"].as<String>(); 
    clima.clima_condicion = doc["weather"][0]["description"].as<String>();
    // Muestra la información extraída en el Serial
    Serial.print("Temperatura: ");
    Serial.println(clima.temp);
    Serial.print("Sensación térmica: ");
    Serial.println(clima.feels_like);
    Serial.print("Temperatura mínima: ");
    Serial.println(clima.temp_min);
    Serial.print("Temperatura máxima: ");
    Serial.println(clima.temp_max);
    Serial.print("Humedad: ");
    Serial.println(clima.humidity); 
    Serial.print("Pais");
    Serial.println(clima.country); 
    Serial.print("Condiciones climaticas");
    Serial.println(clima.clima_condicion);     

    sizeOfData = calculateTotalSize(clima); // Llama a la función y guarda el valor retornado
    Serial.print("El tamaño total en bytes de las variables es: ");
    Serial.println(sizeOfData); // Imprime el tamaño total
  }    
  
  http.end();  // Cierra la conexión
  
  delay(5000);  
}


//cuenta cuantos bytes del clima obtuvo y va a enviar a el master
int calculateTotalSize(const DatosClimaticos& clima)
{
  totalSize = 0;

  // Calcula el tamaño en bytes de las variables double
  totalSize += sizeof(clima.temp);
  totalSize += sizeof(clima.feels_like);
  totalSize += sizeof(clima.temp_min);
  totalSize += sizeof(clima.temp_max);
  totalSize += sizeof(clima.humidity);

  // Calcula el tamaño en bytes de las variables String
  totalSize += clima.country.length() + 1; // +1 for null terminator
  totalSize += clima.clima_condicion.length() + 1; // +1 for null terminator
  Serial.println(totalSize);
  // Devuelve el total calculado al lugar donde se llamó esta función
  return totalSize;
}

//obtiene coordenadas para enviar a la api del clima
void cordenadasCiudad(String ciudad)
{
  HTTPClient http;
  String serverPath = "http://api.openweathermap.org/geo/1.0/direct?q=";
  serverPath += ciudad;
  serverPath += "&limit=1&appid=3699819ba4b0f30b31a12cb5a11217b2";

  http.begin(serverPath.c_str());  // Comienza la conexión con la URL
  int httpCode = http.GET();  // Envía la solicitud GET y recibe el código de estado

  if (httpCode == HTTP_CODE_OK) 
  {
    String response = http.getString();  // Obtiene la respuesta
    Serial.println("Respuesta recibida:");
    Serial.println(response);

      // Parsea la respuesta JSON
     DynamicJsonDocument doc(1024); // Ajusta el tamaño según necesidad
     deserializeJson(doc, response);

      // Extrae la información específica, ejemplo 'lat' y 'lon'
     latitude = doc[0]["lat"]; // Asume que el resultado es un array y accede al primer elemento
     longitude = doc[0]["lon"];
      
     Serial.print("Latitud: ");
     Serial.println(latitude);
     Serial.print("Longitud: ");
     Serial.println(longitude);
     delay(3000);
     //llamada api para datos clima con coordenadas
     //funcion para obtener el clima de la api usando coordenadas 
  } 
  else 
  {
      Serial.print("Error en la solicitud HTTP: ");
      Serial.println(httpCode);
  }
  http.end();  // Cierra la conexión
  delay(5000);
}

