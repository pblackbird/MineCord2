#include "Utl.h"

bool Utl::IsBitSet(int val, int bitPosition) {
	return (val >> bitPosition) & 1;
}

void Utl::SetBit(int& val, int bitPosition) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

	if (!IsBitSet(val, bitPosition))
		val |= 1UL << bitPosition;
	else
		val &= ~(1UL << bitPosition);
#pragma GCC diagnostic pop
}

std::string Utl::GenerateUUID() {
	uint8_t uuid[36];
	bool success = ReadFileOnceSync("/proc/sys/kernel/random/uuid", uuid, 36);

	if (!success) {
		logger.Error(L"Unable to generate UUID. ReadFileOnceSync() failed: %i", errno);
		return "";
	}

	return std::string((char*)uuid);
}

bool Utl::ReadFileOnceSync(std::string path, uint8_t* pBuffer, ssize_t size) {
	FILE* f = fopen(path.c_str(), "rb");
	size_t result = fread(pBuffer, size, 1, f);
	fclose(f);

	if (!result) {
		return false;
	}

	return true;
}
