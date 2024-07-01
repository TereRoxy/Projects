#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Event.h"

class FileFormat {
protected:
	std::string filename;
public:
	FileFormat(const std::string& filename) : filename{ filename } {}
	virtual std::vector<Event> loadFromFile() = 0;
    virtual void saveToFile(const std::vector<Event>& events) = 0;
    virtual ~FileFormat() {} // virtual destructor
};

class CSVFile : public FileFormat {
public:
	CSVFile(const std::string& filename) : FileFormat{ filename } {}
	std::vector<Event> loadFromFile() override;
	void saveToFile(const std::vector<Event>& events) override;
};

class HTMLFile : public FileFormat {
public:
	HTMLFile(const std::string& filename) : FileFormat{ filename } {}
	std::vector<Event> loadFromFile() override;
	void saveToFile(const std::vector<Event>& events) override;
};

class TextFile : public FileFormat {
public:
	TextFile(const std::string& filename) : FileFormat{ filename } {}
	void saveToFile(const std::vector<Event>& events) override;
	std::vector<Event> loadFromFile() override;
};