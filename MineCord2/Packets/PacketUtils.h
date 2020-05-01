#pragma once

#include <cassert>

#include "../Packets/BaseNetPacket.h"
#include "../ThirdParty/BufferedIO.h"
#include "../MinecraftTypes.h"

class BaseNetPacket;

namespace PacketUtils {
	void Write(Buffer& in, Buffer& out, int pktId, bool isCompressed = true, size_t pktIdLen = 1);
	BaseNetPacket ReadCompressed(Buffer& buff);
}