#include "UI.h"
#include <iostream>
#include <limits>

using namespace std;

int UI::get_first_option() {
    cout << "===========================\n";
    cout << "       1. Admin\n";
    cout << "       2. User\n";
    cout << "       0. Exit\n";
    cout << "===========================\n";
    int option;
    while(!(cin >> option)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "UI.cpp: Invalid input. Please try again: ";
    }
    return option;
}

int UI::get_admin_option() {
    cout << "1. Add an event\n";
    cout << "2. Remove an event\n";
    cout << "3. Update an event\n";
    cout << "4. See all events\n";
    cout << "0. Exit\n";
    int option;
    while(!(cin >> option)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "UI.cpp: Invalid input. Please try again: ";
    }
    return option;
}

void UI::add_event() {
    string title, description, date, time, link;
    int participantsNumber;
    cout << "Give the event title: ";
    cin >> title;
    cout << "Event description: ";
    cin >> description;
    cout << "Event date: ";
    cin >> date;
    cout << "Event time: ";
    cin >> time;
    cout << "Number of participants: ";
    while(!(cin >> participantsNumber)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "UI.cpp: Invalid input. Please try again: ";
    }
    cout << "Link to the event: ";
    cin >> link;
    Event event = Event(title, description, date, time, participantsNumber, link);
    controller.addNewEvent(controller.getRepo(), event);
}

void UI::remove_event() {
    string title, date;
    cout << "Give the event title: ";
    cin >> title;
    cout << "Event date: ";
    cin >> date;
    controller.removeEvent(controller.getRepo(), title, date);
}

void UI::update_event() {
    string title, date, newTitle, newDescription, newDate, newTime, newLink;
    int newParticipantsNumber;
    cout << "Give the event title: ";
    cin >> title;
    cout << "Event date: ";
    cin >> date;
    cout << "New event title: ";
    cin >> newTitle;
    cout << "New event description: ";
    cin >> newDescription;
    cout << "New event date: ";
    cin >> newDate;
    cout << "New event time: ";
    cin >> newTime;
    cout << "New number of participants: ";
    while(!(cin >> newParticipantsNumber)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "UI.cpp: Invalid input. Please try again: ";
    }
    cout << "New link to the event: ";
    cin >> newLink;
    controller.updateEvent(controller.getRepo(), title, date, newTitle, newDescription, newDate, newTime, newParticipantsNumber, newLink);
}

void UI::admin_actions() {
    while (true) {
        try {
            int option = get_admin_option();
            switch (option) {
                case 0:
                    return;
                case 1:
                    add_event();
                    break;
                case 2:
                    remove_event();
                    break;
                case 3:
                    update_event();
                    break;
                case 4:
                    cout << controller.get_all_events(controller.getRepo()) << '\n';
                    break;
                default:
                    throw ValidatorException("UI.cpp: Not a valid input");
            }
        } catch (const ValidatorException &e) {
            cout << "Error: " << e.what() << '\n';
        } catch (const RepoException &e) {
            cout << "Error: " << e.what() << '\n';
        }
    }
}

int UI::get_user_option() {
    cout << "1. See all events in a month\n";
    cout << "2. Delete an event from your list\n";
    cout << "3. See events you signed up for\n";
    cout << "4. Open the chosen file\n";
    cout << "0. Exit\n";
    int option;
    while(!(cin >> option)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "UI.cpp: Invalid input. Please try again:";
    }
    return option;
}

void UI::get_events_from_month() {
    cout << "Give the month you want to see:";
    string month;
    cin >> month;
    Repo eventsInMonth = controller.getEventsInMonth(month);
    int index = 0;
    while (true) {
        int option;
        cout << eventsInMonth[index].toStringDetailed() << '\n';
        cout << "1. Sign up for this event\n";
        cout << "2. See next event\n";
        cout << "0. Back\n";
//        controller.openURL(eventsInMonth[index].getLink());
        cin >> option;
        switch (option) {
            case 0:
                return;
            case 1:
                try {
                    controller.addNewEvent(controller.getUserRepo(), eventsInMonth[index]);
                    controller.modifyUserCount(controller.getUserRepo(), eventsInMonth[index], 1);
                    controller.modifyUserCount(controller.getRepo(), eventsInMonth[index], 1);
                } catch (const RepoException &e) {
                    cout << "Error: " << e.what() << '\n';
                } catch (const ValidatorException &e) {
                    cout << "Error: " << e.what() << '\n';
                }
                break;
            case 2:
                // continues to the next event
                break;
            default:
                throw ValidatorException("UI.cpp: Not a valid input");
        }
        index++;
        if (index >= eventsInMonth.getSize()) {
            index = 0;
            eventsInMonth = controller.getEventsInMonth(month);
        }
    }
}

void UI::delete_user_event() {
cout << "Give the event title: ";
    string title;
    cin >> title;
    cout << "Give the event date: ";
    string date;
    cin >> date;
    try {
        controller.removeEvent(controller.getUserRepo(), title, date);
        Event event = Event(title, "", date, "", 0, "");
        controller.modifyUserCount(controller.getUserRepo(), event, -1);
        controller.modifyUserCount(controller.getRepo(), event, -1);
    } catch (const ValidatorException &e) {
        cout << "Error: " << e.what() << '\n';
    } catch (const RepoException &e) {
        cout << "Error: " << e.what() << '\n';
    }
}

void UI::user_actions() {
    while (true) {
        try {
            int option = get_user_option();
            switch (option) {
                case 0:
                    return;
                case 1:
                    get_events_from_month();
                    break;
                case 2:
                    delete_user_event();
                    break;
                case 3:
                    cout << controller.get_all_events(controller.getUserRepo()) << '\n';
                    break;
                case 4:
                    controller.openChosenFile();
                    break;
                default:
                    throw ValidatorException("UI.cpp: Not a valid input");
            }
        } catch(const ValidatorException &e) {
            cout << "Error: " << e.what() << '\n';
        } catch(const RepoException &e) {
            cout << "Error: " << e.what() << '\n';
        }
    }
}

//===================================================================================================

string getFileType() {
    int option;
    cout << "Choose the file type:\n";
    cout << "1. CSV\n";
    cout << "2. HTML\n";
    cout << ">";
    cin >> option;
    while (option != 1 && option != 2) {
        cout << "Invalid input, please try again!\n>";
        cin >> option;
    }
    string fileType;
    if (option == 1)
        fileType = "CSV";
    else
        fileType = "HTML";
    return fileType;
}

void UI::run() {
    while (true) {
        int option = UI::get_first_option();
        switch (option) {
            case 0:
//                cout << _CrtDumpMemoryLeaks();
                return;
            case 1:
                admin_actions();
                break;
            case 2:
                user_actions();
                break;
            default:
                cout << "Not a valid input, try again\n\n";
                break;
        }
    }
}

UI::UI() : controller(getFileType()) {}
