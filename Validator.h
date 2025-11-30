#pragma once

#include <string>
#include <exception>
#include "Event.h"

// -------------------- ValidationException --------------------
class ValidationException {
private:
	std::string message;
public:
	explicit ValidationException(std::string _message);
	std::string getMessage() const;
};

class ValidationExceptionInherited : public std::exception {
private:
	std::string message;
public:
	explicit ValidationExceptionInherited(std::string _message);
	const char* what() const noexcept override;
};

// -------------------- EventValidator --------------------
class EventValidator {
public:
	static void validate(const Event& event);
	static void validateDate(const DateTime& date);
	static void validateString(const std::string& str, const std::string& fieldName);
	static void validateNumber(const std::string& str, const std::string& fieldName);
	static void validateLink(const std::string& str, const std::string& fieldName);
};
