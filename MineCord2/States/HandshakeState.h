#pragma once

#include "BaseClientState.h"

class HandshakeState : public BaseClientState {
public:
	virtual void Process(MinecraftNetworkClient* client, BaseNetPacket& packet) override;
};