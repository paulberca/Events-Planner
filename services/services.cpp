#include "services.h"

/**
 */
Services::Services(const std::string& fileType) : fileType(fileType), chosenFile(nullptr) {
    fileRepo.loadFromFile(repo);
    if (fileType == "CSV")
        chosenFile = new CSVFile;
    else if (fileType == "HTML" || fileType == "placeholder")
        chosenFile = new HTMLFile;
    else throw ValidatorException("services.cpp: Invalid file type");
    chosenFile->writeToFile(userRepo);
}

/**
 * Function that returns all events from the repository
 * @return a string containing all events from the repository
 */
std::string Services::get_all_events(Repo repository) {
    fileRepo.loadFromFile(repo);
    std::string ans;
    for (auto & i : repository)
        ans += i.toStringDetailed() + '\n';
    return ans; }


/**
 * Function that adds a new event to the repository
 * @param title of the event
 * @param description of the event
 * @param date of the event
 * @param time of the event
 * @param participantsNumber of the event
 * @param link of the event
 */
void Services::addNewEvent(Repo& repository, Event& event) {
    if (!Validator::validateDate(event.getDate()) || !Validator::validateTime(event.getTime()))
        throw ValidatorException("services.cpp: Invalid date or time");
    repository.add(event);
    if (repository == repo) {
        fileRepo.writeToFile(repo);
    }
    else {
        chosenFile->writeToFile(userRepo);
    }
}

/**
 * Function that removes an event from the repository
 * @param title of the event
 * @param date of the event
 */
void Services::removeEvent(Repo& repository, const std::string &title, const std::string &date) {
    if (!Validator::validateDate(date))
        throw ValidatorException("services.cpp: Invalid date");
    repository.remove(Event(title, "", date, "", 0, ""));
    if (repository == repo) {
        fileRepo.writeToFile(repo);
    }
    else {
        chosenFile->writeToFile(userRepo);
    }
}

/**
 * Function that updates an event from the repository
 * @param title of the event to be changed
 * @param date of the event to be changed
 * @param newTitle of the event
 * @param newDescription of the event
 * @param newDate of the event
 * @param newTime of the event
 * @param newParticipantsNumber of the event
 * @param newLink of the event
 */
void Services::updateEvent(Repo& repository, const std::string &title, const std::string &date, const std::string &newTitle, const std::string &newDescription, const std::string &newDate, const std::string &newTime, int newParticipantsNumber, const std::string &newLink) {
    if (!Validator::validateDate(date) || !Validator::validateDate(newDate) || !Validator::validateTime(newTime))
        throw ValidatorException("serivces.cpp: Invalid date or time");
    Event removed_event = repository.remove(Event(title, "", date, "", 0, ""));
    try {
        repository.add(Event(newTitle, newDescription, newDate, newTime, newParticipantsNumber, newLink));
        if (repository == repo) {
            fileRepo.writeToFile(repo);
        }
        else {
            chosenFile->writeToFile(userRepo);
        }
    } catch (const RepoException &e) {
        repository.add(removed_event);
        if (repository == repo) {
            fileRepo.writeToFile(repo);
        }
        else {
            chosenFile->writeToFile(userRepo);
        }
        throw e;
    }
}

/**
 * @param title of the event
 * @param date of the event
 * @return true if the event is in the repository, false otherwise
 */
bool Services::inRepo(Repo repository, const std::string &title, const std::string &date) {
    fileRepo.loadFromFile(repo);
    auto it = std::find(repository.begin(), repository.end(), Event(title, "", date, "", 0, ""));
    if (it != repository.end())
        return true;
    return false;
}

Repo Services::getEventsInMonth(const std::string &month) {
    if (month.empty()) {
        Repo empty;
        return empty;
    }
    fileRepo.loadFromFile(repo);
    Repo ans;
    for (auto & i : repo) {
            if (month == "all" || std::stoi(i.getDate().substr(3, 2)) == std::stoi(month))
                ans.add(i);
    }
    return ans; }

Repo& Services::getRepo() {
    return repo;
}

Repo& Services::getUserRepo() {
    return userRepo;
}

/**
 * Function that increments the number of participants of an event
 * @param event
 */
void Services::modifyUserCount(Repo& repository, Event &event, int modification) {
    for (auto & i : repository) {
        if (i == event) {
            i.setParticipantsNumber(i.getParticipantsNumber() + modification);
            if (repository == repo) {
                fileRepo.writeToFile(repo);
            }
            else {
                chosenFile->writeToFile(userRepo);
            }
            return;
        }
    }
}

/**
 * Function that opens a link in the default browser
 * @param link
 */
void Services::openURL(const std::string &link) {
    //ShellExecute(nullptr, "open", link.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

void Services::openChosenFile() {
    chosenFile->openFile();
}

Services::~Services() {
    delete chosenFile;
}


void Services::changeFileType(const std::string &newFileType) {
    fileType = newFileType;
    if (newFileType == "CSV") {
        chosenFile = new CSVFile;
        chosenFile->writeToFile(userRepo);
    }
    else if (newFileType == "HTML") {
        chosenFile = new HTMLFile;
        chosenFile->writeToFile(userRepo);
    }
    else throw ValidatorException("services.cpp: Invalid change file type");
}
