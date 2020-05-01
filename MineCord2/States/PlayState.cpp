#include "PlayState.h"
#include "../World/PrimaryWorld.h"

void PlayState::Process(MinecraftNetworkClient* client, BaseNetPacket& packet) {
	const auto player = PrimaryWorld::GetInstance()->GetPlayerByNetworkClientId(
		client->GetNetID()
	);

	if (!player) {
		return;
	}

	Buffer buf = packet.GetBuffer();
	buf.setReadOffset(0);

	if (!PacketUtils::ReadCompressed(buf, packet)) {
		return;
	}

	player->OnMsg(packet);
}
