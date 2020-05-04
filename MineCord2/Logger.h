#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include <cstdio>
#include <cstdarg>

class Logger {
private:
	std::string _tag;
	static std::mutex _printMutex;

private:
	void PrintText(const std::string& text, va_list args, __FILE* stream = stdout);

public:
	Logger(const std::string&& tag);
	Logger();

	void operator=(const Logger& logger);

	void SetTag(const std::string& tag);
	std::string& GetTag();

	void Info(const std::string&& text, ...);
	void Warning(const std::string&& text, ...);
	void Error(const std::string&& text, ...);
};

