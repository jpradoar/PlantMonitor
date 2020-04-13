import paho.mqtt.client as mqtt
import paho.mqtt.client as mqttClient
from influxdb import InfluxDBClient # FOR write data in influxDB
import time

broker_address = "mosquitto"  #Broker address
database_address = "influxdb"
port = 1883                 #Broker port
user = "root"               #Connection username
password = "root"           #Connection password
subscr = "#"                #Subscribe to ALL topics
db_name = "IoT"


def on_connect(client, userdata, flags, rc):  # The callback for when the client connects to the broker
    print("Connected with result code {0}".format(str(rc)))  # Print result of connection attempt
    client.subscribe(subscr)  # Subscribe to the topic “digitest/test1”, receive any messages published on it

def on_message(client, userdata, msg):  # The callback for when a PUBLISH message is received from the server.
    value = str(msg.payload.decode("utf-8"))   
    xvalue=float(value)
    dbClient = InfluxDBClient(database_address, 8086, user, password, db_name)
    dbClient.create_database(db_name) # Momentaneo, borrar
    loginEvents = [{"measurement":"IoT", "fields":{ msg.topic : xvalue } }]
    writedata = dbClient.write_points(loginEvents)


Connected = False   #global variable for the state of the connection
client = mqttClient.Client("Producer")             #create new instance
client.username_pw_set(user, password=password)    #set username and password
client.on_connect= on_connect                      #attach function to callback
client.on_message= on_message                      #attach function to callback
client.connect(broker_address, port=port)          #connect to broker
client.loop_start()         #start the loop
 
while Connected != True:    #Wait for connection
    time.sleep(0.1)
      
client.subscribe(subscr)
      
try:
    while True:
        time.sleep(300000) # 5min
 
except KeyboardInterrupt:
    print("exiting")
    client.disconnect()
    client.loop_stop()
