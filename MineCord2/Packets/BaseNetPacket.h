#pragma once

#include "../Network/MinecraftNetworkClient.h"
#include "../ThirdParty/BufferedIO.h"
#include "../MinecraftTypes.h"
#include "PacketUtils.h"

#define PKT_END() \
	PacketUtils::Write(buff, dest, packetId);

class BaseNetPacket {
protected:
	Buffer buff;

public:
	int length;
	int packetId;

	int packetIdLen;

public:
	template<class T>
	T Cast() {
		T pkt;
		std::vector<uint8_t> src = buff.getBuffer();
		pkt.Parse(src);

		return pkt;
	}

	virtual void Parse(std::vector<uint8_t>& src);
	virtual void Build(Buffer& dest) {
		throw new std::runtime_error("Build is not implemented");
	}
};

