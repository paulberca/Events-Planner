#include "Exception.h"

bool Validator::validateDate(const std::string &date) {
    if (date.size() != 10)
        return false;
    if (date[0] < '0' || date[0] > '3')
        return false;
    if (date[1] < '0' || date[1] > '9')
        return false;
    if (date[2] != '.')
        return false;
    if (date[3] < '0' || date[3] > '1')
        return false;
    if (date[4] < '0' || date[4] > '9')
        return false;
    if (date[5] != '.')
        return false;
    if (date[6] < '0' || date[6] > '9')
        return false;
    if (date[7] < '0' || date[7] > '9')
        return false;
    if (date[8] < '0' || date[8] > '9')
        return false;
    if (date[9] < '0' || date[9] > '9')
        return false;

    return true;
}

bool Validator::validateTime(const std::string &time) {
    if (time.size() != 5)
        return false;
    if (time[0] < '0' || time[0] > '2')
        return false;
    if (time[1] < '0' || time[1] > '9')
        return false;
    if (time[2] != ':')
        return false;
    if (time[3] < '0' || time[3] > '5')
        return false;
    if (time[4] < '0' || time[4] > '9')
        return false;
    return true;
}
