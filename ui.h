#pragma once
#include <thread>
#include <iostream>
#include "service.h"



class UI {
private:
    Service service;

    void printMenu();
    void printMenuUser();
    //bool validateDateInput(int year, int month, int day, int hour, int minute);
    //void generate_ten();
    void addEvent();
    void removeEvent();
    void updateEvent();
    void showAllEvents();
    void showEventsWithMonth();
    void getAllFromList();
    int getValidatedInt();
    void setEventsList(EventsList* newList) {
        service.setEventsList(newList);
    }

public:
    UI(std::string filename, EventsList* eventslist)
        : service(new TextRepo(filename), eventslist) // <- initialize here
    {
    }
    void run();
    void runadmin();
    void runusers();
    //void printEvent(const Event& event);
    ~UI() = default;
};


