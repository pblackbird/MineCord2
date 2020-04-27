#pragma once

#include <string>
#include <thread>

#include "../Entities/Entity.h"
#include "../Logger.h"

class BaseWorld {
protected:
	bool isWorldActive = true;

	std::thread worldTickThread;

	std::wstring name;
	std::vector<Entity*> pEntities;

	int64_t tickRate = 120;

	Logger logger;

	virtual void Tick();

public:
	BaseWorld() {
		logger.SetTag(L"World");
	}

	void TickLoop();

	void SetTickRate(uint64_t tps) {
		tickRate = tps;
	}

	uint64_t GetTickRate() {
		return tickRate;
	}

	void Run();
};