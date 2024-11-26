#pragma once
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>
#include "../repo/repo.h"
#include "../exceptions/Exception.h"

class FileRepo {
protected:
    std::string fileName;
    std::string openWithCommand;

public:
    FileRepo();

    virtual void writeToFile(Repo &repo);
    void loadFromFile(Repo &repo);
    virtual void openFile() const;
};


class CSVFile : public FileRepo {
public:
    CSVFile();

    void writeToFile(Repo &repo) override;
};


class HTMLFile : public FileRepo {
public:
    HTMLFile();

    void writeToFile(Repo &repo) override;
};
