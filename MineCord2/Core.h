#pragma once

#include "VERSION.h"
#include "Logger.h"
#include "Network/TCPClient.h"
#include "Network/TCPServer.h"

class Core {
private:
	Logger logger;

private:
	void ShowWelcomeMessage();
	void Boot();
	
public:
	void PlugAndPlay();
};

