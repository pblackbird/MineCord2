#pragma once

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string>

class MemoryMappedFile {
private:
	int fd;

	ssize_t size;
	void* pointer;

	std::string path;

public:
	MemoryMappedFile(const std::string& path);
	~MemoryMappedFile();

	void* GetPointer() {
		return pointer;
	}

	bool Remap();
	bool Open(size_t size = 0);
};