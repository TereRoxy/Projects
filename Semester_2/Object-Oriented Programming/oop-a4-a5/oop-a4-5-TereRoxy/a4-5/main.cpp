#include "UI.h"
#include "Tests.h"
#include <crtdbg.h>

int main() {
	{
		runAllTests();
	}
	{
		Repository eventRepo, userRepo;
		eventRepo.load_events();
		Service service{ eventRepo, userRepo };
		UI ui{ service };
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}