#-----------------------------
# INFO
# Si bien podria agregar esto en SubBot.py prefiero tenerlo separado por dos razones
# 1. El ciclo de actualizacion del SMN es cada 1 hora, asi que no tiene sentido estar updateando cada menos tiempo
# 2. Esta api es completamente externa al sistema, la uso solo para tener datos para comparar con mis sensores. 
# 3. La idea es hacer sobreingenieria para aprender y de paso trabajar todo como micro-servicios
#-----------------------------
import paho.mqtt.client as mqtt
import json
import requests
import time
import socket

# Constantes SMN
url             = "https://ws.smn.gob.ar/map_items/weather"   
CityName        = "Capital Federal"
CityProvince    = "Capital Federal"

# Constantes Servers
broker_address      = "mosquitto"       # Broker address
port                = 1883              # Broker port
user                = "admin"           # Connection username
password            = "admin"           # Connection password
topic               = "#"               # Subscribe to ALL topics
client_name         = "smn"      


def getSMN():
    json_obj = requests.get(url).json() # Obtengo el json via request url y me aseguro que venga en json()
    for item in json_obj:               # Hago un bucle para consumir todo el json y filtro la ciudad y la provincia
        if 'name' in item and item['name'] == CityName and item['province'] == CityProvince:
                smn_lastupdate  = item['updated']
                #smn_name        = item['name']      # String    # Resolver el tema del espacio entre palabras 
                #smn_province    = item['province']  # String    # Resolver el tema del espacio entre palabras 
                smn_lat         = item['lat']
                smn_lon         = item['lon']
                smn_hum         = item['weather']['humidity']
                smn_temp        = item['weather']['temp']
                smn_pressure    = item['weather']['pressure']
                smn_st          = item['weather']['st']             # is number, but String when None
                smn_visibility  = item['weather']['visibility']
                smn_wind_speed  = item['weather']['wind_speed']     # String
                smn_description = item['weather']['description']    # String
                smn_wing_deg    = item['weather']['wing_deg']       # String
                #
                data_key    = [  smn_lat,   smn_lon,   smn_hum,   smn_temp,   smn_pressure,   smn_visibility  ]
                data_value  = [ "smn_lat", "smn_lon", "smn_hum", "smn_temp", "smn_pressure", "smn_visibility" ]

                # hago un bucle y obtengo todos los datos de la lista de key/value y lo publico en el MQTT server
                count = 0
                for i in data_value:
                    publish_message(data_value[count],data_key[count])
                    count += 1

    # Para no llenar de requests a la api del SMN dejo que pasen 15 min antes de la prox query.
    seconds = 900 # 900 segundos = 15 min           
    for x in range(seconds,0,-1):
        time.sleep(1)
        print("Wait "+str(x)+" seconds remaining for the next query (SMN)")


                    
def publish_message(smn_key,smn_value):
    print(smn_key, smn_value)
    client = mqtt.Client(client_name)
    print("connecting to broker ",broker_address)
    client.connect(broker_address)#connect
    client.loop_start() #start loop to process received messages
    print("publishing " + smn_key, smn_value)
    client.publish(smn_key, smn_value, 0, 0, "false");
    time.sleep(1)
    client.disconnect() #disconnect
    client.loop_stop() #stop loop                 




def DoMagic():
    a_socket        = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    location        = (broker_address, port)
    result_of_check = a_socket.connect_ex(location)
    if result_of_check == 0:
        getSMN()
    else:
       print("Port is not responding, wait a few seconds...")
       time.sleep(15)   # espero hasta que vuelva a responder.


while True: 
    DoMagic()