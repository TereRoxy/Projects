#include "Validator.h"

using namespace std;

bool DateValidator::validate(const std::string& date) const {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
		throw ValidationException("Invalid date format");
		return false;
	}
	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));
	if (month < 1 || month > 12) {
		throw ValidationException("Invalid month");
		return false;
	}
	if (day < 1 || day > 31) {
		throw ValidationException("Invalid day");
		return false;
	}
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			if (day > 29) {
				throw ValidationException("Invalid day");
				return false;
			}
		}
		else {
			if (day > 28) {
				throw ValidationException("Invalid day");
				return false;
			}
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) {
			throw ValidationException("Invalid day");
			return false;
		}
	}
	return true;
}

bool TimeValidator::validate(const std::string& time) const {
	if (time.length() != 5 || time[2] != ':') {
		throw ValidationException("Invalid time format");
		return false;
	}
	int hour = std::stoi(time.substr(0, 2));
	int minute = std::stoi(time.substr(3, 2));
	if (hour < 0 || hour > 23) {
		throw ValidationException("Invalid hour");
		return false;
	}
	if (minute < 0 || minute > 59) {
		throw ValidationException("Invalid minute");
		return false;
	}
	return true;
}

bool LinkValidator::validate(const std::string& link) const {
	if (link.empty()) {
		throw ValidationException("Link cannot be empty");
		return false;
	}
	return true;
}

bool EventValidator::validateEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, const std::string& link, const int nop) const {
	DateValidator dateValidator;
	TimeValidator timeValidator;
	LinkValidator linkValidator;
	return dateValidator.validate(date) && timeValidator.validate(time) && linkValidator.validate(link);
}