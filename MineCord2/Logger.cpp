#include "Logger.h"

std::mutex Logger::_printMutex;

void Logger::PrintText(const std::string& text, va_list args, __FILE* stream) {
	std::lock_guard<std::mutex> lock(_printMutex);

	std::stringstream outputBuffer;
	outputBuffer << "[" << _tag << "]: ";

	fprintf(stream, outputBuffer.str().c_str());
	vfprintf(stream, text.c_str(), args);
	fprintf(stream, "\n");

	va_end(args);
}

Logger::Logger(const std::string&& tag) {
	SetTag(tag);
}

Logger::Logger() {
	_tag = "Anonymous";
}

void Logger::operator=(const Logger& logger) {
	_tag = logger._tag;
}

void Logger::SetTag(const std::string& tag) {
	_tag = tag;
}

std::string& Logger::GetTag() {
	return _tag;
}

void Logger::Info(const std::string&& text, ...) {
	va_list args;
	va_start(args, text);

	PrintText(text, args);
}

void Logger::Warning(const std::string&& text, ...) {
	va_list args;
	va_start(args, text);

	PrintText(std::string("WARNING " + text), args);
}

void Logger::Error(const std::string&& text, ...) {
	va_list args;
	va_start(args, text);

	PrintText(std::string("CRITICAL ERROR " + text), args, stderr);
}
