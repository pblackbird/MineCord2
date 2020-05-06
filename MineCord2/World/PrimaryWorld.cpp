#include "PrimaryWorld.h"

PrimaryWorld* PrimaryWorld::pSingleton;

PrimaryWorld::PrimaryWorld() : BaseWorld() {
	tickRate = 20;
}

void PrimaryWorld::Tick() {
	BaseWorld::Tick();
}
