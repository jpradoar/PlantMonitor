#!/usr/bin/python
import paho.mqtt.client as mqtt
import datetime 
import requests
from random import randint
import random
import json

statusid = randint(0, 1)
dataid = randint(1, 100)
number_rand = randint(1, 4)
rand_ligth = randint(1,2)
objs = ["Light", "Door"]
rand_obj = random.choice(objs)



#broker_address = "ec2-52-13-47-239.us-west-2.compute.amazonaws.com"
broker_address = "192.168.1.50"
broker_portnum = 1883
cli_id = "00001"
subscr = "#"
xtopic = "IoT"


def send_message():
    client = mqtt.Client()
    client.connect(broker_address, broker_portnum, keepalive=60 )
    client.subscribe(subscr)
    client.publish(topic = xtopic, qos=0, payload=json.dumps( [{"fields": {"status": statusid, "number": rand_ligth, "type": "DS-I", "id": 1, "name": rand_obj}, "measurement": "IoT"}] ))



if __name__ == '__main__':
    send_message()
