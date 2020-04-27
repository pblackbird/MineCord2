#pragma once

#include "../Packets/BaseNetPacket.h"
#include "../Network/MinecraftNetworkClient.h"

class MinecraftNetworkClient;
class BaseNetPacket;

class BaseClientState {
public:
	virtual void Process(MinecraftNetworkClient* client, BaseNetPacket& packet) = 0;
};