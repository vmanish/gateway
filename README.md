# Device gateway

POC for a Device Gateway for monitoring sensor devices.
![alt text](https://github.com/vmanish/gateway/blob/main/gateway.png?raw=true)
## Major Components:
### Sensors/ Simulator
Actual Sensors posting temperature data on mqtt "data" topic.
Simulator creates configurable number of fake devices that sends data every minute to the gateway.
### Monitor 
Listens to all the devices data on mqtt "data" topic and builds device statistics. These stats can be queried via the CLI supported over the mqtt "command" topic.
### CLI 
Handles command request /response to/from monitor to gather device statistics, on mqtt "command" topic.
### MQTT Broker 
Handles all MQTT communication  between CLI, Devices (simulator) and the Monitor.
### Connector(s) [To be implemented]
To add other devices protocols, a per protocol device connector component would be required. This connector will parse protocol specific device data to post the same on mqtt "data" topic.

### Ruler [To be implemented]
Rules engine to apply basic actions on incoming device data stream.

### Keeper [To be implemented]
Responsible for storing all device data, derived streams to data store locally or at remote.

### Analyzer [To be implemented]
Analyzes incoming data streams to  generate new derived streams as needed for business logic.


## Installation & Usage

### Prerequisites:- (refer Dockerfile)
Ubuntu,
Scons,
Paho-MQTT c and cpp libraries and python packages,
Gcc, G++ and Build essentials,
Mosquitto MQTT broker,
Python, Python-pip,
Docker

### Installation Steps 
#### Build the Docker Image:-
```
docker build -t gateway:v1 .
```

#### Run the docker image
```
docker run  -it gateway:v1  /bin/bash
```
### Usage:- (refer startup.sh)
1. Run MQTT Broker (mosquitto)
2. Run Simulator to generate device traffic (simulator/simulator.py)
3. Run monitor (monitor/monitor)
4. Use CLI to observe device statistics developing from device traffic. (cli/cli.py)
#### Start Message broker, device simulator and  gateway monitor services.
```
sh startup.sh
```

#### Run CLI to interact with the monitor gateway
```
cd cli
CLI Usage:-
                python3 cli.py listAllDevices
                python3 cli.py getDeviceInfo {deviceName}
                python3 cli.py getTotalMessageCount 

                Note: refer deviceName from listAlldevices command output.
```
#### To see message broker & monitor service logs 
```
cd /home/gateway && tail -f nohup.out

data: {'name': 'E_00023', 'temp': '8'}       <<<< Monitor receiving temperature data from sensor E_00023
1630928550: Client E_00023 disconnected.     <<<< Sensor E_00023 disconnected
1630928553: New connection from 127.0.0.1 on port 1883.
1630928553: New client connected from 127.0.0.1 as E_00010 (p2, c1, k60).   
data: {'name': 'E_00010', 'temp': '0'}        
...
```
