#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Estate.h"
#include "ui.h"
#include "Controller.h"
#include "Repository.h"
#include "Tests.h"


int main()
{
	/**/
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	/**/

	test_all();

	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	
	Repository* repo = createRepository();
	Controller* ctrl = createRepoController(repo, undoStack, redoStack);
	UI* service = createUI(ctrl);
	
	loadEstates(getRepo(service->repoController));

	print_menu();
	int ok = select_option(service);
	while (ok)
	{
		print_menu();
		ok = select_option(service);
	}
	
	destroyUI(service);
	
	int mem_leak = _CrtDumpMemoryLeaks();
	if (mem_leak)
		printf("Oops! There are memory leaks");
	else
		printf("Yey! No memory leaks reported");
	return 0;
}