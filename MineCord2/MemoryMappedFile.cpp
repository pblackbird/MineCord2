#include "MemoryMappedFile.h"
#include "Utl.h"

MemoryMappedFile::MemoryMappedFile(const std::string& path) {
	this->path = path;
}

MemoryMappedFile::~MemoryMappedFile() {
	munmap(pointer, size);
	close(fd);
}

bool MemoryMappedFile::Remap() {
	if (pointer == nullptr) {
		pointer = mmap64(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	} else {
		pointer = mremap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	}
	
	return pointer != MAP_FAILED;
}

bool MemoryMappedFile::Open(ssize_t size) {
	if (size == 0) {
		size = Utl::GetFileSize(path);

		if (size == -1) {
			return false;
		}
	} else {
		this->size = size;
	}

	fd = open(path.c_str(), O_RDWR);

	if (fd < 0) {
		return false;
	}

	return Remap();
}
