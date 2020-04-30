#pragma once

#include "VERSION.h"
#include "Logger.h"
#include "Network/TCPClient.h"
#include "Network/TCPServer.h"

struct CmdArg {
	std::string name, value;
};

class Core {
private:
	Logger logger;
	std::vector<CmdArg> cmdLine;

	static Core* pSingleton;

private:
	void ShowWelcomeMessage();
	void Boot();
	void Test();

	void ParseCmdLine(int argc, char* argv[]);
	
public:
	static Core* GetInstance();

	bool GetCommandLineArgument(const std::string&& name, std::string& result);
	bool HasCmdArg(const std::string& name);

	void PlugAndPlay(int argc, char* argv[]);
};

