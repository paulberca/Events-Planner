#include "repo.h"
#include "../exceptions/Exception.h"

/**
 * Default constructor for the Repo class
 */
Repo::Repo() = default;

/**
 * Adds an event to the repository
 * @param event - the event to be added
 * @return the event that was added
 */
Event Repo::add(const Event& event) {
    auto it = std::find(repo.begin(), repo.end(), event);
    if (it != repo.end())
        throw RepoException("Event is already in the list");
    repo.push_back(event);
    return event;
}

/**
 * removes an event from the repository
 * @param event
 * @return
 */
Event Repo::remove(const Event &event) {
    auto it = std::find(repo.begin(), repo.end(), event);
    if (it != repo.end()) {
        Event removed = *it;
        repo.erase(it);
        return removed;
    }
    throw RepoException("repo.cpp: Event not found");
}

void Repo::clear() {
    repo.clear();
}

void Repo::push_back(const Event& event) {
    repo.push_back(event);
}

/**
 * Updates an event in the repository
 * @param event - the event to be updated
 * @return the updated event
 */
Event& Repo::operator[](int index) {
    if (index > repo.size())
        throw RepoException("repo.cpp: Index out of range");
    return repo[index];
}

/**
 * @return the size of the repository
 */
unsigned long long Repo::getSize() const {
    return repo.size();
}

bool Repo::operator==(const Repo &other) const {
    return repo == other.repo;
}

//void Repo::saveToFile(const std::string &filename) {
//    std::ofstream outputFile(filename);
//    if (!outputFile.is_open())
//        throw RepoException("repo.cpp: Could not open file");
//
//    for (const auto & event : repo) {
//        outputFile << event << '\n';
//    }
//
//    outputFile.close();
//}
//
//void Repo::loadFromFile(const std::string &filename) {
//    std::ifstream inputFile(filename);
//    if (!inputFile.is_open())
//        throw RepoException("repo.cpp: Could not open file");
//
//    repo.clear();
//    while (!inputFile.eof()) {
//        Event event;
//        inputFile >> event;
//        if (!event.getTitle().empty())
//            repo.push_back(event);
//    }
//
//    inputFile.close();
//}
