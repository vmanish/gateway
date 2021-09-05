import paho.mqtt.client as mqtt
import sys, random, time, threading
from datetime import datetime

def OneSecond():
        threading.Timer(1, OneSecond).start()
        now =datetime.now().timetuple()
        print("\n--", now.tm_sec, "--", end = "")
        for device in devices:
                if now.tm_sec == int(device["trigger"]):
                        client = mqtt.Client(device["name"])
                        client.connect("localhost", 1883, 60)
                        client.publish("data", str({"name" : device["name"], "temp": str(random.randint(-5, 55))}))
                        print(device["name"]+"-->", end="")
                        client.disconnect()


numberOfDevices = int(sys.argv[1])
number = 0
devices = []
#prepare fake devices
while number < numberOfDevices:
        number = number + 1
        control = {"name" : "E_"+str("{:05d}".format(number)), "trigger": str(random.randint(0, 10000) % 60) }
        devices.append(control)

threading.Timer(1, OneSecond).start()
while 1:
        pass
#never gets here
