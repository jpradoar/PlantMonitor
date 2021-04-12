# INFO:

<pre>
La información declarada acá es a título informativo, usada en muchos casos para futuros fixes y/o mejoras.
</pre>

<br>

### Arquitectura:
<pre>
La arquitectura esta sobredimensionada, en mucho de los casos solo es necesario deployar lo declarado a continuación.  Lo demás es para fines educativos y/o aprendizaje 
	- Mosquitto (mqtt)
	- Subscriber
	- InfluxDB
	- Grafana
</pre>

<br>

### Sensores:
<pre>
Los sensores pueden variar por varias razones.
	 A) El error de los propios sensores. (Teniendo en cuenta que son casi los mas baratos del mercado, dentro de todo, funcionan bien)
	 B) La calibracion previa de los mismos.
	 C) La posición y el lugar donde esten.  (En la terraza hay más viento y eso puede generar que la temperatura pueda variar con respecto a otro lugar como un balcon cerrado por ejemplo)
	 D) El voltaje entregado por el modulo
	 E) Razones que aún desconozco e iré descubriendo con el uso y las pruebas.


</pre>







### Info no tan relevante pero útil.
	Al hacer un <b>lsusb</b>,  el nodemcu figura como 
	Bus 001 Device 031: ID 1a86:7523 QinHeng Electronics HL-340 USB-Serial adapter




<br><hr><br>




### LINKS DE INTERES:

<br>

### Deep-Sleep (works with Lolin NodeMcu v3)
	https://diyprojects.io/esp8266-deep-sleep-mode-test-wake-pir-motion-detector/#.YGzSjxLQ-AA

### mAh to Wh conversion calculator
	https://www.rapidtables.com/calc/electric/mah-to-wh-calculator.html

### Global solar atlas (BsAs CABA)
	https://globalsolaratlas.info/map?c=-34.571037,-58.457565,11&s=-34.600998,-58.490524&m=site

### Unix Timestamp Conversion Tool
	https://www.epochconverter.com/






### No necesarios pero interesantes para leer
	https://blog.voneicken.com/2018/lp-wifi-esp-comparison/
	
