#include "ChatWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>

ChatWindow::ChatWindow(ChatSession& chatS, User* u, QWidget* parent) : chatSession{ chatS }, user{ u }
{
	setupUi();
}

void ChatWindow::setupUi()
{
	QVBoxLayout* layout = new QVBoxLayout{ this };
	list = new QListWidget{};
	for (auto m : chatSession.getMessages())
	{
		QListWidgetItem* item = new QListWidgetItem{ m->getMessage().c_str() };
		list->addItem(item);
	}
	QHBoxLayout* hlayout = new QHBoxLayout{};
	layout->addWidget(list);
	edit = new QLineEdit{};
	hlayout->addWidget(edit);
	send = new QPushButton{ "Send" };
	hlayout->addWidget(send);
	layout->addLayout(hlayout);

	this->setWindowTitle(user->getName().c_str());
	QObject::connect(send, &QPushButton::clicked, this, &ChatWindow::handleSendMessage);
}

void ChatWindow::update()
{
	list->clear();
	std::vector < UserMessage* > messages = chatSession.getMessages();
	for (auto m : messages)
	{
		QListWidgetItem* item = new QListWidgetItem{ m->getMessage().c_str() };
		list->addItem(item);
	}
}

void ChatWindow::sendMessage()
{
	std::string message = edit->text().toStdString();
	edit->clear();

	if (message.empty())
		return;
	
	UserMessage* m = new UserMessage{ message, user->getName() };
	chatSession.addMessage(m);
	chatSession.notifyObservers();
}