#include "PrimaryWorld.h"

PrimaryWorld* PrimaryWorld::pSingleton;

PrimaryWorld::PrimaryWorld() : BaseWorld() {
	tickRate = 60;
}

void PrimaryWorld::Tick() {
	BaseWorld::Tick();
}
