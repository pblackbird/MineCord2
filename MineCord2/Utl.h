#pragma once

#include <string>
#include <vector>
#include <zlib.h>
#include <strings.h>

#include "Logger.h"

#define INFLATE_CHUNK_SIZE 4096

enum class CompressionMethod {
	GZIP,
	INFLATE
};

namespace Utl {
	std::string GenerateUUID();
	bool ReadFileOnceSync(std::string path, uint8_t* pBuffer, ssize_t size);

	bool IsBitSet(int val, int bitPosition);
	void SetBit(int& val, int bitPosition);

	ssize_t GetFileSize(const std::string& path);

	bool Decompress(std::vector<uint8_t>& in, std::vector<uint8_t>& out);
	bool Compress(std::vector<uint8_t>& in, std::vector<uint8_t>& out, CompressionMethod method);
}