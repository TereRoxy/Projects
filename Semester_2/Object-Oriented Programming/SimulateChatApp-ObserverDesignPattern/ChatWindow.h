#pragma once
#include <QWidget>
#include "Observer.h"
#include "ChatSession.h"
#include "User.h"
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>

class ChatWindow : public QWidget, public Observer
{
private:
	ChatSession& chatSession;
	User* user;

private slots:
	void handleSendMessage() { sendMessage(); }
	
public:
	ChatWindow(ChatSession& chatS, User* user, QWidget* parent = nullptr);
	void setupUi();
	void update() override;
	void sendMessage();
	~ChatWindow() {};

private:
	QPushButton* send;
	QLineEdit* edit;
	QListWidget* list;
};