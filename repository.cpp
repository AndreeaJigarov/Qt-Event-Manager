#include "repository.h"



Repository::Repository() {}
Repository::~Repository() {}

bool Repository::add_event(Event e) {
	for (const auto& ev : events)
		if (ev == e)
			//throw ValidationException("Event already exists");
			return false;
	events.push_back(e);
	return true;
}

bool Repository::remove_event(string link) {
	for (auto it = events.begin(); it != events.end(); ++it) {
		if (it->get_link() == link) {
			events.erase(it);
			return true;
		}
	}
	//throw ValidationException("Event not found!");
	return false;
}

bool Repository::update_event(Event e) {
	for (auto& ev : events) {
		if (ev == e) {
			ev = e;
			return true;
		}
	}
	//throw ValidationException("Event not found!");
	return false;
}
void Repository::generate_events() {
	add_event(Event("Concert Night", "Live music by famous bands", "https://feverup.com/ro/cluj-napoca/candlelight", 200, DateTime(2025, 6, 15, 19, 30)));
	add_event(Event("Tech Conference", "Latest trends in AI and ML", "https://www.devtalks.ro/", 500, DateTime(2025, 9, 10, 10, 0)));
	add_event(Event("Art Exhibition", "Modern art showcase", "https://www.artsy.net/partner/whitney-museum-of-american-art-1", 100, DateTime(2025, 4, 25, 16, 0)));
	add_event(Event("Book Fair", "Meet your favorite authors", "https://example.com/bookfair", 300, DateTime(2025, 5, 20, 14, 0)));
	add_event(Event("Food Festival", "Taste the best street food", "https://bookfest.ro/home", 1000, DateTime(2025, 7, 8, 12, 0)));
	add_event(Event("Gaming Tournament", "Compete in sports", "https://www.esportsworldcup.com/en/competition/games-and-tournaments", 150, DateTime(2025, 8, 15, 18, 0)));
	add_event(Event("Marathon", "Annual city run", "https://maraton-cluj.ro", 5000, DateTime(2025, 10, 4, 6, 30)));
	add_event(Event("Startup Pitch", "Innovative startup ideas", "https://www.southsummit.io/startup-competition/", 200, DateTime(2025, 11, 12, 9, 0)));
	add_event(Event("Science Fair", "Explore exciting experiments", "https://www.societyforscience.org/isef/", 400, DateTime(2025, 3, 28, 11, 0)));
	add_event(Event("Film Screening", "Exclusive movie premiere", "https://www.intofilm.org/events", 250, DateTime(2025, 4, 5, 20, 0)));

}

std::vector<Event> Repository::get_all_events() const {
	return events;
}

int Repository::get_size() const {
	return events.size();
}

std::vector<Event> Repository::get_events(int month) const {
	std::vector<Event> month_events;

	for (auto ev : events) {
		if (ev.get_date().getMonth() == month)
			month_events.push_back(ev);
	}
	return month_events;
}
Event Repository::get_event(int pos) const { return this->events[pos]; }


//------------------------

TextRepo::TextRepo(const std::string& filename) : filename(filename) {
	loadFromFile();
}

void TextRepo::loadFromFile() {
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		return;
	}

	if (fin.peek() == std::ifstream::traits_type::eof()) {
		this->generate_events();
	}
	else {
		Event e;
		events.clear();
		while (fin >> e) {
			events.push_back(e);
		}
	}
	fin.close();
}

void TextRepo::saveToFile() {
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		return;
	}
	for (const Event& e : events) {
		fout << e << "\n";
	}
	fout.close();
}

bool TextRepo::add_event(Event e) {
	if (Repository::add_event(e)) {
		saveToFile();
		return true;
	}
	return false;
}

bool TextRepo::remove_event(std::string link) {
	if (Repository::remove_event(link)) {
		saveToFile();
		return true;
	}
	return false;
}

bool TextRepo::update_event(Event e) {
	if (Repository::update_event(e)) {
		saveToFile();
		return true;
	}
	return false;
}
