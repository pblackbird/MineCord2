#include "LoginState.h"
#include "../Packets/LoginStartPacket.h"
#include "../Packets/LoginSuccessPacket.h"
#include "../Utl.h"

void LoginState::Process(MinecraftNetworkClient* client, BaseNetPacket& packet) {
	Logger logger(L"Auth");

	if (packet.packetId != 0) {
		return;
	}

	const auto loginRequest = packet.Cast<LoginStartPacket>();
	std::wstring wPlayerName(loginRequest.playerName.begin(), loginRequest.playerName.end());

	logger.Info(L"Player set username = %ls", wPlayerName.c_str());

	client->SetUsername(std::move(wPlayerName));

	std::string uuid = Utl::GenerateUUID();
	if (!uuid.length()) {
		client->Disconnect();
		return;
	}

	LoginSuccessPacket resp;
	resp.playerName = loginRequest.playerName;
	resp.uuid = uuid;

	client->Invoke(resp);
	client->SwitchState(ClientState::PLAY);
}
