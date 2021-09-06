
#ifndef CLI_HPP_
#define CLI_HPP_

int publishCommandResponse(string  response);
int processCommand (string command , string param);
int handleCommand(std::string response);
int handleDeviceData(std::string response);
int parseJson(string & msg, string key[], string value[]);

#endif

