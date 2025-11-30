//
// Created by Raton on 5/14/2025.
//
#pragma once
#include <string>
#include <vector>
#include "Event.h"
#include <cstdlib>  // for system()

class EventsList {
protected:
	std::vector<Event> list;
public:
	EventsList() {};
	virtual ~EventsList() {};

	int getSize() { return list.size(); }

	virtual void open() {}

	virtual void save() {}
	virtual std::string getFilename() { return ""; }

	bool add_event(Event event) {
		list.push_back(event);
		save();
		return true;
	}

	void remove_event(std::vector<Event>::iterator it) {
		list.erase(it);
		save();
	}

	std::vector<Event> get_all_from_list() {
		return list;
	}

	std::vector<Event>& get_list_reference() {
		return list;
	}

	//cause list is protected, we need access to iterate, getter
	Event get_event(int index) {
		if (index < 0 || index >= this->list.size())
			throw std::out_of_range("Index out of range");
		return this->list[index];
	}

};

class HTMLEventsList : public EventsList {
private:
	std::string fileName;
	void save() override;
public:
	void open() override;
	HTMLEventsList(std::string filename);
	~HTMLEventsList() override {};
	std::string getFileName() {
		return this->fileName;
	}
};


class CSVEventsList : public EventsList {
private:
	std::string fileName;
	void save() override;
public:
	void open() override;
	CSVEventsList(std::string filename);
	~CSVEventsList() override {};
	std::string getFileName() {
		return this->fileName;
	}
};


