#pragma once
#include <exception>
#include <string>

class MyException : public std::exception {
private:
    std::string errorMessage;

public:
    explicit MyException(const std::string& message) : errorMessage(message) {}

    MyException(const MyException& other) noexcept : errorMessage(other.errorMessage) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};


class ValidatorException : public MyException {
public:
    explicit ValidatorException(const std::string& message) : MyException(message) {}
};

class RepoException : public MyException {
public:
    explicit RepoException(const std::string& message) : MyException(message) {}};


class Validator {
public:
    static bool validateDate(const std::string& date);
    static bool validateTime(const std::string& time);

};
