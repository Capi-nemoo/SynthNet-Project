
  int displayLayer = 0;
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
  long previousMillis = 0; // Almacena la última vez que actualizamos el estado de parpadeo OJO unsigned 
  const long interval = 430; // Intervalo de parpadeo en milisegundos
  int selection = 1;
  int comodin = 1;


int previousMillistemplate = 0;  // Inicializar con un valor adecuado
int tiempo_template = 0;         // Inicializar con un valor adecuado si es necesario
int selection_template = 0;      // Inicializar con un valor adecuado
int supervisor_template = 0;     // Inicializar con un valor adecuado

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


CityData cityData;    ///< Estructura para almacenar los datos climáticos de la ciudad. 

// Function declarations
void selection1();
void selection2();
void selection3();
void selection_Layer();
void blinkText(const String &text, int x, int y);
void drawUHlogo();
void drawThickH(int x, int y, uint16_t color, int thickness);
void drawThickU(int x, int y, uint16_t color, int thickness);
void drawThickUWithBorder(int x, int y, uint16_t color, int thickness);
void drawThickHWithBorder(int x, int y, uint16_t color, int thickness);
void drawThickHWithBorder2(int x, int y, uint16_t color, int thickness);
void run_Template();
void template_capa1();
void template_capa2();
void capa2prints();
void template_capa3();
void loopScreen();
void comodinloco();
void template_capa4();
void handleTemperatureRoomData();
void handleWeatherData();
void handleUHData();
void handleTasklistData();
void printReceivecitydData(const CityData& cityData);
void receiveEvent(int howMany);
