#!/bin/bash

# Podría hacerlo con python, pero prefiero hacerlo con bash así tengo varios lenguajes.
# De momento el concepto es consultar la api del SMN y mostrarla en el grafana
# para ver la diferencia entre el clima que muestra el SMN y mis sensores.
# Los sensores pueden variar por varias razones.
# A) el error de los propios sensores. 
# B) la posición y el lugar  (en la terraza hay mas viento y por ende la temperatura puede variar)
# C) el voltaje entregado por el modulo
# D) razones que aún desconozco. 



# Get sheater and send filtered output to local file.
curl -s https://ws.smn.gob.ar/map_items/weather | jq -r '.[] | select(.name=="Capital Federal")' >  data.json

lastupdate=$(cat data.json |jq -r .updated)
name=$(cat data.json |jq -r .name|sed 's/ //g')
lat=$(cat data.json |jq -r .lat)
lon=$(cat data.json |jq -r .lon)
tempDesc=$(cat data.json |jq -r .weather.tempDesc|sed 's/..$//')
humidity=$(cat data.json |jq -r .weather.humidity)
pressure=$(cat data.json |jq -r .weather.pressure)
st=$(cat data.json |jq -r .weather.st)
visibility=$(cat data.json |jq -r .weather.visibility)
wind_speed=$(cat data.json |jq -r .weather.wind_speed)
wing_deg=$(cat data.json |jq -r .weather.wing_deg)

# Resolver esta cosa fea, de momento la info que inserta esta ok.
echo "curl -si -XPOST 'http://localhost:8086/write?db=IoT' --data-binary 'smn,smn_name=$name,smn_lat=$lat,smn_lon=$lon,smn_temp=$tempDesc,smn_hum=$humidity,smn_pressure=$pressure,smn_st=$st,smn_visibility=$visibility,smn_wind_speed=$wind_speed,smn_wing_deg=$wing_deg  smn_lastupdate=$lastupdate $lastupdate'"|bash
