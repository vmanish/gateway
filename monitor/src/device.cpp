#include "device.hpp"

     Device* Device::add(const string& S) {
	    auto p = new Device(S);
        _list.push_back(p);
        return p;
    }

	 Device * Device::getDevice(const string& name, bool doCreate) {
		Device * found = NULL;
		for(auto const  dev : _list) {
			if( dev->_name  == name ) {
				found = dev;
				break;
			}
		}

		if ((found == NULL) && (doCreate == true)) {
			found = add(name);
		}
		return found;
	}


	 int Device::updateMessage (string name, string temperature)
	{

		Device::totalMsgCount++;
		Device * dev = 	Device::getDevice(name, true);
		if (dev != NULL) {
			dev->_lastSeen =  time(0);
			dev->_latestMessage = temperature;
			dev->_messageCount++;
		} else { 
			cout << "Failed to add new device XXXXX"<<endl; 
		}

		return 0;
	}

	 int Device::listAllDevices(string & list)
	{
		ostringstream buffer;
		int deviceCount=0;

		for(auto const  dev : _list) {
			if(deviceCount)
				buffer  << ", ";
			
			buffer << dev->_name;
			deviceCount++;
		}
		
		list = buffer.str();
		return deviceCount;

	}

	 int Device::processCommand (string command , string param)
	{
		ostringstream buffer;
		string response;
		buffer << "{ \'response\' : command=";
		buffer << command;
		buffer <<  " , ";
		if(command == "getTotalMessageCount")
		{
			buffer << " \'data\' : ";
			buffer <<  Device::totalMsgCount;
			buffer << " }";
		} else if (command == "getDeviceInfo") {
			Device *dev = Device::getDevice(param, false);
			if(dev == NULL) {
				buffer << "NotFound";
			}
			else {
				buffer << " \'data\' : ";
				buffer << "Name="<<dev->_name;
				buffer << " , ";
				buffer << "LastSeen="<<dev->_lastSeen;
				buffer << " , ";
				buffer << "LastMessage="<<dev->_latestMessage;
				buffer << " , ";
				buffer << "MessagesReceived="<<dev->_messageCount;
				buffer << " }";

			}

		} else if (command == "listAllDevices") {
			string list;
			int deviceCount = Device::listAllDevices(list);
			buffer << " \'data\' : ";
			buffer << "TotalDevices = ";
			buffer << deviceCount ;
			buffer << " , List[]=";
			buffer << list;
			buffer << " }";

		}
		response = buffer.str();
		publishCommandResponse( response);

		return 0;

	}

