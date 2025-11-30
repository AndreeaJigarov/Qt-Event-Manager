//
// Created by Raton on 3/26/2025.
//

#include "DateTime.h"

#include <iostream>
#include <sstream>


DateTime::DateTime(int year, int month, int day, int hour, int minute) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
}

DateTime::DateTime() {
	this->year = 2000;
	this->month = 1;
	this->day = 1;
	this->hour = 0;
	this->minute = 0;

}

DateTime::~DateTime() {}

int DateTime::getYear()const { return year; }
int DateTime::getMonth()const { return month; }
int DateTime::getDay()const { return day; }
int DateTime::getHour()const { return hour; }
int DateTime::getMinute()const { return minute; }

void DateTime::setYear(int new_year) { this->year = new_year; }
void DateTime::setMonth(int new_month) { this->month = new_month; }
void DateTime::setDay(int new_day) { this->day = new_day; }
void DateTime::setHour(int new_hour) { this->hour = new_hour; }
void DateTime::setMinute(int new_minute) { this->minute = new_minute; }

string DateTime::date_to_string() {
	string result;

	// Pad day
	if (day < 10)
		result += "0";
	result += to_string(day) + "-";

	// Pad month
	if (month < 10)
		result += "0";
	result += to_string(month) + "-";

	// Year
	result += to_string(year) + " ";

	// Pad hour
	if (hour < 10)
		result += "0";
	result += to_string(hour) + ":";

	// Pad minute
	if (minute < 10)
		result += "0";
	result += to_string(minute);

	return result;
}
bool DateTime::operator==(const DateTime& other) {
	return this->year == other.year && this->month == other.month && this->day == other.day &&
		this->hour == other.hour && this->minute == other.minute;
}


std::vector<std::string> DateTime::split(std::string str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter))
	{
		result.push_back(token);
	}
	return result;
}


std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
	os << dt.year << "," << dt.month << "," << dt.day << ","
		<< dt.hour << "," << dt.minute;
	return os;
}

std::istream& operator>>(std::istream& is, DateTime& dt) {

	std::string line;
	std::getline(is, line, ';');
	std::vector<std::string> tokens;
	tokens = dt.split(line, ',');
	if (tokens.size() != 5)
		return is;
	dt.year = std::stoi(tokens[0]);
	dt.month = std::stoi(tokens[1]);
	dt.day = std::stoi(tokens[2]);
	dt.hour = std::stoi(tokens[3]);
	dt.minute = std::stoi(tokens[4]);
	return is;
}

void DateTime::from_string(const std::string& str) {
	std::vector<std::string> tokens = split(str, ',');
	if (tokens.size() != 5)
		throw std::invalid_argument("Invalid DateTime string format");
	year = std::stoi(tokens[0]);
	month = std::stoi(tokens[1]);
	day = std::stoi(tokens[2]);
	hour = std::stoi(tokens[3]);
	minute = std::stoi(tokens[4]);
}



// is >> dt.year >> dt.month >> dt.day >> dt.hour >> dt.minute;
// return is;
// std::string str;
// std::getline(is, str, ',');
// std::vector<std::string> tokens;
// std::vector<std::string> tokens_aux;
// tokens = dt.split(str, '|');
// if (tokens.size() != 2)
// 	return is;
// tokens_aux = dt.split(tokens[0], '-');
// if (tokens_aux.size() != 3)
// 	return is;
// dt.year = atoi(tokens_aux[0].c_str());
// dt.month = atoi(tokens_aux[1].c_str());
// dt.day = atoi(tokens_aux[2].c_str());
//
// tokens_aux=dt.split(tokens[1], ':');
// if (tokens_aux.size() != 2)
// 	return is;
// dt.hour = atoi(tokens_aux[0].c_str());
// dt.minute = atoi(tokens_aux[1].c_str());
// return is;


