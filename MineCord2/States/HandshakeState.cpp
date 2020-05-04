#include "HandshakeState.h"
#include "../Packets/HandshakePacket.h"

void HandshakeState::Process(MinecraftNetworkClient* client, BaseNetPacket& packet) {
	Logger logger("Handshake");

	if (packet.packetId != 0x00) {
		return;
	}

	const auto pkt = packet.Cast<HandshakePacket>();

	logger.Info("Next state is %i | PROTOCOL[%i]", pkt.nextState, pkt.protocolVersion);
	
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
	switch (static_cast<ClientState>(pkt.nextState)) {
		case ClientState::STATUS:
			client->SwitchState(ClientState::STATUS);
			break;
		case ClientState::LOGIN:
			client->SwitchState(ClientState::LOGIN);
			break;
		case ClientState::PLAY:
			client->SwitchState(ClientState::PLAY);
			break;
	}
#pragma GCC diagnostic pop
}
