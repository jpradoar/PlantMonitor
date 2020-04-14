#   PlantMonitor :chart_with_downwards_trend: :seedling:
Version 0.1.0

### Importante
- Este proyecto está financiado 100% por mi mismo. (Por tal razón crece lentamente).
- Esta es la versión v0.1.0.  Si bien es completamente funcional, algunos sistemas no tienen el mejor diseño ni el código más elegante. 
- Sientete libre de "forckear" y mejorar. O si crees que puedes ayudarme a mejorar el código, bienvenido seas!

- <b>Si crees que es interesante para tu jardín o invernadero por favor contactame, seguramente podremos hacer algo fantástico juntos!</b>
- Contacto: jpradoar (arroba) gm4il . c0m


### Info
Este proyecto surge de la necesidad de monitorear el estado y ciclo de vida de una planta.
En este caso, tomates cherry :tomato:. 
La finalidad del mismo es monitorear el ciclo de vida, mientras
los datos obtenidos de los sensores son almacenados en una base de datos, para luego generar lo que yo llamo un "plant book", el cual
refleje los niveles necesarios, (e ideales en el mejor de los casos), para un correcto y continuo crecimiento. Junto con esto
están configurados los niveles máximos y mínimos de alertas, que en el caso de que 
estos estén fuera de los niveles establecidos, enviará automáticamente una alerta para analizar el problema.
El sistema también cuenta con una simple API que puede ser consultada públicamente, para fines multiples.


### En el futuro:
  - Documentar con mayor detalle y traducir a ingles                <b>[On going]</b>
  - Generar un pequeño invernadero con control de ventilación.      <b>[On going]</b>
  - Generar el sistema de riego automático.                         <b>[Pending...]</b>
  - Generar un Plant Book mas completo.                             <b>[Pending...]</b>
  - Implementar el uso de paneles solares (100% autosustentable).   <b>[Pending...]</b>
  - Implementar el uso en Hidroponia.                               <b>[Pending...]</b>


### Imágenes del sistema:

<p align="center">Grafana Panel<br>
  <img src="img/grafana-panel.png"/><br>
</p>
<p align="center">Slack alert<br>
  <img src="img/grafana-alert-slack.png"  width="50%" height="50%"  /><br>
</p>
<p align="center">Plant Web Module<br>
  <img src="img/module-web.png"  width="50%" height="50%"  /><br>
</p>



### Circuitos (Pending...)

<p align="center">
  <img src="img/dht22.png"/><br>
</p>

<p align="center">
  <img src="img/ldr.png"/><br>
</p>

<p align="center">
  <img src="img/Soil.png"/><br>
</p>

<p align="center">
  <img src="img/analog-expansor.png"/><br>
</p>





### Imagenes Planta

<p align="center">Planta de tomate cherry<br>
  <img src="img/plant00.jpg" width="50%" height="50%" /><br>
</p>
<p align="center">Mono "invernadero" (cañas de bambú y bolsa Polipropileno)<br>
  <img src="img/mono-invernadero.jpg"  width="50%" height="50%"  /><br>
</p>
<p align="center">Final<br>
  <img src="img/planta-invernadero.jpg"  width="50%" height="50%"  /><br>
</p>
<br>




### Cómo correr/ejecutar
<pre>
git clone https://github.com/jpradoar/PlantMonitor.git
cd infra/ 
docker-compose up -d
</pre>



### FAQ

 - Que tanto va a crecer este proyecto?
    Mi idea es poder crecer hasta tener un sistema completo de monitoreo, 
    análisisis, riego automatico y generar mis propios PlantBook a travez de la experiencia.

 - Tengo un pequeño jardínin, puedo implementarlo?
    Si, puedes implementarlo sin problemas. (de hecho seria genial!)

 - Tengo un invernadero y quiero implementarlo. Puedo agregar mas sensores?
    Si, puedes agregar tantos sensores como la cantidad de pines (o más si usas expansor analogico!).

 - Tengo algunas dudas y preguntas acerca del proyecto. ¿Como puedo contactarte?
    Puedes enviarme un mail y me pondré en contacto.  jpradoar (arroba) gm4il . c0m

 - Quiero ayudar. ¿Como puedo hacerlo?
    Si sabes programar puedes revisar el codigo y mejorarlo. Así todos tendremos un mejor sistema.
    Si sabes de jardinería, puedes generar tus  PRE-PlantBooks. (lo cual ayudará a tener niveles más acertados)
    Si sabes de diseño, puedes intentar mejorar las interfaces o la arquitectura en general.
    Cualquier skill sirve. Solo sientete libre de comunicarlo.



<br><br>
<span style="font-size:1em;">Power by: <a href="www.disruptivesolutions.com.ar" target="_blank">DisruptiveSolutions</a></span>