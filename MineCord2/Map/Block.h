#pragma once

#include <cstdint>

#define AIR_BLOCK Block(0)

class Block {
public:
	int64_t palette;

public:
	Block() {};
	Block(int64_t plt) : palette(plt) {};
};