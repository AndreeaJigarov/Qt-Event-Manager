//
// Created by Raton on 3/26/2025.
//

#pragma once
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class DateTime {
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;


public:

	DateTime(int year, int month, int day, int hour, int minute);
	DateTime();
	~DateTime();

	int getYear()const;
	int getMonth()const;
	int getDay()const;
	int getHour()const;
	int getMinute()const;

	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setHour(int hour);
	void setMinute(int minute);

	string date_to_string();

	//--------------------------------
	friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
	friend std::istream& operator>>(std::istream& is, DateTime& dt);
	void from_string(const std::string& str);

	//----------------------------
	DateTime& operator=(const DateTime& dt) {
		this->day = dt.day;
		this->month = dt.month;
		this->year = dt.year;
		this->hour = dt.hour;
		this->minute = dt.minute;
		return *this;
	}

	bool operator==(const DateTime& other);
	//bool operator<(const DateTime& other);

	/*
	Splits a string into a vector of strings based on a delimiter.
	*/
	std::vector<std::string> split(std::string str, char delimiter);

};




