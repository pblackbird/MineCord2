#pragma once

#include <cstdint>

#define AIR_BLOCK Block(0)

class Block {
public:
	int16_t palette;

public:
	Block() {};
	Block(int16_t plt) : palette(plt) {};
};