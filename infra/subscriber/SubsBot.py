import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient # FOR write data in influxDB
import time
import socket



# constantes 
broker_address      = "mosquitto"  #Broker address
database_address    = "influxdb"
port                = 1883                 #Broker port
influxport          = 8086
user                = "admin"               #Connection username
password            = "admin"           #Connection password
topic               = "#"                #Subscribe to ALL topics
db_name             = "IoT"
client_name         = "Subscriber"
intent              = 0


def on_message(client, userdata, message):
    print("received message: " ,str(message.payload.decode("utf-8")))
    value       = str(message.payload.decode("utf-8"))   
    xvalue      = float(value)
    
    #dbClient    = InfluxDBClient(database_address, influxport, user, password, db_name)
    #loginEvents = [{"measurement":"IoT", "fields":{ message.topic : xvalue } }]
    #writedata   = dbClient.write_points(loginEvents)


def on_subscribe():
    client      = mqtt.Client(client_name)
    client.connect(broker_address, port ) 
    client.loop_start()
    client.subscribe(topic)
    client.on_message = on_message 
    time.sleep(5)
    client.loop_stop()


def DoMagic():
    a_socket        = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    location        = (broker_address, port)
    result_of_check = a_socket.connect_ex(location)
    if result_of_check == 0:
       on_subscribe()
    else:
       print("Port is not responding, wait a few seconds...")
       time.sleep(15)



time.sleep(10) # wait for docker compose up 
while True: 
    DoMagic()
    