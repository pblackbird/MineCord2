#pragma once

#include "../Transformable.h"
#include "../ThirdParty/BufferedIO.h"
#include "Chunk.h"

/*
	Map manager that works with memory mapped map-data file will be implemented in future.
*/
class IMapManager {
public:
	// Serialize chunk at position
	virtual void SerializeChunkAtPosition(Point3D pos, Buffer& dest) = 0;
};