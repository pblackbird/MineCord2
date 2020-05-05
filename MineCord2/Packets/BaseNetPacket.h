#pragma once

#include "../Network/MinecraftNetworkClient.h"
#include "../ThirdParty/BufferedIO.h"
#include "../MinecraftTypes.h"
#include "../VERSION.h"
#include "PacketUtils.h"

#define PKT_END() \
	PacketUtils::Write(buff, dest, packetId, isCompressed);

#define PKT_BEGIN(id) \
	buff.clear(); \
	packetId = id;

class BaseNetPacket {
protected:
	Buffer buff;
	bool isCompressed = true;

public:
	int length, uncompressedLength;
	int packetId;

	int packetIdLen;

public:
	BaseNetPacket() {
		isCompressed = false;
	}

	template<class T>
	T Cast() {
		T pkt;
		std::vector<uint8_t> src = buff.getBuffer();
		pkt.Parse(src);

		return pkt;
	}

	void SetCompressed(bool value) {
		isCompressed = value;
	}

	virtual void Parse(std::vector<uint8_t>& src);
	virtual void Build(Buffer& dest) {
		throw new std::runtime_error("Build is not implemented");
	}

	void SetBuffer(Buffer buffer) {
		buff = buffer;
	}

	Buffer GetBuffer() {
		return buff;
	}
};

