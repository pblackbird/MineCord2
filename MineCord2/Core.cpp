#include "Core.h"
#include "States/StatesBindings.h"
#include "World/PrimaryWorld.h"

#include "NBT/Tests/NBT_Test.h"

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

void Core::Test() {
	std::string nbtFilePath;
	if (!GetCommandLineArgument("nbtfile", nbtFilePath)) {
		return;
	}

	TestNBT(nbtFilePath);
}

void Core::ParseCmdLine(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		std::string currentUnit(argv[i]);
		
		if (currentUnit[0] != '-') {
			continue;
		}

		currentUnit.erase(currentUnit.begin());

		CmdArg arg;
		arg.name = currentUnit;

		for (int j = i + 1; j < argc; j++) {
			std::string currentArgUnit(argv[j]);
			
			if (currentArgUnit[0] == '-') {
				break;
			}

			arg.value += currentArgUnit;
		}

		cmdLine.push_back(arg);
	}
}

bool Core::GetCommandLineArgument(const std::string&& name, std::string& result) {
	for (const auto cmd : cmdLine) {
		if (cmd.name == name) {
			result = cmd.value;
			return true;
		}
	}

	return false;
}

bool Core::HasCmdArg(const std::string& name) {
	std::string _temp;
	return GetCommandLineArgument(std::move(name), _temp);
}

void Core::PlugAndPlay(int argc, char* argv[]) {
	ParseCmdLine(argc, argv);

	if (HasCmdArg("test")) {
		Test();
		return;
	}

	ShowWelcomeMessage();
	Boot();
}
