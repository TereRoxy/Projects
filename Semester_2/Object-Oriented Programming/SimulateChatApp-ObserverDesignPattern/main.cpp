#include "Seminar7.h"
#include "ChatSession.h"
#include "ChatWindow.h"
#include "User.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	ChatSession chatSession{};

	User* u1 = new User{ "John", "john123" };
	User* u2 = new User{ "Alice", "alice123" };
	User* u3 = new User{ "Bob", "bob123" };
	User* u4 = new User{ "Charlie", "charlie123" };

	ChatWindow* w1 = new ChatWindow{ chatSession, u1 };
	ChatWindow* w2 = new ChatWindow{ chatSession, u2 };
	ChatWindow* w3 = new ChatWindow{ chatSession, u3 };
	ChatWindow* w4 = new ChatWindow{ chatSession, u4 };
	
	chatSession.addObserver(w1);
	chatSession.addObserver(w2);
	chatSession.addObserver(w3);
	chatSession.addObserver(w4);
    
	w1->show();
	w2->show();
	w3->show();

    return a.exec();
}
