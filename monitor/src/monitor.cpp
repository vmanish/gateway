#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <sstream>
#include "mqtt/client.h"
#include "device.hpp"

#include "parseJson.hpp"

using namespace std;
using namespace std::chrono;

const string SERVER_ADDRESS	{ "tcp://localhost:1883" };
const string CLIENT_ID		{ "monitor" };

mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);


int publishCommandResponse(string  response)
{

	try {
        std::cout << "\nSending response..." << flush ;
        auto pubmsg = mqtt::make_message("command", response);
        pubmsg->set_qos(1);
        cli.publish(pubmsg);
        std::cout << "...done..." << endl;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc.what() <<  endl;
	}
	return 0;
}



/////////////////////////////////////////////////////////////////////////////

vector<Device *> Device::_list;
int Device::totalMsgCount = 0;

int main(int argc, char* argv[])
{

	auto connOpts = mqtt::connect_options_builder()
		.keep_alive_interval(seconds(30))
		 .finalize();

	const vector<string> TOPICS {  "command", "data" };
	const vector<int> QOS { 2, 1 };

	try {
		cout << "Connecting to the MQTT server..." << flush;
		mqtt::connect_response rsp = cli.connect(connOpts);

	    cout << "Subscribing to topics..." << std::flush;
	    cli.subscribe(TOPICS, QOS);
		
		// Consume messages

		while (true) {
			auto msg = cli.consume_message();

			if (msg) {
				cout << msg->get_topic() << ": " << msg->to_string() << endl;
				if(msg->get_topic() == "data") {
					parseJsonDeviceData(msg->get_payload());
				}
				else if (msg->get_topic() == "command") {
					parseJsonCommand(msg->get_payload());
				}
			}
			else if (!cli.is_connected()) {
				cout << "Lost connection" << endl;
				while (!cli.is_connected()) {
					this_thread::sleep_for(milliseconds(250));
				}
				cout << "Re-established connection" << endl;
			}
		}

		// Disconnect

		cout << "\nDisconnecting from the MQTT server..." << flush;
		cli.disconnect();
		cout << "OK" << endl;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc.what() << "main failed"  << endl;
	}

 	return 0;
}

