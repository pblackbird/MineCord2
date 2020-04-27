#pragma once

#include "BaseClientState.h"

class PlayState : public BaseClientState {
public:
	virtual void Process(MinecraftNetworkClient* client, BaseNetPacket& packet) override;
};