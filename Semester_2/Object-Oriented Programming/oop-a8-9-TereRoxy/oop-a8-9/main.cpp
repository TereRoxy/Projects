#include "EventsManager.h"
#include "Tests.h"
#include "Service.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    
    /**/
    {
		runAllTests();
	}
	/*
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
    */
	
	FileFormat* format = new TextFile("events.txt");
	Repository eventRepo(format), userRepo;
	//eventRepo.load_events();
	eventRepo.load_from_file();
	Service service{ eventRepo, userRepo };
    
    QApplication a(argc, argv);
    EventsManager w;
	w.setService(&service);
    w.show();
	int res = a.exec();

	eventRepo.save_to_file();
	
    return res;
}
