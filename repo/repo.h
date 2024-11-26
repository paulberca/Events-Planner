#pragma once

#include <vector>
#include <algorithm>
#include "../domain/event.h"

class Repo {
private:
    std::vector<Event> repo;

public:
    Repo();

    Event add(const Event& event);
    Event remove(const Event& event);
    void clear();
    void push_back(const Event& event);

    unsigned long long getSize() const;

    Event& operator[](int index);
    bool operator==(const Repo& other) const;

//    void saveToFile(const std::string& filename = "events.txt");
//    void loadFromFile(const std::string& filename = "events.txt");

    auto begin() {
        return repo.begin();
    }
    auto end() {
        return repo.end();
    }
};
