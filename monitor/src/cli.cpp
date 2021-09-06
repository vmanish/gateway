#include "device.hpp"
#include "cli.hpp"

int processCommand (string command , string param)
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
        string info;
        Device::getDeviceInfo(param, info);
        buffer << " \'data\' : ";
        buffer << info;
        buffer << " }";

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


int handleCommand(string msg)
{
    string key[] = {"request", "param"};
    string value[2];
    if(!parseJson(msg, key, value )) {
        processCommand (value[0] , value[1]);
    }
	return 0;
}

int handleDeviceData(string msg)
{
    string key[] = {"name", "temp"};
    string value[2];
    if(!parseJson(msg, key, value)) {
	    Device::updateMessage (value[0], value[1] );
    }
	return 0;
}

int parseJson(string & msg, string key[], string value[])
{
    std::stringstream ss(msg); //simulating an response stream
    const unsigned int BUFFERSIZE = 256;

    //temporary buffer
    char buffer[BUFFERSIZE];
    memset(buffer, 0, BUFFERSIZE * sizeof(char));

    //returnValue.first holds the variables name
    //returnValue.second holds the variables value
    std::pair<std::string, std::string> kv;

    //read until the opening bracket appears
    while(ss.peek() != '{')         
    {
        //ignore the { sign and go to next position
        ss.ignore();
    }
	int loop = 0;
    //get response values until the closing bracket appears
    while(ss.peek() != '}' )
    {
        //read until a opening variable quote sign appears
        ss.get(buffer, BUFFERSIZE, '\''); 

        //and ignore it (go to next position in stream)
        ss.ignore();

        //read variable token excluding the closing variable quote sign
        ss.get(buffer, BUFFERSIZE, '\'');
        //and ignore it (go to next position in stream)
        ss.ignore();
        //store the variable name
        kv.first = buffer;
		if(kv.first == "response")
		{
			return 1; //ignore
		}
        //read until opening value quote appears(skips the : sign)
        ss.get(buffer, BUFFERSIZE, '\'');

        //and ignore it (go to next position in stream)
        ss.ignore();

        //read value token excluding the closing value quote sign
        ss.get(buffer, BUFFERSIZE, '\'');
        //and ignore it (go to next position in stream)
        ss.ignore();
        //store the variable name
        kv.second = buffer;

		if(kv.first == key[0])
		{
			value[0] = kv.second;
		}
		else if(kv.first == key[1]) 
		{
			value[1] = kv.second;
		} 
		
    }
    return 0;
}