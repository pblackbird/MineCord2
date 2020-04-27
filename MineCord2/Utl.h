#pragma once

#include <string>
#include "Logger.h"

static Logger logger(L"Utl");

namespace Utl {
	std::string GenerateUUID();
	bool ReadFileOnceSync(std::string path, uint8_t* pBuffer, ssize_t size);

	bool IsBitSet(int val, int bitPosition);
	void SetBit(int& val, int bitPosition);
}