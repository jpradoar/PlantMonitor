## Monitor de planta "Real Plant Book" + Estacion meteorologica

Este proyecto surge de la necesidad de monitorear el ciclo de vida de una planta en relacion al estado del clima, utilizando tecnologias OpenSource e IoT.
En este caso, IoT en tomates cherry :tomato:.  (aunque aplica para cualquier otro fin)

A través de los sensores, el sistema recolecta datos que son almacenados en una base de datos. Estos a su vez, son mostrados en un panel en tiempo real, para luego generar lo que yo llamo un "Real Plant Book", el cual refleje los niveles reales y necesarios, (e ideales en el mejor de los casos), para un correcto y continuo crecimiento de la planta o fruto. 
Junto con esto están configurados unos niveles máximos y mínimos de alertas, (agua, sol, etc) que, en el caso de que estos estén fuera de los niveles establecidos, enviará automáticamente una alerta para analizar el problema, (mucho calor, poca agua, etc etc).  
Al cabo de un año de uso, se podrá tener el histórico completo del estado del clima más el estado de la plata (comportamiento) según clima. 

El sistema también cuenta con una simple API que puede ser consultada públicamente, para fines múltiples.

Adicionalmente, el sistema consume información del Servicio Meteorológico Nacional (SMN) y la guarda en la base de datos, la cual es mostrada en el mismo panel para tener visibilidad real y precisa. (Punto de comparación), ya que el sistema puede mostrar distintas mediciones dependiendo del lugar donde esté (ej: si esta en un balcón, o si esta en el interior de una casa).

### Info
- Esta es la versión v0.1.0-beta.  Si bien es completamente funcional, algunas partes del sistema no tienen el mejor diseño ni el código más elegante. 
- Sientete libre de "forckear" y mejorar. O si crees que puedes ayudarme a mejorar el código, bienvenido seas!
- <b>Si crees que es interesante para tu jardín, huerta o invernadero por favor contactame, seguramente podremos hacer algo fantástico juntos!</b>
- Contacto: jpradoar @ gmail . com


### En el futuro:
  - Documentar con mayor detalle y traducir a ingles                <b>[En marcha]</b>
  - Generar un pequeño invernadero con control de ventilación.      <b>[Pendiente...]</b>
  - Implementar el uso de paneles solares (100% autosustentable).   <b>Hecho!</b>
  - Generar el sistema de riego automático.                         <b>[Investigando...]</b>
  - Generar un Plant Book más completo.                             <b>[Pendiente...]</b>
  - Implementar el uso en Hidroponia.                               <b>[Pendiente...]</b>
  - Implementar desarrollo a una escala mayor.                      <b>[Investigando...]</b>
  - Implementar sistema de usuarios para api.                       <b>[Pendiente...]</b>

<br>

### Panel del sistema completo de la planta (Grafana)
<p align="center">
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/grafana-panel.png"/>
</p>

<br>

### Mensajes y alertas en Slack + Thresholds/Umbrales configurables
<p align="center">
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/grafana-alert-slack.png"  width="50%" height="50%"  />
</p>

<br>

### Interfaz web del modulo de la planta
<p align="center">
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/module-web.png"  width="50%" height="50%"  />
</p>


<br><br><br>

### Materiales (Pending...)
<p align="center">
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/dht22.jpg"  width="20%" height="20%"/>   
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/ldr.jpg"  width="20%" height="20%"/><br>
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/Soil.jpg" width="20%" height="20%"/>    
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/analog-digital-converter-16-bit-ads1115.jpg"  width="20%" height="20%"/><br>
 <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/panel-solar.png"  width="20%" height="20%"/> Panel Solar 9v 222ma 2w 115 X 115 Mm
</p>

<br><br><br>

### Circuitos
<p align="center">
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/Fritzing-graph.png"  width="50%" height="50%"/>
</p>


<br><br><br>

### Arquitectura
<p align="center">
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/arquitectura.png"/>
</p>


<br><br><br>

### Pruebas de concepto
<p align="center">
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/plant00.jpg" width="50%" height="50%" /><br>
</p>
<p align="center">Mono "invernadero" (cañas de bambú y bolsa Polipropileno)<br>
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/mono-invernadero.jpg"  width="50%" height="50%"  /><br>
</p>
<p align="center">Final<br>
  <img src="https://github.com/jpradoar/PlantMonitor/tree/master/img/planta-invernadero.jpg"  width="50%" height="50%"  /><br>
</p>

<br>

### Cómo correr/ejecutar
<pre>
git clone https://github.com/jpradoar/PlantMonitor.git
cd PlantMonitor/infra/
docker-compose up -d
</pre>

<br>

### Preguntas frecuentes: (FAQ)
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
