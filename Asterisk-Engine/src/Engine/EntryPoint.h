
#include "Engine/Engine.h"

extern asterisk::Engine* asterisk::Create();

#ifdef PLATFORM_WINDOWS

int main() {
	asterisk::Engine* engine = asterisk::Create();
	engine->Run();
	delete engine;

	return 0;
}

#endif