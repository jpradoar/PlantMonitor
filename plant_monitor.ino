/*
Plant Monitor v1.0.0
Jonathan Prado
jpradoar (arroba) gm4il punto COM
*/

#include <ESP8266WiFi.h>        // Libreria para utilizar el modulo wifi nativo del ESP
#include <ESP8266WebServer.h>   // Libreria para levantar un pequeño webserver en el ESP
#include "DHT.h"                // Libreria para manejar el sensor de humedad y temperatura
#include <PubSubClient.h>       // Libreria para manejar comunicación MQTT
#include <Wire.h>               // Libreria para usar el I2C.
#include <Adafruit_ADS1015.h>   // Libreria para el modulo de ampliación de pines analogicos.


// Descomentar el que se necesite utilizar.
//#define DHTTYPE DHT11       // DHT 11
//#define DHTTYPE DHT21       // DHT 21 (AM2301)
#define DHTTYPE DHT22         // DHT 22  (AM2302), AM2321

// WIFI 
const char* ssid      = "MySSID";  // SSID
const char* password  = "MySSID-PASS";      // Password

/*-------------------------------- USER CONFIGURED SECTION START -------------------------------- */
const char* mqtt_server       = "mosquitto"; // Servidor donde esta el MQTT server
const int   mqtt_port         = 1883;           // Puerto del MQTT
const char *mqtt_user         = "admin";        // USER
const char *mqtt_pass         = "admin";        // PASS
const char *mqtt_client_name  = "HomeWeatherSystem";       // Nombre del cliente (Client connections cant have the same connection name)
const char *mqtt_topic        = "IoT";          // El nombre del topic donde voy a insertar la data
const char *admin_topic       = "admin";      // El nombre del topico

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient cherry;

PubSubClient client(cherry);  // Cuidado, esto no soporta guiones medios

Adafruit_ADS1115 ads;           // Inicializo el sensor ADS1115 (ampliador analogico)

const int AirValue      = 14750;    // Valor cuando está fuera del agua y seco
const int WaterValue    = 7430;     // Valor cuando está dentro del agua

int soilMoistureValue   = 0;    // Defino el valor en cero
int soilmoisturepercent = 0;    // Defino el valor en cero

ESP8266WebServer server(80);    // Levanto un webserver en el puerto 80


uint8_t DHTPin    = 2;          // Defino el pin del DHT (ESP8266 D4)
DHT dht(DHTPin, DHTTYPE);       // Inicializo el sensor DHT
float Temperature;              // Defino el valor Temperatura como float (por que viene en numero con coma)
float Humidity;                 // Defino el valor Humedad como float (por que viene en numero con coma)


void setup() {                  // START SETUP
  Serial.begin(115200);         // Inicializo el serial en 115200 para poder enviar los outputs por consola
  delay(100);                   // Espero 100ms

//  pinMode(LED_BUILTIN, OUTPUT); // De ser necesario puedo setear el led on-board como testigo (Opcional)
  pinMode(DHTPin, INPUT);         // Defino el pin del DHT en modo input para leer los datos que genera el mismo.
  dht.begin();                    // Inicializo el DHT

  ads.begin();                    // Inicializo el ads (expansor analogico)

  Serial.println("Connecting to "); // Imprimo por consola para saber que inició
  Serial.println(ssid);             // Imprimo por consola el SSID para estar seguro que me conecto a la red correcta

  WiFi.begin(ssid, password);       // Inicializo la wifi
  
  while (WiFi.status() != WL_CONNECTED) { // En este loop chequeo si la wifi esta conectada
    delay(1000);                          // Para no estresar al router intento cada 1 segundo
    Serial.print(".");                    // Mientras el loop siga, imprimo un punto para saber que esta haciendo algo (testigo)
  }                                       // Fin del loop de conexion a wifi

  Serial.println("");                     // Imprimo un salto de linea vacío.
  Serial.println("WiFi connected..!");    // Imprimo el mensaje que estoy conectado.
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());  // Imprimo la IP que se me asigno por si necesito acceder.

  server.on("/", handle_OnConnect);       // Defino una ruta para el webserver  en este caso el /
  server.onNotFound(handle_NotFound);     // Defino un 404

  server.begin();                         // Inicializo el webserver
  Serial.println("HTTP server started");  // Imprimo que el servicio web ya esta corriendo.



/* -------------------------------- MQTT CONFIG START --------------------------------- */
  client.setServer(mqtt_server, mqtt_port);       // Seteo los parametros de mi MQTT server
  client.setCallback(MQTTcallback);               // Seteo un calback

  while (!client.connected()) {                   // Genero un loop para intentar conectarme.
    Serial.println("Connecting to MQTT...");      // Mando un mensje que estoy intentando conectarme.
    if (client.connect(mqtt_client_name, mqtt_user, mqtt_pass )) {    // Paso por parametro los datos que necesito para conectarme.
      Serial.println("connected");                                    // Imprimo que estoy conectado.
    } else {                                                          // Si no me puedo conectar hago lo siguiente
      Serial.print("failed with state ");  // Imprimo un mensaje que no me pude conectar por alguna razon (en general es por que no llego al server)
      Serial.println(client.state());      // Si recibo el estado 5 es por falta de coincidencia en la configuración
      delay(3000);                         // Genero un reintento cada 3 segundos para no estresar el server remoto.
    }
  }

/* -------- SUBSCRIBE TO... -----------*/
  client.subscribe("IoT");                // Me subscribo a la cola de mi MQTT

/* -------- WITHNESS LIGHT onboard-led -----------*/
  pinMode(LED_BUILTIN, OUTPUT);           // Pongo el led onboard como testigo (Opcional)
  digitalWrite(BUILTIN_LED, HIGH);        // Y lo prendo  (Opcional)


} // END SETUP




/*--------------------- MQTT CALBACK AND FUNCTIONS ----------------------------*/
void MQTTcallback(char* mqtt_topic, byte* payload, unsigned int length) {     // Genero una funcion de callback
  String message;                                                             // Seteo como string el mensaje
  for (int i = 0; i < length; i++) {                                          // Si el mensaje es igual a cero le sumo uno
    message = message + (char)payload[i];                                     //Convierto *bytes a Strings
  }


/* -------- PUBLISH MY IP, VERY IMPORTANT -----------*/
/*
  if(message == "ping"){                                  // Esto es solo para pruebas y debug 
      String ipaddress = WiFi.localIP().toString();
      char ipchar[ipaddress.length()+1];
      ipaddress.toCharArray(ipchar,ipaddress.length()+1);
      client.publish(admin_topic, ipchar);
  }
*/
} 


void loop() {                          // START LOOP

  server.handleClient();

  Temperature = dht.readTemperature();  // Leo el sensor y lo guardo en una variable llamada Temperature
  Humidity = dht.readHumidity();        // Leo el sensor y lo guardo en una variable llamada Humedad


  short adc0 = ads.readADC_SingleEnded(0); // (SOIL) Leo del expansor analogico la posicion 0 para Obtener datos del A0 del ADS1115SOIL que tiene conectado otro sensor 
  short adc1 = ads.readADC_SingleEnded(1); // (LDR)  Leo del expansor analogico la posicion 0 para Obtener datos del A0 del ADS1115SOIL que tiene conectado otro sensor 
  
  soilmoisturepercent = map(adc0, AirValue, WaterValue, 0, 100); // Aca mapeo el dato del sendor de tierra (SOIL) junto con los valores maximox y minimos que declare al principio

  if(soilmoisturepercent > 100){
      //Serial.println("100 %");    // Opbional, descomentar para ver que trae
      soilmoisturepercent = 100;    // Si el valor que recibo es mas de 100, le hardcodeo un 100 por que no tiene sentido tener mas de 100%
  }
  else if(soilmoisturepercent <0){
      //Serial.println("0 %");      // Opbional, descomentar para ver que trae
      soilmoisturepercent = 0;      // Si el valor que recibo es menor de 0, le hardcodeo un 0 por que no tiene sentido tener menos de 0%
    }
  else if(soilmoisturepercent >0 && soilmoisturepercent < 100){
      //Serial.print(soilmoisturepercent);    // Opbional, descomentar para ver que trae
     // Serial.println("%");
    }

  // No tiene mucho sentido explicar esto,  imprimo todos los datos
  Serial.print("Temp: ");
  Serial.println(Temperature);
  Serial.print("Hum: ");
  Serial.println(Humidity);
  Serial.print("Soil: ");
  Serial.println(soilmoisturepercent);
  Serial.print("Ldr: ");
  Serial.println(adc1);
  Serial.println("xxxxxxxxxxxxx");

  // Aca me conecto al MQTT server remoto.
  client.connect(mqtt_client_name, mqtt_user, mqtt_pass, mqtt_topic, 0, 0, "closed");

// Aca no tiene mucho sentido explicar. Publico los datos al MQTT server en formato String
  client.publish("Temperature", String(Temperature).c_str(), true);
  delay(100);
  client.publish("Humidity", String(Humidity).c_str(), true);
  delay(100);
  client.publish("Soil", String(soilmoisturepercent).c_str(), true);
  delay(100);
  client.publish("Ldr", String(adc1).c_str(), true);
  client.disconnect();

  delay(2000);          // Espero 2 segundos para no estresar el server.
}

void handle_OnConnect() { // Funcion para generar el index del webserver
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}


// Aca no tiene mucho sentido explicar, armo un index.html medianamente lindo con CSS e iconos de fontawesome

String SendHTML(float Temperaturestat,float Humiditystat){
  short adc1 = ads.readADC_SingleEnded(1); // LDR   (Esto lo tengo que poner en la linea 185 despues del Humidity)
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=no'><script src='https://kit.fontawesome.com/a27eb255f0.js' crossorigin='anonymous'></script>\n";
  ptr +="<title>Plant Monitor v0.1</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id='webpage' align='center'>\n";
  ptr +="<h1>Plant Monitor v.0.1</h1>  <i class='fa fa-leaf fa-3x' style='color:Green;'></i> \n ";
  ptr +="<p><i class='fa fa-thermometer-quarter fa-2x' style='color:Blue;'></i>Air Temperature: ";
  ptr +=(int)Temperaturestat;
  ptr +="&#176;C</p>";
  ptr +="<p><i class='fas fa-water fa-2x' style='color:Blue;'></i>Air Humidity: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  ptr +="<p><i class='fas fa-seedling fa-2x' style='color:#985c2d;'></i>Soil Moisture: ";
  ptr +=(int)soilmoisturepercent;
  ptr +="%</p>";
  ptr +="<p><i class='fas fa-sun fa-2x' style='color:#FFC300;'></i>Light intensity: ";
  ptr +=(int)adc1;
  ptr +="</p>";
  ptr +="</div>\n";
  ptr +="<a href='https://github.com/jpradoar/PlantMonitor' target='_blank' class='github-corner' aria-label='View source on GitHub'><svg width='120' height='120' viewBox='0 0 250 250' style='fill:#8904B1; color:#fff; position: absolute; top: 0; border: 0; right: 0;' aria-hidden='true'><path d='M0,0 L115,115 L130,115 L142,142 L250,250 L250,0 Z'></path><path d='M128.3,109.0 C113.8,99.7 119.0,89.6 119.0,89.6 C122.0,82.7 120.5,78.6 120.5,78.6 C119.2,72.0 123.4,76.3 123.4,76.3 C127.3,80.9 125.5,87.3 125.5,87.3 C122.9,97.6 130.6,101.9 134.4,103.2' fill='currentColor' style='transform-origin: 130px 106px;' class='octo-arm'></path><path d='M115.0,115.0 C114.9,115.1 118.7,116.5 119.8,115.4 L133.7,101.6 C136.9,99.2 139.9,98.4 142.2,98.6 C133.8,88.0 127.5,74.4 143.8,58.0 C148.5,53.4 154.0,51.2 159.7,51.0 C160.3,49.4 163.2,43.6 171.4,40.1 C171.4,40.1 176.1,42.5 178.8,56.2 C183.1,58.6 187.2,61.8 190.9,65.4 C194.5,69.0 197.7,73.2 200.1,77.6 C213.8,80.2 216.3,84.9 216.3,84.9 C212.7,93.1 206.9,96.0 205.4,96.6 C205.1,102.4 203.0,107.8 198.3,112.5 C181.9,128.9 168.3,122.5 157.7,114.1 C157.9,116.9 156.7,120.9 152.7,124.9 L141.0,136.5 C139.8,137.7 141.6,141.9 141.8,141.8 Z' fill='currentColor' class='octo-body'></path></svg></a><style>.github-corner:hover .octo-arm{animation:octocat-wave 560ms ease-in-out}@keyframes octocat-wave{0%,100%{transform:rotate(0)}20%,60%{transform:rotate(-25deg)}40%,80%{transform:rotate(10deg)}}@media (max-width:500px){.github-corner:hover .octo-arm{animation:none}.github-corner .octo-arm{animation:octocat-wave 560ms ease-in-out}}</style>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
