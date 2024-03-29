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

ssize_t Utl::GetFileSize(const std::string& path) {
	struct stat fileStat;

	int fd = open(path.c_str(), O_RDONLY);

	if (fd < 0) {
		return -1;
	}

	if (fstat(fd, &fileStat) < 0) {
		return -1;
	}

	close(fd);

	return fileStat.st_size;
}

bool Utl::Decompress(std::vector<uint8_t>& in, std::vector<uint8_t>& out) {
	z_stream stream;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.next_in = in.data();
	stream.avail_in = (uInt)in.size();

	if (inflateInit2(&stream, 47) != Z_OK) {
		return false;
	}

	int zlibResult = Z_OK;
	int len = 0;

	do {
		out.resize(len + INFLATE_CHUNK_SIZE);

		stream.avail_out = INFLATE_CHUNK_SIZE;
		stream.next_out = out.data() + len;
		
		switch ((zlibResult = inflate(&stream, Z_NO_FLUSH))) {
			case Z_MEM_ERROR: 
				return false;
				break;
			case Z_DATA_ERROR:
				return false;
				break;
			default:
				len += INFLATE_CHUNK_SIZE - stream.avail_out;
		}

	} while (stream.avail_out == 0);

	inflateEnd(&stream);

	return true;
}

bool Utl::Compress(std::vector<uint8_t>& in, std::vector<uint8_t>& out, CompressionMethod method) {
	z_stream stream;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.next_in = in.data();
	stream.avail_in = (uInt)in.size();

	int windowSizeInBits = 15;

	if (method == CompressionMethod::GZIP) {
		windowSizeInBits += 16;
	}

	if (deflateInit2(
		&stream, 
		Z_DEFAULT_COMPRESSION,
		Z_DEFLATED,
		windowSizeInBits,
		8,
		Z_DEFAULT_STRATEGY
	) != Z_OK) {
		return false;
	}

	int len = 0;

	do {
		out.resize(len + INFLATE_CHUNK_SIZE);

		stream.avail_out = INFLATE_CHUNK_SIZE;
		stream.next_out = out.data() + len;

		if (deflate(&stream, Z_FINISH) == Z_STREAM_ERROR) {
			return false;
		}

		len += INFLATE_CHUNK_SIZE - stream.avail_out;

	} while (stream.avail_out == 0);

	deflateEnd(&stream);

	return true;
}

std::string Utl::GenerateUUID() {
	Logger logger("UUID generator");

	uint8_t uuid[37];
	bzero(uuid, 37);
	bool success = ReadFileOnceSync("/proc/sys/kernel/random/uuid", uuid, 36);

	if (!success) {
		logger.Error("Unable to generate UUID. ReadFileOnceSync() failed: %i", errno);
		return "";
	}

	return std::string((char*)uuid);
}

bool Utl::ReadFileOnceSync(std::string path, uint8_t* pBuffer, ssize_t size) {
	FILE* f = fopen(path.c_str(), "rb");

	if (!f) {
		return false;
	}

	size_t result = fread(pBuffer, size, 1, f);
	fclose(f);

	if (!result) {
		return false;
	}

	return true;
}
