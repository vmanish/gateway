# Device gateway

POC for a Device Gateway monitoring sensor devices.

Components:
Sensors posting temperature data on mqtt "data" topic.
Simulator, Creates configurable number of fake devices that sends data every minute to the gateway.

Monitor, Listens to all the devices data on mqtt "data" topic and creates device statistics.
        Also implements the device statistics queries from CLI over "command" topic.

CLI,  handles command request /response to/from monitor to gather device statistics, on mqtt "command" topic.

MQTT Broker, handles all MQTT communication  between CLI, Devices (simulator) and the Monitor.

Connector(s),  To add other devices protocols, a per protocol device connector component would be required. This connector will parse protocol specific device data to post the same on mqtt "data" topic.
Keeper, subscribes to all data MQTT communication and feed run time sensor data streams in to a data store.


Installation

Prerequisites:-
Scons
Paho-MQTT c and cpp libraries and python packages.
build essentials
Mosquitto MQTT broker
Python
Docker 

apt install scons
apt install mosquitto mosquitto-clients




Usage:-
1. Run MQTT Broker
2. Run Simulator to generate device traffic
3. Run monitor
4. Use CLI to observe device statistics developing from device traffic.