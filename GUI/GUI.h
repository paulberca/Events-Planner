#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <vector>
#include "../services/services.h"

class  GUI : public QWidget {
private:
    int windowHeight, windowWidth;
    int buttonHeight, buttonWidth;
    int layoutSpacing;
    Services controller;

    QStackedWidget *stackedWidget;
    QWidget *fileMenu;
    QWidget *mainMenu;
    QWidget *adminMenu;
    QWidget *userMenu;
    QWidget *addEventWidget;
    QWidget *removeEventWidget;
    QWidget *updateEventWidget;
    QWidget *seeAllEventsWidget;
    QWidget *getEventsFromMonthWidget;
    QWidget *removeUserEventWidget;
    QWidget *seeAllUserEventsWidget;

    // File menu buttons
    QPushButton *CSVButton;
    QPushButton *HTMLButton;

    // Main menu buttons
    QPushButton *adminButton;
    QPushButton *userButton;
    QPushButton *exitButton;

    // Admin menu buttons
    QPushButton *addEventButton;
    QPushButton *removeEventButton;
    QPushButton *updateEventButton;
    QPushButton *seeAllEventsButton;

    // User menu buttons
    QPushButton *seeEventsButton;
    QPushButton *deleteEventButton;
    QPushButton *seeUserEventsButton;
    QPushButton *openFileButton;

    // Add Event form inputs
    QLineEdit *titleInput;
    QLineEdit *descriptionInput;
    QLineEdit *dateInput;
    QLineEdit *timeInput;
    QLineEdit *participantsInput;
    QLineEdit *linkInput;
    QPushButton *submitAddEventButton;
    QPushButton *addEventBackButton;

    // Remove Event form inputs
    QLineEdit *removeTitleInput;
    QLineEdit *removeDateInput;
    QPushButton *submitRemoveEventButton;
    QPushButton *removeEventBackButton;

    // Update Event form inputs
    QLineEdit *currentTitleInput;
    QLineEdit *currentDateInput;
    QLineEdit *newTitleInput;
    QLineEdit *newDescriptionInput;
    QLineEdit *newDateInput;
    QLineEdit *newTimeInput;
    QLineEdit *newParticipantsInput;
    QLineEdit *newLinkInput;
    QPushButton *submitUpdateEventButton;
    QPushButton *updateEventBackButton;

    // See All Events widgets
    QTextEdit *eventsDisplay;
    QPushButton *seeAllEventsBackButton;

    // Get Events From Month widgets
    QComboBox *monthComboBox;
    QTextEdit *monthEventsDisplay;
    QPushButton *signUpButton;
    QPushButton *nextEventButton;
    QPushButton *getEventsFromMonthBackButton;
    Repo currentMonthEvents;
    int currentEventIndex;

    // Remove User Event widgets
    QLineEdit *removeUserTitleInput;
    QLineEdit *removeUserDateInput;
    QPushButton *submitRemoveUserEventButton;
    QPushButton *removeUserEventBackButton;

    // See All Events widgets
    QTextEdit *userEventsDisplay;
    QPushButton *seeAllUserEventsBackButton;

    void setupFileType();
    void CSVFileChosen();
    void HTMLFileChosen();

    void setupMainMenu();
    void setupAdminMenu();
    void setupUserMenu();
    void setupAddEventWidget();
    void setupRemoveEventWidget();
    void setupUpdateEventWidget();
    void setupSeeAllEventsWidget();
    void setupGetEventsFromMonthWidget();
    void setupRemoveUserEventWidget();
    void setupSeeAllUserEventsWidget();

    void showAdminMenu();
    void showUserMenu();
    void backToAdminMenu();
    void backToUserMenu();
    void showAddEventWidget();
    void showRemoveEventWidget();
    void showUpdateEventWidget();
    void showSeeAllEventsWidget();
    void showGetEventsFromMonthWidget();
    void showRemoveUserEventWidget();
    void showSeeAllUserEventsWidget();
    void addEvent();
    void removeEvent();
    void updateEvent();
    void getEventsFromMonth();
    void showEventDetails();
    void signUpForEvent();
    void showNextEvent();
    void removeUserEvent();
    void openChosenFile();

public:
    explicit GUI(QWidget *parent = nullptr);
};
