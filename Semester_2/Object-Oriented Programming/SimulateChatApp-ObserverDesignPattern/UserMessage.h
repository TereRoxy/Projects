#pragma once
#include <string>

class UserMessage {
private:
	std::string message;
	std::string user;

public:
	UserMessage(std::string message, std::string user) : message(message), user(user) {}
	std::string getMessage() { return user + ": " + message; }
	std::string getUser() { return user; }
};