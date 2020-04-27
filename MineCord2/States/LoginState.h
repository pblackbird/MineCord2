#pragma once

#include "BaseClientState.h"

class LoginState : public BaseClientState {
public:
	virtual void Process(MinecraftNetworkClient* client, BaseNetPacket& packet) override;
};