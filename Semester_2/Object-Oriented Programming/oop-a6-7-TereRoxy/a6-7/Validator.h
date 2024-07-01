#pragma once
#include "Exceptions.h"
#include <iostream>
#include <string>

class Validator {
public:
	virtual bool validate(const std::string& input) const = 0;
};

class DateValidator : public Validator {
public:
	bool validate(const std::string& date) const override;
};

class TimeValidator : public Validator {
public:
	bool validate(const std::string& time) const override;
};

class LinkValidator : public Validator {
public:
	bool validate(const std::string& link) const override;
};

class EventValidator : public Validator {
public:
	bool validate(const std::string& eve) const override {
		return true;
	}
	bool validateEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& link, const int nop) const;
};