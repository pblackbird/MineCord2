#include "LoginState.h"
#include "../Packets/SetCompressionPacket.h"
#include "../Packets/LoginStartPacket.h"
#include "../Packets/LoginSuccessPacket.h"
#include "../GamePackets/JoinGamePacket.h"
#include "../Utl.h"
#include "../World/PrimaryWorld.h"
#include "../Network/NetConfig.h"

void LoginState::Process(MinecraftNetworkClient* client, BaseNetPacket& packet) {
	Logger logger("Auth");

	if (packet.packetId != 0) {
		return;
	}

	const auto loginRequest = packet.Cast<LoginStartPacket>();

	logger.Info("Player set username = %s", loginRequest.playerName.c_str());

	client->SetUsername(loginRequest.playerName);

	std::string uuid = Utl::GenerateUUID();
	if (!uuid.length()) {
		client->Disconnect();
		return;
	}

	SetCompressionPacket setCompression;
	setCompression.maxUncompressedSize = MAX_UNCOMPRESSED_SIZE;

	client->Invoke(setCompression);

	LoginSuccessPacket resp;
	resp.playerName = loginRequest.playerName;
	resp.uuid = uuid;

	client->Invoke(resp);

	PrimaryWorld::GetInstance()->AddPlayer(
		client,
		loginRequest.playerName,
		uuid
	);

	client->SwitchState(ClientState::PLAY);
}
