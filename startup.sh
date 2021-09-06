#!/bin/bash

#start message broker
nohup mosquitto & 

#kick off 25 fake sensor devices
nohup python3 /home/gateway/simulator/simulator.py 25 &   

#start gateway monitor
nohup /home/gateway/monitor/monitor & 

echo "Run python3 /home/gateway/cli/cli.py to peek & poke the gateway."
