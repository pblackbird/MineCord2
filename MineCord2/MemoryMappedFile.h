#pragma once

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string>

class MemoryMappedFile {
private:
	int fd;

	ssize_t size;
	void* pointer = nullptr;

	std::string path;

public:
	MemoryMappedFile(const std::string& path);
	~MemoryMappedFile();

	void* GetPointer() {
		return pointer;
	}

	void SetSize(ssize_t newSize) {
		size = newSize;
	}

	ssize_t GetSize() {
		return size;
	}

	bool Remap();
	bool Open(ssize_t ssize = 0);
};