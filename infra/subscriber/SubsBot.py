#!/usr/bin/env python3
import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient # FOR write data on influxDB
import time
import socket


# constantes 
broker_address      = "mosquitto"    # Broker address
database_address    = "influxdb"    # DB address
port                = 1883              # Broker port
influxport          = 8086
user                = "admin"           # Connection username
password            = "admin"           # Connection password
topic               = "#"               # Subscribe to ALL topics
db_name             = "IoT"             # DB name
client_name         = "Subscriber"      
intent              = 0


def on_message(client, userdata, message):
    #print("received message: " ,str(message.payload.decode("utf-8")))
    value       = str(message.payload.decode("utf-8"))   
    xvalue      = float(value)
    print(message.topic , str(value))
    dbClient    = InfluxDBClient(database_address, influxport, user, password, db_name)
    loginEvents = [{"measurement":"measurement", "fields":{ message.topic : xvalue } }]
    print(loginEvents)
    writedata   = dbClient.write_points(loginEvents)

def on_subscribe():
    client      = mqtt.Client(client_name)
    client.connect(broker_address, port )   #connect
    client.loop_start()                     #start loop to process received messages
    client.subscribe(topic)                 #subscribe to topic
    client.on_message = on_message 
    time.sleep(5)
    client.loop_stop()


def DoMagic():
    a_socket        = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    location        = (broker_address, port)
    result_of_check = a_socket.connect_ex(location)
    if result_of_check == 0:
        print(".")
        on_subscribe()
    else:
       print("Port is not responding, wait a few seconds...")
       time.sleep(15)

while True: 
    DoMagic()