#include "UI.h"
#include "Tests.h"
#include <crtdbg.h>

int main() {
	{
		runAllTests();
	}
	{
		FileFormat* format = new TextFile("events.txt");
		Repository eventRepo(format), userRepo;
		//eventRepo.load_events();
		eventRepo.load_from_file();
		Service service{ eventRepo, userRepo };
		UI ui{ service };
		ui.run();
		eventRepo.save_to_file();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}