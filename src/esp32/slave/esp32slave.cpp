#include <Wire.h>               ///< Librería para la comunicación I2C.
#include <WiFi.h>               ///< Librería para la conexión WiFi.
#include <HTTPClient.h>         ///< Librería para realizar solicitudes HTTP.
#include <ArduinoJson.h>        ///< Librería para el manejo de JSON.
#include <ArduinoJson.hpp>      ///< Librería para el manejo de JSON.

// Variables globales para almacenar las credenciales de la red WiFi.
int howMany;                    ///< Variable para almacenar la cantidad de bytes recibidos.
const char* ssid = "18662675";  ///< Nombre de la red WiFi.
const char* password = "Aluna18662675*"; ///< Contraseña de la red WiFi.

// Variables para almacenar la primera parte de los datos recibidos y coordenadas geográficas.
String firstBytex;     ///< Variable para almacenar el primer byte recibido.
double latitude;                ///< Variable para almacenar la latitud geográfica.
double longitude;               ///< Variable para almacenar la longitud geográfica.

bool firstCycle = true;


/**
 * @struct DatosClimaticos
 * @brief Estructura para almacenar los datos climáticos recibidos de la API.
 *
 * Almacena temperatura actual, sensación térmica, temperaturas mínima y máxima, humedad, país y condición climática.
 */
struct DatosClimaticos {
    double temp;                ///< Temperatura actual.
    double feels_like;          ///< Sensación térmica.
    double temp_min;            ///< Temperatura mínima.
    double temp_max;            ///< Temperatura máxima.
    double humidity;            ///< Humedad.
    String country;             ///< País.
    String clima_condicion;     ///< Condición climática.
};

DatosClimaticos clima;     

int sizeOfData;                 ///< Tamaño total de los datos climáticos.
int length;                     ///< Longitud de algún dato.
int totalSize;                  ///< Tamaño total de algo más.



void receiveEvent(int howMany);
void climaCiudad(const String& ciudad, DatosClimaticos& clima);
int calculateTotalSize(const DatosClimaticos& clima);
void coordenadasCiudad(String ciudad);
void requestEvent();

/**
 * @brief Configuración inicial del microcontrolador.
 *
 * Inicializa la comunicación I2C, Serial y se conecta a la red WiFi especificada.
 */
void setup() {
  Wire.onReceive(receiveEvent); // Establece la función a ejecutar al recibir datos por I2C.
  Wire.onRequest(requestEvent); // Establece la función a ejecutar al recibir una petición por I2C.
  Wire.begin(2);                // Inicia el bus I2C con dirección 2.
  Serial.begin(19200);          // Inicia la comunicación serial a 19200 baudios.

  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);   // Inicia la conexión a la red WiFi.

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("Termino el setup"); 
  delay(2000);
}

/**
 * @brief Loop principal vacío.
 *
 * La recepción de datos se maneja por interrupción, por lo que el loop principal no realiza operaciones.
 */
void loop() {
  delay(200);
}


/**
 * @brief Maneja el caso A, que corresponde a la solicitud de datos climáticos de una ciudad.
 * 
 * Esta función lee la ciudad recibida a través de I2C, solicita las coordenadas geográficas 
 * de la ciudad a una API y luego obtiene los datos climáticos de esa ciudad a través de otra API.
 * Finalmente, calcula el tamaño total de los datos climáticos en bytes.
 */
void handleCaseA() {
    Serial.println("Ejecutando condicion: A");
    Serial.println("Esta es la condicion de APIciudad");
    delay(300);
    String ciudad;
    // Leer y almacenar la ciudad recibida
    while (Wire.available()) {
        char c = Wire.read();
        ciudad += c; // Agrega cada byte a la cadena
    }
    Serial.print("Ciudad recibida para enviar a la API: ");
    Serial.println(ciudad);
    delay(200);
    coordenadasCiudad(ciudad);
    Serial.println("Termina funcion de coordenadas");
    DatosClimaticos clima;
    climaCiudad(ciudad, clima);
    Serial.println("Termina funcion de obtener datos de la API");
    
}

/**
 * @brief Maneja el caso B, que corresponde a alguna funcionalidad específica no especificada.
 * 
 * Coloca aquí el código específico para cuando el primer byte recibido es 'B'.
 */
void handleCaseB() {
    Serial.println("Ejecutando código para B == funfacts");
    // Coloca aquí el código específico para cuando el primer byte es 'B'
}

/**
 * @brief Maneja el caso C, que corresponde a alguna funcionalidad específica no especificada.
 * 
 * Coloca aquí el código específico para cuando el primer byte recibido es 'C'.
 */
void handleCaseC() {
    Serial.println("Código predeterminado C == miscrosoft api");
    // Coloca aquí el código específico para cuando el primer byte es 'C'
}

/**
 * @brief Maneja el caso predeterminado, que corresponde a alguna funcionalidad no especificada.
 * 
 * Coloca aquí el código predeterminado que se ejecutará cuando el primer byte recibido no coincida con 'A', 'B' o 'C'.
 */
void handleDefaultCase() {
    Serial.println("Código predeterminado == miscrosoft api");
    // Coloca aquí el código predeterminado
}

/**
 * @brief Función para manejar eventos de solicitud I2C.
 *
 * Responde con datos sobre el clima dependiendo de la solicitud recibida.
 */
/*void requestEvent() {
  Serial.println("se recibio una peticion!");
  Serial.println(firstBytex);
  if (firstBytex == "A")
  {
    Serial.println("Esta petición es para datos del caso A (Datos climáticos de ciudades)");
    totalSize = calculateTotalSize(clima);  // Asume que esta función está definida correctamente
    Serial.print("El tamaño total en bytes de las variables es: ");
    Serial.println(totalSize);
    Serial.println("Ahora se va a regresar al host la respuesta que será igual a la cantidad de bytes que tendrá que volver a solicitarme");
    Wire.write(totalSize);  // Envía el tamaño como un byte
    
  }
}
*/

void requestEvent() {
    Serial.println("se recibio una peticion!");
    Serial.println(firstBytex);
    if (firstCycle) {
        Serial.println("ciclo para enviar cantidad de datos");
        Serial.println("Esta petición es para.....");
        if (firstBytex == "A")
        {
            Serial.println("datos del caso A (Datos climáticos de ciudades)");
            totalSize = calculateTotalSize(clima);  // Asume que esta función está definida correctamente
            Serial.print("El tamaño total en bytes de las variables es: ");
            Serial.println(totalSize);
            Serial.println("Ahora se va a regresar al host la respuesta que será igual a la cantidad de bytes que tendrá que volver a solicitarme");
            Wire.write(totalSize);  // Envía el tamaño como un byte
            delay(1000);
        }
        firstCycle = false;  // Cambia el ciclo para la próxima petición
    } else {
        Serial.println("ciclo para enviar valores de datos");
        if (firstBytex == "A")
        {
            Serial.println("datos del caso A (Datos climáticos de ciudades)");
            totalSize = calculateTotalSize(clima);  // Asume que esta función está definida correctamente
            Serial.print("El tamaño total en bytes de las variables es: ");
            Serial.println(totalSize);
            Serial.println("Ahora se va a regresar al host la respuesta que será igual a la cantidad de bytes que tendrá que volver a solicitarme");
            Wire.write(totalSize);  // Envía el tamaño como un byte
            
        }
        firstCycle = true;  // Reestablece para el próximo ciclo
    }
    }

/**
 * @brief Se ejecuta cuando el ESP recibe datos via I2C.
 * 
 * Esta función imprime el primer byte para identificar el tipo de solicitud y procesa los datos adicionales según corresponda.
 * @param howMany Cantidad de bytes que se espera recibir.
 */
void receiveEvent(int howMany)
{
    if (howMany > 0) 
    {
        Serial.println("Primeros bites para saber el caso");
        Serial.println("A=APIciudad");
        Serial.println("B=Fnfacts");
        Serial.println("C=Microsofttodolist");
        Serial.println("Bytes recibidos: ");
        Serial.println(howMany);

        if (Wire.available()) 
        {
            char firstByte = Wire.read(); // Lee el primer byte (la primera letra).
            firstBytex = firstByte;
            Serial.print("Primer byte: ");
            Serial.println(firstByte);

            switch (firstByte) 
            {
                case 'A': 
                    handleCaseA(); // Maneja el caso A.
                    break;
                case 'B':
                    handleCaseB(); // Maneja el caso B.
                    break;
                case 'C':
                    handleCaseC(); // Maneja el caso C.
                    break;
                default: 
                    handleDefaultCase(); // Maneja cualquier otro caso.
                    break;
            } 
        } 
  
        while (Wire.available()) 
        {
            char c = Wire.read(); // Lee un byte como carácter.
            Serial.print(c); // Imprime el carácter recibido.
        }
        Serial.println(); // Nueva línea después de la recepción de todos los datos.
    }
}

/**
 * @brief Solicita y procesa los datos climáticos de una ciudad específica.
 * 
 * Esta función configura la conexión HTTP y solicita los datos climáticos a la API. Luego parsea la respuesta y almacena los datos en la estructura `DatosClimaticos`.
 * @param ciudad Nombre de la ciudad para la que se solicitan los datos climáticos.
 * @param clima Estructura donde se almacenarán los datos climáticos.
 */
void climaCiudad(const String& ciudad, DatosClimaticos& clima)
{
    Serial.print("Comenzando la función para pedir los datos de la ciudad a la API...");
    HTTPClient http;
    String serverPath = "https://api.openweathermap.org/data/2.5/weather?lat=";
    serverPath += latitude;
    serverPath += "&lon=";
    serverPath += longitude;
    serverPath += "&appid=3699819ba4b0f30b31a12cb5a11217b2&units=imperial";

    http.begin(serverPath.c_str());  // Comienza la conexión con la URL.
    int httpCode = http.GET();  // Realiza la solicitud GET.

    if (httpCode == HTTP_CODE_OK) 
    {
        String response = http.getString();  // Obtiene la respuesta.
        Serial.println("Respuesta recibida:");
        Serial.println(response);

        DynamicJsonDocument doc(1024); // Ajusta el tamaño según necesidad.
        deserializeJson(doc, response); // Parsea la respuesta JSON.

        // Extrae la información específica declima del JSON:

        clima.temp = doc["main"]["temp"];
        clima.feels_like = doc["main"]["feels_like"];
        clima.temp_min = doc["main"]["temp_min"];
        clima.temp_max = doc["main"]["temp_max"];
        clima.humidity = doc["main"]["humidity"];
        clima.country = doc["sys"]["country"].as<String>(); 
        clima.clima_condicion = doc["weather"][0]["description"].as<String>();

        Serial.println("Datos climáticos obtenidos:");
        Serial.print("País: ");
        Serial.println(clima.country);
        Serial.print("Condición climática: ");
        Serial.println(clima.clima_condicion);
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
    }    
  
    http.end();  // Termina la conexión HTTP.
    Serial.println("termino la funcion API");
    delay(1000);  // Espera 5 segundos antes de continuar.
}

/**
 * @brief Calculates the total size of the climate data in bytes to send to the master.
 * 
 * This function calculates the size in bytes of each member of the DatosClimaticos structure.
 * It also prints out the byte size of each member to the Serial console.
 * 
 * @param clima A constant reference to the DatosClimaticos structure containing climate data.
 * @return The total size in bytes of the climate data.
 */
int calculateTotalSize(const DatosClimaticos& clima)
{
    Serial.println("Ahora se esta ejecutando la funcion para calcular cuantos bytes pesa la respuesta de la api filtrada");
    Serial.print("Tamaño inicial: ");
    Serial.println(totalSize);
    totalSize += sizeof(clima.temp);
    Serial.print("Después de temperatura: ");
    Serial.println(totalSize);

    int oldTotalSize = totalSize;  // Usando oldTotalSize para mantener el código limpio
    totalSize += sizeof(clima.feels_like);
    Serial.print("Después de sensación térmica: ");
    Serial.println(totalSize);

    oldTotalSize = totalSize;
    totalSize += sizeof(clima.temp_min);
    Serial.print("Después de temperatura mínima: ");
    Serial.println(totalSize);

    oldTotalSize = totalSize;
    totalSize += sizeof(clima.temp_max);
    Serial.print("Después de temperatura máxima: ");
    Serial.println(totalSize);

    oldTotalSize = totalSize;
    totalSize += sizeof(clima.humidity);
    Serial.print("Después de humedad: ");
    Serial.println(totalSize);

    oldTotalSize = totalSize;
    totalSize += clima.country.length() + 1;
    Serial.print("Después de país: ");
    Serial.println(totalSize);

    oldTotalSize = totalSize;
    totalSize += clima.clima_condicion.length() + 1;
    Serial.print("Después de condición climática: ");
    Serial.println(totalSize);

    return totalSize;
}

/**
 * @brief Obtains geographic coordinates for a city to use in the climate API.
 * 
 * This function sends a GET request to the OpenWeatherMap API to obtain the latitude
 * and longitude for a specified city. It prints the API response and extracts the 
 * latitude and longitude from the JSON response.
 * 
 * @param ciudad The city for which to obtain geographic coordinates.
 */
void coordenadasCiudad(String ciudad)
{
    Serial.println("Inicia funcion para obtener coordenadas...");
    HTTPClient http;
    String serverPath = "http://api.openweathermap.org/geo/1.0/direct?q=";
    serverPath += ciudad;
    serverPath += "&limit=1&appid=3699819ba4b0f30b31a12cb5a11217b2";
    Serial.print("punto1");
    http.begin(serverPath.c_str());  // Comienza la conexión con la URL
    int httpCode = http.GET();  // Envía la solicitud GET y recibe el código de estado
    Serial.println("Se verifica que que no hay un error");
    Serial.println(httpCode);
    Serial.print("punto2");
    if (httpCode == HTTP_CODE_OK) 
    {
        String response = http.getString();  // Obtiene la respuesta
        Serial.println("Respuesta de la api recibida:");
        Serial.println(response);

        DynamicJsonDocument doc(1024); // Ajusta el tamaño según necesidad
        deserializeJson(doc, response);
        latitude = doc[0]["lat"]; // Extracts the latitude
        longitude = doc[0]["lon"]; // Extracts the longitude
        Serial.println("informacion de coordenadas filtrada:");
        Serial.print("Latitud: ");
        Serial.println(latitude);
        Serial.print("Longitud: ");
        Serial.println(longitude);
        delay(3000);
    } 
    else 
    {
        Serial.print("Error en la solicitud HTTP: ");
        Serial.println(httpCode);
    }
    Serial.print("punto3");
    Serial.println("cierra conexion y hace delay");
    http.end();  // Cierra la conexión
}
