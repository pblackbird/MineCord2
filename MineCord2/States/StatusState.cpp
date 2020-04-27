#include "StatusState.h"
#include "../Packets/StatusPacket.h"
#include "../Packets/PingPacket.h"

void SendTestMOTD(MinecraftNetworkClient* client) {
	std::string status = "{\"version\":{\"name\":\"Nya :3\",\"protocol\":498},\"players\":{\"max\":100,\"online\":0,\"sample\":[]},\"description\":{\"text\":\"MineCord C++ Server\"}}";

	StatusPacket statusResponse;
	statusResponse.json = status;
	
	client->Invoke(statusResponse);
}

void StatusState::Process(MinecraftNetworkClient* client, BaseNetPacket& packet) {
	Logger logger(L"Status state");

	switch (packet.packetId) {
		case 0x00: {
			logger.Info(L"Sending motd ...");

			SendTestMOTD(client);
			break;
		}

		case 0x01: {
			logger.Info(L"Sending pong ...");

			const auto pingRequest = packet.Cast<PingPacket>();

			PingPacket pongPacket;
			pongPacket.payload = pingRequest.payload;

			client->Invoke(pongPacket);

			break;
		}
	}
}
