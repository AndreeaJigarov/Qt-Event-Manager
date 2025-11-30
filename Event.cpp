//
// Created by Raton on 3/26/2025.
//

#include "Event.h"

#include <sstream>

Event::Event() {
	this->title = "";
	this->description = "";
	this->link = "";
	this->no_of_people = 0;
	this->date = DateTime();
}

Event::Event(string title, string description, string link, int no_of_people, DateTime date) {
	this->title = title;
	this->description = description;
	this->link = link;
	this->no_of_people = no_of_people;
	this->date = date;
}

Event::~Event() {
	// Nothing to clean up, no dynamic memory used
}

string Event::get_title() const { return title; }
string Event::get_description() const { return description; }
string Event::get_link() const { return link; }
int Event::get_no_of_people() const { return no_of_people; }
DateTime Event::get_date() const { return date; }

void Event::set_title(string new_title) { this->title = new_title; }
void Event::set_description(string new_description) { this->description = new_description; }
void Event::set_link(string new_link) { this->link = new_link; }
void Event::set_no_of_people(int new_no_of_people) { this->no_of_people = new_no_of_people; }
void Event::set_date(DateTime new_date) { this->date = new_date; }


std::string Event::to_string() {
	std::string str = "";
	str += "Title: " + this->title + "\n";
	str += "Description: " + this->description + "\n";
	str += "People going: " + std::to_string(this->no_of_people) + "\n";
	str += "Link: " + this->link + "\n";
	str += "Date: " + this->date.date_to_string() + "\n";
	return str;

}

std::vector<std::string> Event::split(std::string str, char delimiter)
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

bool Event::operator==(const Event& other) const {
	return this->link == other.link;
}

//-------------------------

std::ostream& operator<<(std::ostream& os, const Event& ev) {
	os << ev.title << ";" << ev.description << ";" << ev.date << ";"
		<< ev.no_of_people << ";" << ev.link;
	return os;
}

std::istream& operator>>(std::istream& is, Event& ev) {
	// is >> ev.title >> ev.description >> ev.date >> ev.no_of_people>> ev.link;
	// return is;
	std::string line;
	std::getline(is, line, '\n');
	std::vector<std::string> tokens;
	tokens = ev.split(line, ';');
	if (tokens.size() != 5)
		return is;
	ev.title = tokens[0];
	ev.description = tokens[1];
	ev.date.from_string(tokens[2]);
	ev.no_of_people = std::stoi(tokens[3]);
	ev.link = tokens[4];
	return is;
}