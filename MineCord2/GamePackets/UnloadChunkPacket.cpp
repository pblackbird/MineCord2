#include "UnloadChunkPacket.h"

void UnloadChunkPacket::Build(Buffer& dest) {
	PKT_BEGIN(UNLOAD_CHUNK_PACKETID);

	buff.writeInt32_BE(x);
	buff.writeInt32_BE(z);

	PKT_END();
}
