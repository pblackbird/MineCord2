#pragma once

#include "../ThirdParty/BufferedIO.h"
#include "../MinecraftTypes.h"

namespace PacketUtils {
	void Write(Buffer& in, Buffer& out, int pktId, size_t pktIdLen = 1);
}