//
// Created by Raton on 3/26/2025.
//


#pragma once
#include <string.h>
using namespace std;
#include "DateTime.h"



class Event {
private:
	string title;
	string description;
	string link;
	int no_of_people;
	DateTime date;

public:
	Event();
	Event(string title, string description, string link, int no_of_people, DateTime date);
	~Event();

	string get_title() const;
	string get_description() const;
	string get_link() const;
	int get_no_of_people()const;
	DateTime get_date()const;

	void set_title(string title);
	void set_description(string description);
	void set_link(string link);
	void set_no_of_people(int no_of_people);
	void set_date(DateTime date);

	std::string to_string();
	std::vector<std::string> split(std::string str, char delimiter);


	/*
	 * Redefines "==" operator to be true if links of 2 events are equal. Unicity given by link
	 */
	bool operator==(const Event& other) const;

	Event& operator=(const Event& other) {
		this->title = other.title;
		this->description = other.description;
		this->link = other.link;
		this->no_of_people = other.no_of_people;
		this->date = other.date;
		return *this;
	}

	//---------------------------------------------------------------
	friend std::ostream& operator<<(std::ostream& os, const Event& ev);
	friend std::istream& operator>>(std::istream& is, Event& ev);
	//-----------------------------------------------------------------

};




