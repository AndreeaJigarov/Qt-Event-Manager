#pragma once
//include "textrepository.h"
#include "repository.h"
#include "Event.h"
#include "DateTime.h"
#include "EventsList.h"
#include "Validator.h"
#include <vector>

class Service {
private:

	Repository* repository;
	//std::vector<Event> list; // Replaces DynamicArray<Event> list
	EventsList* ev_list;

public:
	Service(Repository* repo, EventsList* ev) : repository(repo), ev_list(ev) {}
	~Service();

	void setEventsList(EventsList* newList) {
		if (this->ev_list != nullptr) delete this->ev_list;
		this->ev_list = newList;
	}

	Service& operator=(const Service& other) {
		if (this != &other) {
			this->repository = other.repository;
		}
		return *this;
	}

	bool addEvent(std::string title, std::string description, DateTime date, int number_people, std::string link);
	bool removeEvent(std::string link);
	bool updateEvent(std::string link, std::string title, std::string description, DateTime date, int number_people);

	std::vector<Event> getAllEvents();
	int getSize();

	std::vector<Event> getEventsmonth(int month);

	bool add_to_list(Event event);
	bool remove_from_list(Event event);
	std::vector<Event> get_all_from_list();
	int get_list_size() { return ev_list->getSize(); }
	void open_list();

	static bool compareByDate(Event a, Event b);


};
