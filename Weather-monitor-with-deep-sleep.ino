/*-------------------------------- LIBRARIES -------------------------------- */
#include <ESP8266WiFi.h>
#include "DHT.h"                // Libreria para manejar el sensor de humedad y temperatura
#include <PubSubClient.h>       // Libreria para manejar comunicación MQTT
#include <Wire.h>               // Libreria para usar el I2C.
#include <Adafruit_ADS1015.h>   // Libreria para el modulo de ampliación de pines analogicos.
#include <Ticker.h>             // https://blog.creations.de/?p=149
Ticker ticker;                  // https://blog.creations.de/?p=149
#include <Adafruit_Sensor.h>    // Libreria para manejar el sensor TSL2561 (requiere I2C - Wire.h)
#include <Adafruit_TSL2561_U.h> // Libreria para manejar el sensor TSL2561 (requiere I2C - Wire.h)


/*-------------------------------- DHTT option to use -------------------------------- */
// Descomentar el que se necesite utilizar.
//#define DHTTYPE DHT11       // DHT 11
//#define DHTTYPE DHT21       // DHT 21 (AM2301)
#define DHTTYPE DHT22         // DHT 22  (AM2302), AM2321


/*-------------------------------- MQTT SERVER CONFIGURATION -------------------------------- */
const char* mqtt_server       = "1.2.3.4"; // Servidor donde esta el MQTT server (puede ser un endpoint de aws (un NLB)
const int   mqtt_port         =  1883;                    // Puerto del MQTT
const char *mqtt_user         = "admin";                  // USER
const char *mqtt_pass         = "admin";                  // PASS
const char *mqtt_client_name  = "HomeWeatherSystem";      // Nombre del cliente (Client connections cant have the same connection name)
const char *mqtt_topic        = "IoT";                    // El nombre del topic donde voy a insertar la data
const char *admin_topic       = "admin";                  // El nombre del topico



// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient HomeWeatherSystem;
PubSubClient client(HomeWeatherSystem); // Cuidado, esto no soporta guiones medios

/* -------------------------------- Adafruit_ADS1115 DEFINITIONS --------------------------------- */
Adafruit_ADS1115 ads;                   // Inicializo el sensor ADS1115 (ampliador analogico)


/* ------ SOIL CONFIG (Capacitive soil moisture sensor v1.2 --------------------------------- */
const int AirValue      = 14750;        // Valor cuando está fuera del agua y seco
const int WaterValue    = 7430;         // Valor cuando está dentro del agua
int soilMoistureValue   = 0;            // Defino el valor en cero
int soilmoisturepercent = 0;            // Defino el valor en cero


/* -------------------------------- DHT22 DEFINITIONS --------------------------------- */
uint8_t DHTPin    = 12;           // Defino el pin del DHT (ESP8266 2=D4 12=D6 )
DHT dht(DHTPin, DHTTYPE);         // Inicializo el sensor DHT
float Temperature;                // Defino el valor Temperatura como float (por que viene en numero con coma)
float Humidity;                   // Defino el valor Humedad como float     (por que viene en numero con coma)

/* -------------------------------- WIFI CONFIG --------------------------------- */
const char* ssid       = "mi-wifi-ssid";           // your wifi name
const char* password   = "mi-wifi-pass";           // your wifi pass

/* -------------------------------- DEEP-SLEEP CONFIG --------------------------------- */
#define durationSleep  30 // 1 second = 1,000,000 microseconds (si uso 60 se apaga el powerbank)
#define NB_TRYWIFI     10 // number of try to connect WiFi

void tick()
{
  int state = digitalRead(BUILTIN_LED);     // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);        // set pin to the opposite state
}




/*-------------------------------- TSL2561 config-------------------------------- */
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);


void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}



void configureSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);       /* fast but low resolution */
   tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);       /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);     /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */  
  /*
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
  */
}





/* -------------------------------- GENERAL SETUP --------------------------------- */
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  ticker.attach(0.5, tick);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

/* -------------------------------- WIFI CONNECTING --------------------------------- */
  int _try = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
    _try++;
    if ( _try >= NB_TRYWIFI ) {
        Serial.println("Impossible to connect WiFi network, go to deep sleep, bye...");
        ESP.deepSleep(durationSleep * 1000000);
    }
  }
  Serial.print("Connected to "); Serial.print(ssid); Serial.print(" Wifi network");
  Serial.print ( "Got IP address: " );
  Serial.println ( WiFi.localIP() );
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("----------------");   // un separador :)



/* -------------------------------- DHT22 SETUP --------------------------------- */
  pinMode(DHTPin, INPUT);                       // Defino el pin del DHT en modo input para leer los datos que genera el mismo.
  dht.begin();                                  // Inicializo el DHT
  Temperature = dht.readTemperature();          // Leo el sensor y lo guardo en una variable llamada Temperature
  Humidity    = dht.readHumidity();             // Leo el sensor y lo guardo en una variable llamada Humedad




/* ----- ADS (expansor analogico) & SOIL/LDR Sensors CONFIG --------------------------------- */

  ads.begin();                                  // Inicializo el ads (expansor analogico)

  short adc0 = ads.readADC_SingleEnded(0);      // (SOIL) Leo del expansor analogico la posicion 0 para obtener datos del A0 del ADS1115SOIL que tiene conectado otro sensor 
  short adc1 = ads.readADC_SingleEnded(1);      // (LDR)  Leo del expansor analogico la posicion 0 para obtener datos del A1 del ADS1115SOIL que tiene conectado otro sensor 
  short adc2 = ads.readADC_SingleEnded(2);      // (Water Sensor)
  
  soilmoisturepercent = map(adc0, AirValue, WaterValue, 0, 100); // Aca mapeo el dato del sendor de tierra (SOIL) junto con los valores maximos y minimos que declare al principio

  if(soilmoisturepercent > 100){
      //Serial.println("100 %");
      soilmoisturepercent = 100;    // Si el valor que recibo es mas de 100, le asigno 100 por que no tiene sentido tener mas de 100%
  }
  else if(soilmoisturepercent <0){
      //Serial.println("0 %");
      soilmoisturepercent = 0;      // Si el valor que recibo es menor de 0, le asigno 0 por que no tiene sentido tener menos de 0%
    }
  else if(soilmoisturepercent >0 && soilmoisturepercent < 100){
      //Serial.print(soilmoisturepercent);
     // Serial.println("%");
    }





/*-------------------------------- TSL2561 -------------------------------- */
  /* Initialise the sensor */
  //use tsl.begin() to default to Wire, 
  //tsl.begin(&Wire2) directs api to use Wire2, etc.
  if(!tsl.begin())
  {
    // There was a problem detecting the TSL2561 ... check your connections
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  
  //displaySensorDetails();         // Display some basic information on this sensor
  configureSensor();                // Setup the sensor gain and integration time
  // We're ready to go!
  //Serial.println(".");
 
  sensors_event_t event;            // Get a new sensor event
  tsl.getEvent(&event);
 
  // Display the results (light is measured in lux)
  /*
  if (event.light)  {
    Serial.print("Lux: "); Serial.println(event.light); 
  }
  else {
    Serial.println("Sensor overload"); //If event.light = 0 lux the sensor is probably saturated and no reliable data could be generated!
  }
  delay(250);
  */

    
/* -------------------------------- MQTT CONFIG --------------------------------- */
  client.setServer(mqtt_server, mqtt_port);                             // Seteo los parametros de mi MQTT server
  client.setCallback(MQTTcallback);                                     // Seteo el calback
  client.subscribe("IoT");                                              // Me subscribo a la cola de mi MQTT
  
  while (!client.connected()) {                                         // Genero un loop para intentar conectarme.
    Serial.println("Connecting to MQTT...");                            // Mando un mensje que estoy intentando conectarme.
    if (client.connect(mqtt_client_name, mqtt_user, mqtt_pass )) {      // Paso por parametro los datos que necesito para conectarme.
      Serial.println("connected");                                      // Imprimo que estoy conectado.
    } else {                                                            // Si no me puedo conectar hago lo siguiente
      Serial.print("Can not connect to MQTT, I will retry  ");          // Imprimo un mensaje que no me pude conectar por alguna razon (en general es por que no llego al server)
      //Serial.println(client.state());                                 // Si recibo el estado 5 es por falta de coincidencia en la configuración
      Serial.print("I'm going to sleep for "); Serial.print(durationSleep); Serial.println(" seconds");
      ESP.deepSleep(durationSleep * 1000000);                           // Lo pongo en reposo
    }
  }
 
  client.connect(mqtt_client_name, mqtt_user, mqtt_pass, mqtt_topic, 0, 0, "closed");  // Aca me conecto al MQTT server remoto.
  
  // Publico los datos al MQTT server en formato String (espero 500ms para no matar el mqtt server)
  client.publish("Temperature", String(Temperature).c_str(), false);    // uso false para que el mensaje no persista en el MQTT server una vez consumido
  delay(500);                                                           // espero medio seg para no sobrecargar el MQTT server
  client.publish("Humidity", String(Humidity).c_str(), false);          // uso false para que el mensaje no persista en el MQTT server una vez consumido
  delay(500);                                                           // espero medio seg para no sobrecargar el MQTT server
  client.publish("Soil", String(soilmoisturepercent).c_str(), false);   // uso false para que el mensaje no persista en el MQTT server una vez consumido
  delay(500);                                                           // espero medio seg para no sobrecargar el MQTT server
  client.publish("Ldr", String(adc1).c_str(), false);                   // uso false para que el mensaje no persista en el MQTT server una vez consumido
  delay(500);
  client.publish("Lux", String(event.light).c_str(), false);
  delay(500);
  client.publish("Water", String(adc2).c_str(), false);  
  client.disconnect();                                                  // me desconecto


  // Imprimo todos los datos para visualizarlos en el serial monitor del arduino
  Serial.print("Temp: "); Serial.println(Temperature);
  Serial.print("Hum: ");  Serial.println(Humidity);
  Serial.print("Soil: "); Serial.println(soilmoisturepercent);
  Serial.print("Ldr: ");  Serial.println(adc1);
  Serial.print("Lux: ");  Serial.println(event.light);
  Serial.print("Water: ");  Serial.println(adc2);
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("ESP-MAC-Address: ");  Serial.println(WiFi.macAddress());  // muestro la mac
  Serial.print("FromIP: "); Serial.println(WiFi.localIP());               // muestro la IP que tiene mi arduino (IP de origen)
  Serial.print("ToMQTT: "); Serial.println(mqtt_server);                  // muestro la IP del MQTT server (IP de destino)
  Serial.println();
  Serial.print("I'm going to sleep for "); Serial.print(durationSleep); Serial.print(" seconds");

  



     
  ESP.deepSleep(durationSleep * 1000000);  // entro ne modo deep-sleep
  
}

/*--------------------- MQTT CALBACK AND FUNCTIONS ----------------------------*/
void MQTTcallback(char* mqtt_topic, byte* payload, unsigned int length) {     // Genero una funsion de callback
  String message;                                                             // Seteo como string el mensaje
  for (int i = 0; i < length; i++) {                                          // Si el mensaje es igual a cero le sumo uno
    message = message + (char)payload[i];                                     // Convierto *bytes a Strings
  }
} 




void loop() {
  // como utilizo el deep-sleep no uso este loop
  }


