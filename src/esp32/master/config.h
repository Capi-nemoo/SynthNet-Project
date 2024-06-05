//Librerias
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WebServer.h>
#include <WiFi.h> 
#include "htmlCity.h" 

//Wifi credentials
const char* ssid = "Renaplex";
const char* password = "1234567890";

//Variables
/**
 * @struct DatosClimaticos
 * @brief Estructura para almacenar los datos climáticos recibidos de la API.
 *
 * Almacena temperatura actual, sensación térmica, temperaturas mínima y máxima, humedad, país y condición climática.
 */
struct CityData {
    double temp;                ///< Temperatura actual.
    double feels_like;          ///< Sensación térmica.
    double temp_min;            ///< Temperatura mínima.
    double temp_max;            ///< Temperatura máxima.
    double humidity;            ///< Humedad.
    String country;             ///< País.
    String clima_condicion;     ///< Condición climática.
};

CityData cityData;      

bool isDifferent = false;
String checklastCity = "xd";
String cityName = "xd";

// Set web server port number to 80
WebServer server(90);
//definicion de data variable a manda al arduino mega

// Variable to store the HTTP request
String header;
String climaFinal = "";

int sizeCityData;


//variable de cehckcity cada 5segundos
unsigned long tiempoAnterior = 0; // Almacena la última vez que se ejecutó la acción
const unsigned long intervalo = 5000; // Intervalo deseado de 5 segundos

const int arduino1 = 0x02;  // Ejemplo de dirección del esclavo 1
const int espslave = 0x03;  // Ejemplo de dirección del esclavo 2
const int mega2560 = 0x04;  // Ejemplo de dirección del esclavo 1

//Declaracion funciones
void sendcityName();
void checkCity();
void requestDataFromSlave(int slaveAddress, int count);
void handleDataRequest();
void waitForData();
void receive_citydataSize();
void recieve_cityData();
void printCityData(const CityData& data);
void reenviar_cityData(const CityData& data);
void requestDataFromSlave(int slaveAddress, int count);
void handleDataRequest();
void waitForData();
void checkCity();


