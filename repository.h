#pragma once
#include <vector>
#include "Event.h"
#include "DateTime.h"
#include "Validator.h"
#include <fstream>
using namespace std;
class Repository {
protected:
	std::vector<Event> events;

public:
	Repository();
	virtual ~Repository();

	virtual bool add_event(Event e);
	virtual bool remove_event(std::string link);
	virtual bool update_event(Event e);

	void generate_events();

	vector<Event> get_all_events() const;
	int get_size() const;
	vector<Event> get_events(int month) const;
	Event get_event(int pos) const;

	Repository& operator=(const Repository& other)
	{
		if (this != &other)
		{
			this->events = other.events;
		}
		return *this;
	}

};


class TextRepo : public Repository {
private:
	std::string filename;

	void loadFromFile();
	void saveToFile();

public:
	TextRepo(const std::string& filename);
	~TextRepo() = default;

	bool add_event(Event e) override;
	bool remove_event(std::string link) override;
	bool update_event(Event e) override;
};