#pragma once
#include <string>
#include <exception>

class RepositoryException : public std::exception {
private:
	std::string message;
public:
	RepositoryException(const std::string& msg) : message{ msg } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class ServiceException : public std::exception {
private:
	std::string message;
public:
	ServiceException(const std::string& msg) : message{ msg } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class ValidationException : public std::exception {
private:
	std::string message;
public:
	ValidationException(const std::string& msg) : message{ msg } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};
