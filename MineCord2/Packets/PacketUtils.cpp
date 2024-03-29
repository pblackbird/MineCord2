#include "PacketUtils.h"
#include "../Utl.h"
#include "../Network/NetConfig.h"

void SerializeUncompressedPacket(Buffer& in, Buffer& out, int pktId, size_t pktIdLen) {
	MinecraftTypes::WriteVarInt(out, (int)in.getBuffer().size() + (int)pktIdLen);
	MinecraftTypes::WriteVarInt(out, pktId);

	for (size_t i = 0; i < in.getBuffer().size(); i++) {
		out.writeUInt8(in.getBuffer().at(i));
	}
}

void PacketUtils::Write(Buffer& in, Buffer& out, int pktId, bool isCompressed, size_t pktIdLen) {
	if (!isCompressed) {
		SerializeUncompressedPacket(in, out, pktId, pktIdLen);
		return;
	}

	Buffer rawBodyBuffer;
	MinecraftTypes::WriteVarInt(rawBodyBuffer, pktId);
	for (const auto byte : in.getBuffer()) {
		rawBodyBuffer.writeUInt8(byte);
	}

	std::vector<uint8_t> outputBody, rawBody(rawBodyBuffer.getBuffer());

	Buffer compressedPacketHeader;

	int rawBodySize = 0;

	if (in.getBuffer().size() >= MAX_UNCOMPRESSED_SIZE) {
		rawBodySize = (int)in.getBuffer().size() + 1; // +1 for packet id length
		assert(Utl::Compress(rawBody, outputBody, CompressionMethod::INFLATE));
	} else {
		outputBody = rawBody;
	}

	int sizeOfDataLength = 0;
	Buffer dataLengthBuffer;

	MinecraftTypes::WriteVarInt(dataLengthBuffer, rawBodySize, &sizeOfDataLength);

	if (sizeOfDataLength == 0) {
		sizeOfDataLength = 1;
	}

	MinecraftTypes::WriteVarInt(out, sizeOfDataLength + (int)outputBody.size());

	for (const auto byte : dataLengthBuffer.getBuffer()) {
		out.writeUInt8(byte);
	}

	for (size_t i = 0; i < outputBody.size(); i++) {
		out.writeUInt8(outputBody.at(i));
	}
}

bool PacketUtils::ReadCompressed(Buffer& buff, BaseNetPacket& pktResult) {
	int length = MinecraftTypes::ReadVarInt(buff);
	int uncompressedLength = MinecraftTypes::ReadVarInt(buff);
	int packetId = 0;
	
	if (uncompressedLength == 0) {
		packetId = MinecraftTypes::ReadVarInt(buff);
	} else {
		std::vector<uint8_t> decompressed, compressed;

		for (int i = 0; i < uncompressedLength; i++) {
			compressed.push_back(buff.readUInt8());
		}

		if (!Utl::Decompress(compressed, decompressed)) {
			return false;
		}

		buff = Buffer(decompressed);
		packetId = MinecraftTypes::ReadVarInt(buff);
	}

	pktResult.packetId = packetId;
	pktResult.length = length;

	pktResult.SetBuffer(Buffer(buff));
	pktResult.SetCompressed(true);

	return true;
}
