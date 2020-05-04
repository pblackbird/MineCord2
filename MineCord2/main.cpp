#include <cstdio>
#include "Core.h"

int main(int argc, char* argv[]) {
	Core *core = Core::GetInstance();
	core->PlugAndPlay(argc, argv);
}