#pragma once

#include <string>
#include <vector>
#include <zlib.h>

#include "Logger.h"

#define INFLATE_CHUNK_SIZE 4096

static Logger logger(L"Utl");

namespace Utl {
	std::string GenerateUUID();
	bool ReadFileOnceSync(std::string path, uint8_t* pBuffer, ssize_t size);

	bool IsBitSet(int val, int bitPosition);
	void SetBit(int& val, int bitPosition);

	ssize_t GetFileSize(const std::string& path);

	bool Decompress(std::vector<uint8_t>& in, std::vector<uint8_t>& out);
}