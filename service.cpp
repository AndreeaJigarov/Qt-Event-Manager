#include "service.h"
#include <algorithm>


// Service::Service(string &filename) {
// 	TextRepo repo(filename);
//
// }
Service::~Service() {
	delete this->repository;
	delete this->ev_list;
}

bool Service::addEvent(string title, string description, DateTime date, int number_people, string link) {
	// if (number_people < 0) return -2;
	// if (link.empty()) return -3;
	// if (title.empty()) return -4;

	Event event(title, description, link, number_people, date);
	// if (!repository->add_event(event)) return -1;
	// return 0;

	EventValidator::validate(event);
	if (this->repository->add_event(event) == false)
		throw ValidationException("Event is already in the repository");
	return true;
}

bool Service::removeEvent(string link) {
	// if (!repository->remove_event(link)) return -1;
	// return 0;
	if (this->repository->remove_event(link) == false) {
		throw ValidationException("Event is not in the repository");
	}
	return true;

}

bool Service::updateEvent(string link, string title, string description, DateTime date, int number_people) {
	// if (number_people < 0) return -2;
	// if (link.empty()) return -3;
	// if (title.empty()) return -4;

	Event event(title, description, link, number_people, date);
	// if (!repository->update_event(event)) return -1;
	// return 0;
	EventValidator::validate(event);
	if (this->repository->update_event(event) == false) {
		throw ValidationException("Event is not in the repository");
	}
	return true;
}

std::vector<Event> Service::getAllEvents() {
	return repository->get_all_events();
}

int Service::getSize() { return repository->get_size(); }

void Service::open_list() {
	this->ev_list->open();
}

bool Service::compareByDate(Event a, Event b) {
	DateTime d1 = a.get_date();
	DateTime d2 = b.get_date();

	if (d1.getYear() != d2.getYear()) return d1.getYear() < d2.getYear();
	if (d1.getMonth() != d2.getMonth()) return d1.getMonth() < d2.getMonth();
	if (d1.getDay() != d2.getDay()) return d1.getDay() < d2.getDay();
	if (d1.getHour() != d2.getHour()) return d1.getHour() < d2.getHour();
	return d1.getMinute() < d2.getMinute();
}

std::vector<Event> Service::getEventsmonth(int month) {
	std::vector<Event> events;

	if (month == 0) {
		events = repository->get_all_events();
	}
	else {
		events = repository->get_events(month);
	}

	std::sort(events.begin(), events.end(), compareByDate);
	return events;
}

// ---- User part ----

bool Service::add_to_list(Event event) {
	// Use std::find_if to check for duplicate
	auto& list = ev_list->get_list_reference();
	//auto list = ev_list->get_all_from_list();
	auto it = std::find_if(list.begin(), list.end(), [&](const Event& e) { return e == event; });
	if (it != list.end()) return false;

	event.set_no_of_people(event.get_no_of_people() + 1);
	repository->update_event(event);
	ev_list->add_event(event);
	return true;
}

bool Service::remove_from_list(Event event) {
	auto& list = ev_list->get_list_reference();
	//auto& list = ev_list->get_list_reference();
	//auto list = ev_list->get_all_from_list();
	auto it = std::find_if(list.begin(), list.end(), [&](const Event& e) { return e == event; });
	if (it != list.end()) {
		event.set_no_of_people(event.get_no_of_people() - 1);
		repository->update_event(event);
		ev_list->remove_event(it);
		return true;
	}
	return false;
}

std::vector<Event> Service::get_all_from_list() {
	return ev_list->get_all_from_list();
}
