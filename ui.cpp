
#include "ui.h"
#include "Validator.h"
using namespace std;

void waitForSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void UI::printMenu() {
    cout << "\nAdministrator Mode - Event Management\n";
    cout << "1. Add Event\n";
    cout << "2. Remove Event\n";
    cout << "3. Update Event\n";
    cout << "4. Show All Events\n";
    cout << "0. Exit\n";
}

void UI::printMenuUser() {
    cout << "\nUser Mode - Event Management\n";
    cout << "1. Display all events for month\n";
    cout << "2. Print all from list\n";
    cout << "3. Open the list \n";
    cout << "0. Exit\n";
}


void UI::addEvent() {
    string title, description, link;
    int number_people, year, month, day, hour, minute;

    cout << "Title: "; cin.ignore(); getline(cin, title);
    cout << "Description: "; getline(cin, description);
    cout << "Number of people: "; number_people = getValidatedInt();
    cout << "Link: "; getline(cin, link);
    cout << "Date: \n";
    cout << "Year: "; year = getValidatedInt();
    cout << "Month: ";month = getValidatedInt();
    cout << "Day: ";day = getValidatedInt();
    cout << "Hour: ";hour = getValidatedInt();
    cout << "Minute: ";minute = getValidatedInt();
    // cin >> year >> month >> day >> hour >> minute;

    DateTime date(year, month, day, hour, minute);

    try {
        EventValidator::validateDate(date);  // Validate the date
        EventValidator::validateString(title, "Title");  // Validate the title string
        EventValidator::validateString(description, "Description");  // Validate description
        EventValidator::validateLink(link, "Link");  // Validate the link
        service.addEvent(title, description, date, number_people, link);
        cout << "Event added successfully!\n";
    }
    catch (ValidationException& ex) {
        std::cout << ex.getMessage() << std::endl;
        return;
    }
    catch (ValidationExceptionInherited& exh) {
        std::cout << exh.what() << std::endl;
        return;
    }
}



void UI::removeEvent() {
    string link;
    cout << "Enter event link to remove: ";cin.ignore(); getline(cin, link);
    try {
        EventValidator::validateString(link, "String");
        service.removeEvent(link);
        cout << "Event removed successfully!\n";
    }
    catch (ValidationException& ex) {
        std::cout << ex.getMessage() << std::endl;
        return;
    }
    catch (ValidationExceptionInherited& exh) {
        std::cout << exh.what() << std::endl;
        return;
    }
}

void UI::updateEvent() {
    string title, description, link;
    int number_people, year, month, day, hour, minute;

    cout << "Enter event link to update: ";getline(cin, link);
    cout << "New Title: "; getline(cin, title);
    cout << "New Description: "; getline(cin, description);
    cout << "New Number of people: "; number_people = getValidatedInt(); //cin >> number_people;
    cout << "New Date (YYYY MM DD HH MM): ";
    cout << "Date: \n";
    cout << "Year: "; year = getValidatedInt();
    cout << "Month: ";month = getValidatedInt();
    cout << "Day: ";day = getValidatedInt();
    cout << "Hour: ";hour = getValidatedInt();
    cout << "Minute: ";minute = getValidatedInt();


    //cin >> year >> month >> day >> hour >> minute;

    // if (!validateDateInput(year, month, day, hour, minute)) {
    //     cout << "Invalid date inputs!\n";
    //     return;
    // }

    DateTime date(year, month, day, hour, minute);

    try {
        EventValidator::validateDate(date);
        EventValidator::validateString(title, "Title");
        EventValidator::validateString(description, "Description");
        EventValidator::validateLink(link, "Link");
        service.updateEvent(link, title, description, date, number_people);
        cout << "Event updated successfully!\n";
    }
    catch (ValidationException& ex) {
        std::cout << ex.getMessage() << std::endl;
        return;
    }
    catch (ValidationExceptionInherited& exh) {
        std::cout << exh.what() << std::endl;
        return;
    }
}

void UI::showAllEvents() {
    std::vector<Event> events = service.getAllEvents();
    int size = service.getSize();

    if (size == 0) {
        cout << "No events found!\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << "Title: " << events[i].get_title() << "\n"
            << "Description: " << events[i].get_description() << "\n"
            << "People Going: " << events[i].get_no_of_people() << "\n"
            << "Link: " << events[i].get_link() << "\n"
            << "Date: " << events[i].get_date().date_to_string() << "\n\n";
    }
}



void UI::getAllFromList() {
    std::vector<Event> events = this->service.get_all_from_list();
    for (Event event : events) {
        cout << "Title: " << event.get_title() << "\n"
            << "Description: " << event.get_description() << "\n"
            << "People Going: " << event.get_no_of_people() << "\n"
            << "Link: " << event.get_link() << "\n"
            << "Date: " << event.get_date().date_to_string() << "\n\n";
    }
}

void UI::showEventsWithMonth() {
    int choice = 3;
    int index = 0;
    int month;
    Event event;
    cout << "Enter month of wanted events: (0 for all events sorted) ";
    month = getValidatedInt();
    cout << endl;

    std::vector<Event> events = this->service.getEventsmonth(month);

    if (events.empty()) {
        cout << "No events found for this month.\n";
        return;
    }

    while (true) {
        if (index >= events.size()) {
            index = 0;
        }
        if (index == 0)
            cout << "\nThese are all the Events requested!\n";

        if (choice == 3) {
            event = events[index];
            string URL = event.get_link();
            cout << "Title: " << event.get_title() << "\n"
                << "Description: " << event.get_description() << "\n"
                << "People Going: " << event.get_no_of_people() << "\n"
                << "Link: " << event.get_link() << "\n"
                << "Date: " << event.get_date().date_to_string() << "\n\n";

            this_thread::sleep_for(chrono::seconds(1));
            system(std::string("start " + URL).c_str());
        }

        cout << "1. Book event\n";
        cout << "2. Remove event from personal\n";
        cout << "3. Next\n";
        cout << "4. Exit\n";
        cout << " > ";
        choice = getValidatedInt();

        if (choice == 1) {
            if (this->service.add_to_list(event))
                cout << "Event added to your personal list\n";
            else
                cout << "You already booked this event!\n";

        }
        else if (choice == 2) {
            if (this->service.remove_from_list(event))
                cout << "Event removed from your personal list\n";
            else
                cout << "This event is not in your personal list\n";

        }
        else if (choice == 3) {
            index++;
            continue;

        }
        else if (choice == 4) {
            break;

        }
        else {
            cout << "Invalid choice!\n";
        }
    }
}


// int UI::getValidatedInt() {
//  int num;
//  while (true) {
//
//     std::cin >> num;
//
//     if (std::cin.fail()) {
//        std::cin.clear(); // clear the error flag
//        std::cin.ignore(10000, '\n'); // discard invalid input
//        std::cout << "Invalid input. Please enter an integer.\n";
//     } else {
//        std::cin.ignore(10000, '\n'); // discard any extra input after the number
//        return num;
//     }
//  }
// }
int UI::getValidatedInt() {
    int num;
    std::string input;

    while (true) {
        try {
            std::getline(std::cin, input);  // Read full line as string
            size_t pos;
            num = std::stoi(input, &pos);  // Try to convert to int

            if (pos != input.length())  // Check if whole string was valid
                throw std::invalid_argument("Extra characters after number");

            return num;  // Valid integer, return it

        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid integer.\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Number out of range. Please try again.\n";
        }
        cout << " > ";
    }
}



void UI::runadmin() {
    int option;
    do {
        printMenu();
        cout << "Choose an option: "; option = getValidatedInt(); cout << endl;
        switch (option) {
        case 1: addEvent(); break;
        case 2: removeEvent(); break;
        case 3: updateEvent(); break;
        case 4: showAllEvents(); break;

        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid option! Try again.\n";
        }
    } while (option != 0);
}


void UI::runusers() {
    int formatChoice;
    cout << "Choose output format:\n";
    cout << "1. CSV\n";
    cout << "2. HTML\n";
    cout << "> ";
    formatChoice = getValidatedInt();

    if (formatChoice == 1) {
        setEventsList(new CSVEventsList{ "list.csv" });
    }
    else if (formatChoice == 2) {
        setEventsList(new HTMLEventsList{ "list.html" });
    }
    else {
        cout << "Invalid choice. Defaulting to CSV.\n";
        setEventsList(new CSVEventsList{ "personal.csv" });
    }


    int option;
    do {
        printMenuUser();
        cout << "Choose an option:       "; cin >> option; cout << endl;
        switch (option) {
        case 1: showEventsWithMonth(); break;
        case 2:  getAllFromList(); break;
        case 3:  service.open_list(); break;
        case 0: cout << "Exiting...\n"; return;
        default: cout << "Invalid option! Try again.\n";
        }
    } while (option != 0);
}

void UI::run() {
    //generate_ten();
    int option;
    while (true) {
        cout << "\nChoose user (1 for admin, 2 for user): \n";
        cout << "Press 0 for exit \n";
        cout << "> ";
        option = getValidatedInt();
        //cin >> option;
        switch (option) {
        case 1: runadmin(); break;
        case 2: runusers(); break;
        case 0: cout << "Exiting...\n"; return;
        default: cout << "Invalid option! Try again.\n";
        }
    }
}

