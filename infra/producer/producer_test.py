#!/usr/bin/python
import paho.mqtt.client as mqtt
import datetime 
import requests
from random import randint
import json

statusid = randint(0, 1)
dataid = randint(1, 100)
number_rand = randint(1, 4)

#broker_address = "ec2-52-13-47-239.us-west-2.compute.amazonaws.com"
broker_address = "192.168.1.59"
broker_portnum = 1883
cli_id = "00001"
subscr = "#"
xtopic = "management"

def send_message():
    client = mqtt.Client()
    client.connect(broker_address, broker_portnum, keepalive=60 )
    client.subscribe(subscr)
    client.publish(topic = xtopic, qos=0, payload=json.dumps([{
    "measurement": "management",
    "fields": {
        "ipv4": "02:42:4d:ae:1e:e1",
        "name": "xxx",
        "number": 999
        }
    }]))
    print json.dumps([{
    "measurement": "management",
    "fields": {
        "ipv4": dataid,
        "name": "xxx"
        }
    }])
    



if __name__ == '__main__':
    send_message()
