#ifndef DEVICE_HPP_
#define DEVICE_HPP_

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>

using namespace std;
using namespace std::chrono;


class Device {
private:
    string _name;
	string _latestMessage;
	int _messageCount;
	time_t _lastSeen;
public:
    static vector<Device *> _list;
	static int totalMsgCount;
    explicit Device(const string& S) : _name(S), _latestMessage(""), _messageCount(1), _lastSeen(time(0)) {  }

    static Device* add(const string& S);

	static Device * getDevice(const string& name, bool doCreate);

	static int updateMessage (string name, string temperature);

	static int listAllDevices(string & list);

    static int getDeviceInfo(string name, string & info);

};


#endif