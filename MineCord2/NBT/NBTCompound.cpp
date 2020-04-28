#include "NBTCompound.h"

void NBTCompound::Write(Buffer& dest) {
	NBT::Write(dest);

	for (auto tag : tags) {
		tag.Write(dest);
	}

	dest.writeUInt8(0x00); // TAG_End
}

void NBTCompound::Read(Buffer& src) {
	NBT::Read(src);

	NBTDataType lastTagType;

	do {
		NBT currentNBT;
		currentNBT.Read(src);

		lastTagType = currentNBT.type;

		tags.push_back(currentNBT);
	} while (lastTagType != NBTDataType::TAG_End);
}
