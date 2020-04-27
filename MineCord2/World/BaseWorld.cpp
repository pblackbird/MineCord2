#include "BaseWorld.h"

void BaseWorld::Tick() {
	for (const auto entity : pEntities) {
		entity->OnTick();
	}
}

void BaseWorld::TickLoop() {
	auto tickTimerStart = std::chrono::high_resolution_clock::now();
	ssize_t currentTPS = 0;

	while (isWorldActive) {
		if (currentTPS <= tickRate) {
			Tick();
			currentTPS++;
		}

		const auto tickTimerFinish = std::chrono::high_resolution_clock::now();
		const auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
			tickTimerFinish - tickTimerStart
		).count();

		if (elapsed == 1) {
			if (currentTPS < tickRate) {
				logger.Warning(L"Current TPS (%llu) is less than %llu", currentTPS, tickRate);
			}

			currentTPS = 0;
			tickTimerStart = std::chrono::high_resolution_clock::now();
		}
	}
}

void _threadEntry(BaseWorld* pWorld) {
	pWorld->TickLoop();
}

void BaseWorld::Run() {
	worldTickThread = std::thread(_threadEntry, this);
}
