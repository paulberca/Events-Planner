#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include "../repo/repo.h"
#include "../fileData/fileRepo.h"
#include "../exceptions/Exception.h"

class Services {
private:
    Repo repo;
    Repo userRepo;
    FileRepo fileRepo;
    FileRepo* chosenFile;

public:
    std::string fileType;
    explicit Services(const std::string& fileType);
    ~Services();

    std::string get_all_events(Repo repository);
    void addNewEvent(Repo& repository, Event& event);
    void removeEvent(Repo& repository, const std::string& title, const std::string& date);
    void updateEvent(Repo& repository, const std::string& title, const std::string& date,
                     const std::string& newTitle, const std::string& newDescription, const std::string& newDate, const std::string& newTime, int newParticipantsNumber, const std::string& newLink);

    bool inRepo(Repo repository, const std::string& title, const std::string& date);

    Repo getEventsInMonth(const std::string& month);
    Repo& getRepo();
    Repo& getUserRepo();

    void modifyUserCount(Repo& repository, Event& event, int modification);

    static void openURL(const std::string& link);

    void openChosenFile();
    void changeFileType(const std::string& newFileType);
};
