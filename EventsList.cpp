//
// Created by Raton on 5/14/2025.
//

#include "EventsList.h"
#include <fstream>




void HTMLEventsList::save() {
	std::ofstream file(this->fileName);

	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Events List</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "<tr>\n";
	file << "<td>Title</td>\n";
	file << "<td>Description</td>\n";
	file << "<td>Date</td>\n";
	file << "<td>Number of people</td>\n";
	file << "<td>Link</td>\n";
	file << "</tr>\n";

	for (const auto& event : this->list) {
		file << "<tr>\n";
		file << "<td>" << event.get_title() << "</td>\n";
		file << "<td>" << event.get_description() << "</td>\n";
		file << "<td>" << event.get_date().date_to_string() << "</td>\n";
		file << "<td>" << event.get_no_of_people() << "</td>\n";
		file << "<td><a href=\"" << event.get_link() << "\">Link</a></td>\n";
		file << "</tr>\n";
	}

	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";

	file.close();
}
void HTMLEventsList::open() {
	std::string command;
	command = "start \"\" \"" + this->fileName + "\"";
	system(command.c_str());
}


HTMLEventsList::HTMLEventsList(std::string filename)
{
	this->fileName = filename;
}

void CSVEventsList::save() {
	std::ofstream file(this->fileName);
	for (const auto& ev : this->list) {
		file << ev.get_title() << "," << ev.get_description() << "," << ev.get_date() << "," << ev.get_no_of_people()
			<< "," << ev.get_link() << "\n";
	}
	file.close();
}

void CSVEventsList::open() {
	std::string command = "start \"\" \"" + this->fileName + "\"";
	system(command.c_str());
}




CSVEventsList::CSVEventsList(std::string filename)
{
	this->fileName = filename;
}
