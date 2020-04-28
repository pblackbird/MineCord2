#include "NBTCompound.h"

void NBTCompound::Write(Buffer& dest) {
	NBT::Write(dest);

	for (auto tag : tags) {
		tag->Write(dest);
	}

	dest.writeUInt8(0x00); // TAG_End
}

void NBTCompound::Read(Buffer& src) {
	NBT::Read(src);

	NBTDataType lastTagType;

	do {
		NBT* pResult = NBT::ReadNBTSafely(src);

		if (!pResult) {
			break;
		}

		lastTagType = pResult->type;
		tags.push_back(pResult);
	} while (lastTagType != NBTDataType::TAG_End);
}

void NBTCompound::WalkTree(OnNBTWalkTree_t callback) {
	for (const auto tag : tags) {
		if (tag->type == NBTDataType::TAG_Compound) {
			((NBTCompound*)tag)->WalkTree(callback);
			continue;
		}

		callback(tag);
	}
}
