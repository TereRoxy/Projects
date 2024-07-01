#pragma once
#include <string>

class User
{
private:
	std::string name;
	std::string uniqueUserName;

public:
	User(std::string name, std::string uniqueUserName) : name(name), uniqueUserName(uniqueUserName) {}
	std::string getName() { return name; }
	std::string getUniqueUserName() { return uniqueUserName; }
};