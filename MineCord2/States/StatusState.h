#pragma once

#include "BaseClientState.h"

class StatusState : public BaseClientState {
public:
	void Process(MinecraftNetworkClient* client, BaseNetPacket& packet) override;
};
