#include "ChunkDataPacket.h"

void ChunkDataPacket::Build(Buffer& dest) {
	packetId = CHUNK_DATA_PACKETID;
	
	chunk.Serialize(buff);

	PKT_END();
}
