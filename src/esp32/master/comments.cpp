
/*
void i2cUNO();
void i2cAPItodolist();
void readbuffer();
void sendCasetomega();
void processReceivedByte(byte receivedByte);

*/
//void readbuffer();
//void sendCasetomega();
//void i2cUNO();
//void i2cAPItodolist();
//void bytesOf();
//void i2cUNO();
//void i2cAPItodolist();


/*
void i2cUNO() {
    //tiene que recibir primero los datos del arduino UNO para mandarlos al mega2560
  Wire.requestFrom(3, 10);
  Serial.println("Se envia peticion al ArduinoUNO de 10bytes");
  String datosUno;
  char c = Wire.read();//se lee el primer byte
  datosUno += c; // Agrega cada byte a la cadena
  Serial.print("comienza ahora a reenviar los datos al mega2560");
  Serial.print(datosUno);
  Wire.beginTransmission(4); //esclavo con dirección 2
  
  for (int i = 0; i < 10; i++) {
      Wire.write(datosUno[i]);
  }
}
*/
/*
void i2cAPItodolist() {
  //recibir los datos del espAPI y mandarlos al MEGA250
}
*/

/*
void readbuffer() {
  //leer el buffer de el arduino UNO modulos fisicos
  //leer el buffer de el ESP(esclavo) de la API de microsoft
  //leer el buffer de el ESP(slave) de la API de openweather

} 
*/
/*
void sendCasetomega() {
  // Send a byte to slave(4)
  Wire.beginTransmission(4); // Start communication with slave at address 4
  Wire.write(1); // Send a byte with value 1
  byte error = Wire.endTransmission(); // End transmission and check for errors

  if (error == 0) {
    Serial.println("Byte sent successfully.");
  } else {
    Serial.print("Transmission error: ");
    Serial.println(error);
  }
}
*/

/*
// Función para procesar el byte recibido
void processReceivedByte(byte receivedByte) {

    // Checar el valor del byte con cada "if"
    if (receivedByte == 1) {
        Serial.println("......= 1 (transmisión del Arduino UNO / temperatura de los módulos)");
        // Código de transmisión del Arduino UNO

    } 
    else if (receivedByte == 2) {
        Serial.println("......= 2 (transmisión del ESP (esclavo) - Datos clima del API)");
        // Código de transmisión del ESP (esclavo)
  
    }
    else if (receivedByte == 3) {
        Serial.println("......= 3 (transmisión de este mismo ESP (maestro) al Mega 2560)");
        // Código de transmisión de este mismo ESP (maestro)

    } 
    else if (receivedByte == 4) {
        Serial.println("......= 4 (transmisión del ESP32 (esclavo) - Datos de la API de Microsoft)");
        // Código de transmisión del ESP32 (esclavo)

    } else {
        Serial.println("Ninguna opción fue seleccionada. Resetear el código o manejar como error.");
    }
    Serial.print("El tamaño del mensaje es de : ");
    Serial.println(" bytes");
}
*/