#include "Logger.h"

std::mutex Logger::_printMutex;

void Logger::PrintText(const std::wstring& text, va_list args, __FILE* stream) {
	std::lock_guard<std::mutex> lock(_printMutex);

	std::wstringstream outputBuffer;
	outputBuffer << L"[" << _tag << L"]: ";

	fwprintf(stream, outputBuffer.str().c_str());
	vfwprintf(stream, text.c_str(), args);
	fwprintf(stream, L"\n");

	va_end(args);
}

Logger::Logger(const std::wstring&& tag) {
	SetTag(tag);
}

Logger::Logger() {
	_tag = L"Anonymous";
}

void Logger::operator=(const Logger& logger) {
	_tag = logger._tag;
}

void Logger::SetTag(const std::wstring& tag) {
	_tag = tag;
}

std::wstring& Logger::GetTag() {
	return _tag;
}

void Logger::Info(const std::wstring&& text, ...) {
	va_list args;
	va_start(args, text);

	PrintText(text, args);
}

void Logger::Warning(const std::wstring&& text, ...) {
	va_list args;
	va_start(args, text);

	PrintText(std::wstring(L"WARNING " + text), args);
}

void Logger::Error(const std::wstring&& text, ...) {
	va_list args;
	va_start(args, text);

	PrintText(std::wstring(L"CRITICAL ERROR " + text), args, stderr);
}
