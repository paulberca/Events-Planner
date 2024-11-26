#include "event.h"
#include <string>
#include <sstream>

/**
 * Default constructor for the Event class
 * @return an Event object with all fields set to default values
 */
Event::Event() {
    title = "";
    description = "";
    date = "";
    time = "";
    participantsNumber = 0;
    link = "";
}

/**
 * Constructor for the Event class
 * @param title - the title of the event
 * @param description - the description of the event
 * @param date - the date of the event
 * @param time - the time of the event
 * @param participantsNumber - the number of participants of the event
 * @param link - the link of the event
 * @return an Event object with all fields set to the given values
 */
Event::Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int participantsNumber, const std::string& link) {
    this->title = title;
    this->description = description;
    this->date = date;
    this->time = time;
    this->participantsNumber = participantsNumber;
    this->link = link;
}

/**
 * Getter for the title of the event
 */
std::string Event::getTitle() const {
    return title;
}

/**
 * Getter for the description of the event
 */
std::string Event::getDescription() const {
    return description;
}

/**
 * Getter for the date of the event
 */
std::string Event::getDate() const {
    return date;
}

/**
 * Getter for the time of the event
 */
std::string Event::getTime() const {
    return time;
}

/**
 * Getter for the number of participants of the event
 */
int Event::getParticipantsNumber() const {
    return participantsNumber;
}

/**
 * Getter for the link of the event
 */
std::string Event::getLink() const {
    return link;
}

/**
 * Setter for the title of the event
 * @param newTitle - the new title of the event
 */
void Event::setTitle(const std::string& newTitle) {
    title = newTitle;
};

/**
 * Setter for the description of the event
 * @param newDescription - the new description of the event
 */
void Event::setDescription(const std::string &newDescription) {
    description = newDescription;
}

/**
 * Setter for the date of the event
 * @param newDate - the new date of the event
 */
void Event::setDate(const std::string &newDate) {
    date = newDate;
}

/**
 * Setter for the time of the event
 * @param newTime - the new time of the event
 */
void Event::setTime(const std::string &newTime) {
    time = newTime;
}

/**
 * Setter for the number of participants of the event
 * @param newParticipantsNumber - the new number of participants of the event
 */
void Event::setParticipantsNumber(int newParticipantsNumber) {
    participantsNumber = newParticipantsNumber;
}

/**
 * Setter for the link of the event
 * @param newLink - the new link of the event
 */
void Event::setLink(const std::string &newLink) {
    link = newLink;
}

/**
 * @return a string representation of the event
 */
std::string Event::toString() const {
    std::string ans = "Title: " + title + ", Date: " + date;
    return ans;
}

/**
 * @return a detailed string representation of the event
 */
//std::string Event::toStringDetailed() const {
//    std::string ans = "Title: " + title + ", Description: " + description + ", Date: " + date + ", Time: " + time
//            + ", Number of Participants: " + std::to_string(participantsNumber) + ", Link: " + link;
//    return ans;
//}

std::string Event::toStringDetailed() const {
    std::string ans = title + " - " + description + " - " + date + " - " + time + " - " + std::to_string(participantsNumber) + " - " + link;
    return ans;
}

/**
 * @param other
 * @return true if the two events are equal, false otherwise
 */
bool Event::operator==(const Event &other) const {
    if (title == other.title && date == other.date)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, const Event& event) {
    out << event.getTitle() << " ";
    out << event.getDescription() << " ";
    out << event.getDate() << " ";
    out << event.getTime() << " ";
    out << std::to_string(event.getParticipantsNumber()) << " ";
    out << event.getLink();
    return out;
}

std::istream& operator>>(std::istream& in, Event& event) {
    std::string title, description, date, time, link;
    int participantsNumber;
    in >> title >> description >> date >> time >> participantsNumber >> link;
    event = Event(title, description, date, time, participantsNumber, link);
    return in;
}
