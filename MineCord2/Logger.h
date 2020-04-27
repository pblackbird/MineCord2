#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include <cstdio>
#include <cstdarg>

class Logger {
private:
	std::wstring _tag;
	static std::mutex _printMutex;

private:
	void PrintText(const std::wstring& text, va_list args, __FILE* stream = stdout);

public:
	Logger(const std::wstring&& tag);
	Logger();

	void operator=(const Logger& logger);

	void SetTag(const std::wstring& tag);
	std::wstring& GetTag();

	void Info(const std::wstring&& text, ...);
	void Warning(const std::wstring&& text, ...);
	void Error(const std::wstring&& text, ...);
};

