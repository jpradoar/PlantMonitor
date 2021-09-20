## Monitor de planta "Real Plant Book" + Estacion meteorologica

###  | [Home](https://jpradoar.github.io/PlantMonitor/)  | [Linkedin](https://www.linkedin.com/in/jonathan-prado-87b1b628) | [Github](https://github.com/jpradoar/) |

<br> 

Este proyecto surge de la necesidad de monitorear el ciclo de vida de una planta en relacion al estado del clima, utilizando tecnologias OpenSource e IoT.
En este caso, IoT en tomates cherry   (aunque aplica para cualquier otro fin)

A través de los sensores, el sistema recolecta datos que son almacenados en una base de datos. Estos a su vez, son mostrados en un panel en tiempo real, para luego generar lo que yo llamo un "Real Plant Book", el cual refleje los niveles reales y necesarios, (e ideales en el mejor de los casos), para un correcto y continuo crecimiento de la planta o fruto. 
Junto con esto están configurados unos niveles máximos y mínimos de alertas, (agua, sol, etc) que, en el caso de que estos estén fuera de los niveles establecidos, enviará automáticamente una alerta para analizar el problema, (mucho calor, poca agua, etc etc).  
Al cabo de un año de uso, se podrá tener el histórico completo del estado del clima más el estado de la plata (comportamiento) según clima. 

El sistema también cuenta con una simple API que puede ser consultada públicamente, para fines múltiples.

Adicionalmente, el sistema consume información del Servicio Meteorológico Nacional (SMN) y la guarda en la base de datos, la cual es mostrada en el mismo panel para tener visibilidad real y precisa. (Punto de comparación), ya que el sistema puede mostrar distintas mediciones dependiendo del lugar donde esté (ej: si esta en un balcón, o si esta en el interior de una casa).

### Que quiero lograr con esto?
 - Armar un "PlantBook" de una planta X en una zona particular del planeta
 - Monitorear el ciclo de vida y entorno "ideal" para el crecimiento natural de una planta
 - Con ese PlantBook podría reproducir el crecimiento de una planta que crece en otro país, en el balcón de casa :D 
 - Si varias personas en distintos países arman su propio PlantBook, estos podrían ser publicados y personas de todo el mundo podrían reproducir dicha planta por mas que no exista en el país local. 

### Info
- Esta es la versión v0.1.0-beta.  Si bien es completamente funcional, algunas partes del sistema no tienen el mejor diseño ni el código más elegante. 
- Sientete libre de "forckear" y mejorar. O si crees que puedes ayudarme a mejorar el código, bienvenido seas!
- <b>Si crees que es interesante para tu jardín, huerta o invernadero por favor contactame, seguramente podremos hacer algo fantástico juntos!</b>
- Contacto: jpradoar @ gmail . com



<br>

<div align="center"><h3> MVP (Minimo Producto Viable)</h3> </div>
<p align="center">
 <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/box0.jpeg" width="30%" height="30%" />
 <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/box2.jpeg" width="30%" height="30%" />
 <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/box3.jpeg" width="30%" height="30%" />
 <br>
 <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/box1.jpeg" width="30%" height="30%" />
 <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/box4.jpeg" width="30%" height="30%" />
</p>

<div align="center"><h3> Pruebas de concepto </h3> </div>
<p align="center">
  <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/plant00.jpg" width="30%" height="30%" /><br> 
</p>

<br>

<div align="center"><h3> Si te interesa saber como construí todo, acá tenes el paso a paso</h3> </div>
<p align="center">
 <a href="https://jpradoar.github.io/PlantMonitor/construccion"> <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/tool.png" width="20%" height="20%" /> </a>
</p>


<br>

<div align="center"><h3> Panel del sistema completo de la planta (Grafana) </h3> </div>
<p align="center">
  <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/grafana-panel.png"/>
</p>

<br>


<div align="center"><h3> Interfaz web del modulo de la planta </h3> </div>
<p align="center">
  <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/module-web.png"  width="30%" height="30%"  />
</p>

<br>


<div align="center"><h3> Circuitos </h3> </div>
<p align="center">
  <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/Fritzing-graph.png"  width="70%" height="70%"/>
</p>


<br>

<div align="center"><h3> Diseño y Arquitectura </h3> </div>
<p align="center">
  <img src="https://raw.githubusercontent.com/jpradoar/PlantMonitor/master/img/arquitectura2.png"/>
</p>

<br>
<div align="center"><h3> Tecnologias y descripcion de componentes </h3> </div>

|Tecnologias / Lenguajes | Uso | Obs |
|---       |---  |---  |
|C++       | Para todo el core en Arduino/ESP | - | 
|Python    | Para las API | - | 
|PHP       | Para el ABM de usuarios | - | 
|HTML      | Para el front end | - | 
|Docker    | Como microservicios | Podria usar servicios cloud, pero prefiero que sea "Cloud Agnostic"  |
|docker-compose  | Para levantar todo el stack | Tambien esta implementado sobre Kubernetes, pero a fines practicos es mas simple correrlo en docker-compose |


<br>

|Componente     | Funcion    | Obs | 
|---            |---         | ---      |
| Panel solar   | Generador de energia para las baterías     | - | 
| Bateria       | Almacenamiento de la energía obtenida del panel solar   | - | 
| ESP           | Core del desarrollo, donde esta toda la lógica de sensores     | - | 
| LDR           | Medir la intensidad de la luz     | Con esto calculo la cantidad y el tiempo de luz que le da a la planta | 
| Lux Sensor    | Medir la intensidad de la luz | Mismo concepto que el LDR pero dedicado a [Lux](https://es.wikipedia.org/wiki/Lux)
| 16Bit I2C     | Conversor de analógico a digital  | Como el ESP tiene 1 solo pin analógico uso esto para poder usar sensores analógicos|
| DHT22         | Medir temperatura y humedad del aire      | Lo uso para calcular el estado del clima y con eso hago algunas predicciones básicas   | 
| Soil Sensor   | Medir humedad de la tierra | Lo uso para saber si la plata necesita humedad o si la tierra esta muy seca    | 
| MQTT          | Servidor donde van todas las mediciones ([mosquitto-mqtt](https://mosquitto.org/)) | - | 
| Subscriber    | Consumir los mensajes del MQTT Server y enviar a la DB (InfluxDB) | - | 
| InfluxDB      | Guardar un histórico de toda la información obtenida de los sensores.  | - | 
| smn-Consumer  | Función que consulta el estado del tiempo real  | Lo uso para ver el diferencial entre mis sensores y la temperatura real    | 
| SMN           | [Servicio Meteorológico Nacional](https://www.smn.gob.ar/) | Gracias gente por ofrecer la api gratis :)  | 
| http-API      | Api para consumo de data  | La uso para consumir data sin hacer Querys directo a la DB  | 
| MySQL         | Base de datos de usuarios (ABM) | Lo uso para generar usuarios para la API o cualquier otra función que no sea 100% publica    | 
| Nginx         | Front End | - | 
| Grafana       | Visualización de toda la data  | - | 

<br>


<div align="center"><h3> Cómo correr/ejecutar </h3> </div>
<pre>
git clone https://github.com/jpradoar/PlantMonitor.git
cd PlantMonitor/infra/
docker-compose up -d
</pre>

<br>


<div align="center"><h3> Roadmap </h3> </div>

|Descripcion    | Estado    | 
|---            |---        |
| Medicion de sensores                                         |   Hecho          |
| Medicion de sensores SMN                                     |   Hecho          | 
| Implementar el uso de paneles solares (100% autosustentable).|   Hecho          |
| Implementar en Docker + docker-compose                       |   Hecho          |
| Implementar en kubernetes                                    |   Hecho          |
| Implementar en cloud                                         |   Hecho          |
| Construir caja protectora                                    |   Investigando   |
| Documentar con mayor detalle y traducir a ingles             |   En marcha      |
| Implementar un [pluviómetro](https://es.wikipedia.org/wiki/Pluvi%C3%B3metro)                                   |   Pendiente      |
| Implementar un [anemómetro de viento](https://es.wikipedia.org/wiki/Anem%C3%B3metro)                          |   Pendiente      |
| Generar el sistema de riego automático.                      |   Investigando   |
| Generar un Plant Book más completo.                          |   Pendiente      |
| Implementar el uso en Hidroponia.                            |   Pendiente      |
| Implementar desarrollo a una escala mayor.                   |   Investigando   |
| Implementar sistema de usuarios para api.                    |   Pendiente      |

<br>

<div align="center"><h3> Preguntas frecuentes: (FAQ) </h3> </div>

 - <b>El proyecto es publico, ¿tiene algún costo?</b><br>
    El proyecto es Open Source, es decir que todo el codigo està documentado y publicado para que cualquiera lo pueda usar, modificar y mejorar.
    100% reproducible por cualquier persona sin costo alguno. (solo deberías conseguir los materiales)

 - <b>Que tanto va a crecer este proyecto?</b><br>
    Mi idea es poder crecer hasta tener un sistema completo de monitoreo, 
    análisisis, riego automatico y generar mis propios PlantBook a travez de la experiencia.

 - <b>Tengo un pequeño jardínin, puedo implementarlo?</b><br>
    Si, puedes implementarlo sin problemas. (de hecho seria genial!)

 - <b>Tengo una huerta y/o invernadero y quiero implementarlo. Puedo agregar mas sensores?</b><br>
    Si, puedes agregar tantos sensores como la cantidad de pines (o más si usas expansor analogico!). O bien puedes agregar más sensores digitales.
 
 - <b>No tengo una huerta ni invernadero pero quiero usarlo como una Estación meteorológica . Puedo agregar mas sensores?</b><br>
    Claro, puedes usarlo solo como Estación meteorológica en tu casa/balcon/etc y hasta agregar tus propios sensores. Seria genial!

 - <b>Tengo algunas dudas y preguntas acerca del proyecto. ¿Como puedo contactarte?</b><br>
    Puedes enviarme un mail y me pondré en contacto.  jpradoar (arroba) gm4il . c0m

 - <b>Quiero ayudar. ¿Como puedo hacerlo?</b><br>
    Si sabes programar puedes revisar el codigo y mejorarlo. Así todos tendremos un mejor sistema.
    Si sabes de jardinería, puedes generar tus  PRE-PlantBooks. (lo cual ayudará a tener niveles más acertados)
    Si sabes de diseño, puedes intentar mejorar las interfaces o la arquitectura en general.
    Cualquier skill sirve. Solo sientete libre de comunicarlo.
