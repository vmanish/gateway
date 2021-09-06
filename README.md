# Device gateway

POC for a Device Gateway for monitoring sensor devices.

## Major Components:
### Sensors/ Simulator
Actual Sensors posting temperature data on mqtt "data" topic. or
Simulator creates configurable number of fake devices that sends data every minute to the gateway.
### Monitor 
Listens to all the devices data on mqtt "data" topic and builds device statistics. These stats can be queried via the CLI supported over the mqtt "command" topic. "command" topic.
### CLI 
Handles command request /response to/from monitor to gather device statistics, on mqtt "command" topic.
### MQTT Broker 
Handles all MQTT communication  between CLI, Devices (simulator) and the Monitor.
### Connector(s)
[To be implemented]
To add other devices protocols, a per protocol device connector component would be required. This connector will parse protocol specific device data to post the same on mqtt "data" topic.
Keeper, subscribes to all data MQTT communication and feed run time sensor data streams in to a data store.
### Ruler
[To be implemented]
Rules engine toapply basic actions on incoming device data stream.

### Keeper
[To be implemented]
Responsible for storing all device data, derived streams to data store locally or at remote.

### Analyzer
[To be implemented]
Analyzes incoming data streams to  generate new derived streams as needed for business logic.


## Installation

### Prerequisites:-
Ubuntu
Scons
Paho-MQTT c and cpp libraries and python packages.
build essentials
Mosquitto MQTT broker
Python
Docker 

### Installation Steps 
#### Build the Docker Image:-
docker build -t gateway:v1 .

#### Run the docker image
docker run  -it gateway:v1  /bin/bash

#### Start Message broker, device simulator and  gateway monitor services.
sh startup.sh

#### To see message broker+ monitor service logs 
tail -f nohup.log

#### Run CLI to interact with the monitor gateway
CLI Usage:-
                python3 cli.py listAllDevices
                python3 cli.py getDeviceInfo {deviceName}
                python3 cli.py getTotalMessageCount )

                Note: refer deviceName from listAlldevices commands.


### Usage:- (refer startup.sh)
1. Run MQTT Broker (mosquitto)
2. Run Simulator to generate device traffic (simulator/simulator.py)
3. Run monitor (monitor/monitor)
4. Use CLI to observe device statistics developing from device traffic. (cli/cli.py)