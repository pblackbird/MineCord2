#pragma once

#include "../Packets/BaseNetPacket.h"

class JoinGamePacket : public BaseNetPacket {
public:
	int entityId;
	GameMode gamemode;
	Dimension dimension;
	uint8_t maxPlayers;
	std::string worldType;
	int viewDistance;
	bool isDebug;

public:
	virtual void Build(Buffer& dest) override;
};