#include "fileRepo.h"

FileRepo::FileRepo() {
    fileName = "events.txt";
    openWithCommand = "notepad";
}

void FileRepo::writeToFile(Repo &repo) {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open())
        throw RepoException("File could not be opened");

    for (const auto & event : repo) {
        outputFile << event << '\n';
    }

    outputFile.close();
}

void FileRepo::loadFromFile(Repo &repo) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
        throw RepoException("File could not be opened");

    repo.clear();
    while(!inputFile.eof()) {
        Event event;
        inputFile >> event;
        if(!event.getTitle().empty())
            repo.push_back(event);
    }

    inputFile.close();
}

void FileRepo::openFile() const {
    std::string command = openWithCommand + " " + fileName;
    system(command.c_str());
//    ShellExecute(nullptr, "open", fileName.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

/** =========================================================================================== **/

CSVFile::CSVFile() {
    fileName = "events.csv";
    openWithCommand = "notepad";
}

void CSVFile::writeToFile(Repo &repo) {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open())
        throw RepoException("File could not be opened");

    outputFile << "Title,Description,Date,Time,Participants,Link\n";

    for (const auto & event : repo) {
        outputFile << event.getTitle() << ','
                   << event.getDescription() << ','
                   << event.getDate() << ','
                   << event.getTime() << ','
                   << event.getParticipantsNumber() << ','
                   << event.getLink() << '\n';
    }

    outputFile.close();
}

/** =========================================================================================== **/

HTMLFile::HTMLFile() {
    fileName = "events.html";
    openWithCommand = "start";
}

void HTMLFile::writeToFile(Repo &repo) {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open())
        throw RepoException("File could not be opened");

    outputFile << "<!DOCTYPE html>\n"
               << "<html>\n"
               << "<head>\n"
               << "\t<title>Events</title>\n"
               << "</head>\n"
               << "<body>\n"
               << "<table border=\"1\">\n"
               << "\t<tr>\n"
               << "\t\t<th>Title</th>\n"
               << "\t\t<th>Description</th>\n"
               << "\t\t<th>Date</th>\n"
               << "\t\t<th>Time</th>\n"
               << "\t\t<th>Participants</th>\n"
               << "\t\t<th>Link</th>\n"
               << "</tr>\n";

    for (const auto & event : repo) {
        outputFile << "\t<tr>\n"
                   << "\t\t<td>" << event.getTitle() << "</td>\n"
                   << "\t\t<td>" << event.getDescription() << "</td>\n"
                   << "\t\t<td>" << event.getDate() << "</td>\n"
                   << "\t\t<td>" << event.getTime() << "</td>\n"
                   << "\t\t<td>" << event.getParticipantsNumber() << "</td>\n"
                   << "\t\t<td><a href=\"" << event.getLink() << "\">Link</a></td>\n"
                   << "\t</tr>\n";
    }

    outputFile << "</table>\n"
               << "</body>\n"
               << "</html>";

    outputFile.close();
}
