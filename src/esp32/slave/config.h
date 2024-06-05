//librerias
#include <Arduino.h>
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
   
int sizeOfData;                 ///< Tamaño total de los datos climáticos.
int length;                     ///< Longitud de algún dato.
int totalSize;                  ///< Tamaño total de algo más.

DatosClimaticos clima;

//declaracion funciones
void receiveEvent(int howMany);
void climaCiudad(const String& ciudad, DatosClimaticos& clima);
int calculateTotalSize(const DatosClimaticos& clima);
void coordenadasCiudad(String ciudad);
void requestEvent();

