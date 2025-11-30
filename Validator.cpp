#include "Validator.h"
#include <algorithm>
#include <cctype>
#include <sstream>

// -------------------- ValidationException Implementation --------------------
ValidationException::ValidationException(std::string _message)
	: message(std::move(_message)) {
}

std::string ValidationException::getMessage() const {
	return message;
}

ValidationExceptionInherited::ValidationExceptionInherited(std::string _message)
	: message(std::move(_message)) {
}

const char* ValidationExceptionInherited::what() const noexcept {
	return message.c_str();
}

// -------------------- EventValidator Implementation --------------------
void EventValidator::validate(const Event& event) {
	std::string error;

	if (event.get_title().empty())
		error += "Title cannot be empty!\n";
	if (event.get_description().empty())
		error += "Description cannot be empty!\n";

	std::string link = event.get_link();
	if (link.empty())
		error += "Link cannot be empty!\n";
	if (link.find("http://") == std::string::npos && link.find("https://") == std::string::npos &&
		link.find("www.") == std::string::npos)
		error += "Link must start with http:// , https:// or www.\n";

	if (event.get_no_of_people() < 0)
		error += "Number of people cannot be negative!\n";

	DateTime dt = event.get_date();
	if (dt.getYear() < 1900 || dt.getYear() > 3000)
		error += "Year must be between 1900 and 3000\n";
	if (dt.getMonth() < 1 || dt.getMonth() > 12)
		error += "Month must be between 1 and 12\n";
	if (dt.getDay() < 1 || dt.getDay() > 31)
		error += "Day must be between 1 and 31\n";
	if (dt.getHour() < 0 || dt.getHour() > 23)
		error += "Hour must be between 0 and 23\n";
	if (dt.getMinute() < 0 || dt.getMinute() > 59)
		error += "Minute must be between 0 and 59\n";

	if (!error.empty())
		throw ValidationException(error);
}

void EventValidator::validateDate(const DateTime& date) {
	std::string error;

	if (date.getYear() < 2000)
		error += "Year must be >= 2000!\n";
	if (date.getMonth() < 1 || date.getMonth() > 12)
		error += "Month must be between 1 and 12!\n";
	if (date.getDay() < 1 || date.getDay() > 31)
		error += "Day must be between 1 and 31!\n";
	if (date.getHour() < 0 || date.getHour() > 23)
		error += "Hour must be between 0 and 23!\n";
	if (date.getMinute() < 0 || date.getMinute() > 59)
		error += "Minute must be between 0 and 59!\n";

	if (!error.empty())
		throw ValidationException(error);
}


void EventValidator::validateString(const std::string& str, const std::string& fieldName) {
	if (str.empty())
		throw ValidationException(fieldName + " cannot be empty!");
}

void EventValidator::validateLink(const std::string& str, const std::string& fieldName) {
	if (str.empty())
		throw ValidationException(fieldName + " cannot be empty!");
	if (std::any_of(str.begin(), str.end(), ::isspace))
		throw ValidationException(fieldName + " cannot contain spaces!");
}



void EventValidator::validateNumber(const std::string& str, const std::string& fieldName) {
	if (str.empty())
		throw ValidationException(fieldName + " cannot be empty!");
	if (std::any_of(str.begin(), str.end(), ::isalpha))
		throw ValidationException(fieldName + " cannot contain letters!");
	if (std::any_of(str.begin(), str.end(), ::isspace))
		throw ValidationException(fieldName + " cannot contain spaces!");
	if (std::stoi(str) < 0)
		throw ValidationException(fieldName + " cannot be negative!");
}
