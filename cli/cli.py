import paho.mqtt.client as mqtt
import sys, random, time, threading
from datetime import datetime


def on_message(client, userdata, message):
    print(str(message.payload))

commandList = {
    "listAllDevices",       #List all devices from where messages are arriving
    "getDeviceInfo",        #List available information on given {deviceName}
    "getTotalMessageCount"  #Give total message count received from all devices.
    }
usage = """CLI Usage:-
                python3 cli.py listAllDevices 
                python3 cli.py getDeviceInfo {deviceName}
                python3 cli.py getTotalMessageCount )"""
if(len(sys.argv) > 1):
    command = sys.argv[1]
else:
    print(usage)
    exit()
param = "x"
if(command == "getDeviceInfo"):
    if((len(sys.argv)-1) == 2):
        param = sys.argv[2]
    else:
        print(usage)
        exit()

client = mqtt.Client("cli")
client.on_message=on_message
client.connect("localhost", 1883, 60)
client.loop_start()
client.subscribe("command")
if(command in commandList):
    msg = {'request':command, 'param' :param}
    client.publish("command", str(msg))
    time.sleep(4)
else:
    print(">>"+usage)
client.loop_stop()


#done
