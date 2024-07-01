#pragma once
#include <vector>
#include "UserMessage.h"
#include "Subject.h"


class ChatSession : public Subject
{
	std::vector<UserMessage*>messages;
	
public:
	ChatSession() {};
	void addMessage(UserMessage* message) { messages.push_back(message); };
	std::vector<UserMessage*> getMessages() { return messages; };
	~ChatSession() {};
};