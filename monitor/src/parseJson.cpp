#include "parseJson.hpp"


int parseJsonCommand(string response)
{
	string command;
	string param;
	std::stringstream ss(response); //simulating an response stream
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
			return 0; //ignore
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

		if(kv.first == "request")
		{
			command = kv.second;
		}
		else if(kv.first == "param") 
		{
			param = kv.second;
		} 
		
    }
	
	Device::processCommand (command , param);
	return 0;
}


int parseJsonDeviceData(string response)
{
	string deviceName;
	//string deviceTrigger;
	string deviceTemperature;

	std::stringstream ss(response); //simulating an response stream
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

		if(kv.first == "name")
		{
			deviceName = kv.second;
		}
		// else if(kv.first == "trigger") 
		// {
		// 	deviceTrigger = kv.second;
		// } 
		else if(kv.first == "temp") 
		{
			deviceTemperature = kv.second;
		}

    }

	Device::updateMessage (deviceName, deviceTemperature );
	return 0;
}