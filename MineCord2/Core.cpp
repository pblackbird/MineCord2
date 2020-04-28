#include "Core.h"
#include "States/StatesBindings.h"
#include "World/PrimaryWorld.h"

void Core::ShowWelcomeMessage() {
	logger.Info(L"Welcome to MineCord v%ls", VERSION);
}

void Core::Boot() {
	logger.SetTag(L"Core");
	logger.Info(L"Starting Core ...");

	StatesBindings::GetInstance()->Fill();

	const auto world = PrimaryWorld::GetInstance();
	world->Run();

	const auto tcpServer = TCPServer::GetInstance();
	tcpServer->Start(25565);
}

void Core::PlugAndPlay() {
	ShowWelcomeMessage();
	Boot();
}
