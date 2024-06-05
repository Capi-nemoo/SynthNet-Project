### SynthNet

```
├── docs/                   
│   ├── setup.md
│   ├── usage.md
│   └── api_reference.md
├── src/                     
│   ├── esp32/               # Código ESP32
│   │   ├── master/
│   │   │   ├── main.cpp
│   │   │   ├── config.h
│   │   │   └── ... (otros archivos específicos)
│   │   └── slave/
│   │       ├── main.cpp
│   │       ├── config.h
│   │       └── ... (otros archivos específicos)
│   ├── mega2560/            # Código Mega2560
│   │   ├── main.cpp
│   │   ├── config.h
│   │   └── ... (otros archivos específicos)
│   ├── uno/                 # Código UnoR3
│   │   ├── main.cpp
│   │   ├── config.h
│   │   └── ... (otros archivos específicos)
│   ├── wifi/                #  WiFi
│   │   ├── wifihost.cpp
│   │   ├── wifihost.h
│   │   └── ... (otros archivos específicos)
│   ├── libraries/           # Librerías
│   │   ├── libs/
│   │   │   ├── libs.h
│   │   │   ├── libs.cpp
│   │   │   └── ... (otros archivos específicos)
│   │   ├── lib2/
│   │   └── ... (más librerías)
│   └── common/              # Código compartido         microcontroladores
│       ├── utils.cpp
│       ├── utils.h
│       └── ... (otros archivos comunes)
├── tests/                   # Pruebas y test
│   ├── esp32/
│   │   ├── master/
│   │   ├── slave/
│   │   └── ...
│   ├── mega2560/
│   ├── uno/
│   ├── wifi/
│   └── common/
├── .vscode/                 
│   ├── settings.json
│   └── tasks.json
├── .gitignore              
├── CppProperties.json       # Configuración de propiedades
└── README.md                # Descripción del proyecto

Mega 2560     ESP32-S2       Arduino UNO
---------     -------        -----------
GND --------- GND ---------- GND
5V ---------- VCC (5V) ----- 5V
20 (SDA) ---- 21 (SDA) ----- A4 (SDA)
21 (SCL) ---- 22 (SCL) ----- A5 (SCL)


