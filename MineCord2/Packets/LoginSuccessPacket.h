#pragma once

#include "BaseNetPacket.h"

class LoginSuccessPacket : public BaseNetPacket {
public:
	std::string playerName;
	std::string uuid;

public:
	virtual void Build(Buffer& dest) override;
};