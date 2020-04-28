#include "PlayState.h"
#include "../World/PrimaryWorld.h"

void PlayState::Process(MinecraftNetworkClient* client, BaseNetPacket& packet) {
	const auto player = PrimaryWorld::GetInstance()->GetPlayerByNetworkClientId(
		client->GetNetID()
	);

	if (!player) {
		return;
	}

	player->OnMsg(packet);
}
