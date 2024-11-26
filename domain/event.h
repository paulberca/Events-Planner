#pragma once

#include <string>

class Event {
private:
    std::string title;
    std::string description;
    std::string date;
    std::string time;
    int participantsNumber;
    std::string link;

public:
    Event();
    Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int participantsNumber, const std::string& link);

    std::string toString() const;
    std::string toStringDetailed() const;

    std::string getTitle() const;
    std::string getDescription() const;
    std::string getDate() const;
    std::string getTime() const;
    int getParticipantsNumber() const;
    std::string getLink() const;

    void setTitle(const std::string& newTitle);
    void setDescription(const std::string& newDescription);
    void setDate(const std::string& newDate);
    void setTime(const std::string& newTime);
    void setParticipantsNumber(int newParticipantsNumber);
    void setLink(const std::string& newLink);

    bool operator==(const Event& other) const;

};

std::ostream& operator<<(std::ostream& out, const Event& event);
std::istream& operator>>(std::istream& in, Event& event);
