#include "GUI.h"
#include <QLabel>
#include <QMessageBox>
#include "../services/services.h"

GUI::GUI(QWidget *parent) : QWidget(parent), controller("placeholder") {
    windowHeight = 600;
    windowWidth = 800;
    buttonHeight = windowHeight / 10;
    buttonWidth = windowWidth / 2;
    layoutSpacing = 20;

    setWindowTitle("Event manager");
    setFixedSize(windowWidth, windowHeight);

    stackedWidget = new QStackedWidget(this);

    setupFileType();
    setupMainMenu();
    setupAdminMenu();
    setupUserMenu();
    setupAddEventWidget();
    setupRemoveEventWidget();
    setupUpdateEventWidget();
    setupSeeAllEventsWidget();
    setupGetEventsFromMonthWidget();
    setupRemoveUserEventWidget();
    setupSeeAllUserEventsWidget();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);

    setLayout(mainLayout);
}

void GUI::setupFileType() {
    fileMenu = new QWidget(this);

    auto *layout = new QVBoxLayout(fileMenu);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(layoutSpacing);

    CSVButton = new QPushButton("CSV File", this);
    HTMLButton = new QPushButton("HTML file", this);

    CSVButton->setFixedSize(buttonWidth, buttonHeight);
    HTMLButton->setFixedSize(buttonWidth, buttonHeight);

    layout->addWidget(CSVButton);
    layout->addWidget(HTMLButton);

    connect(CSVButton, &QPushButton::clicked, this, &GUI::CSVFileChosen);
    connect(HTMLButton, &QPushButton::clicked, this, &GUI::HTMLFileChosen);
    
    stackedWidget->addWidget(fileMenu);
}

void GUI::CSVFileChosen() {
    controller.changeFileType("CSV");
    stackedWidget->setCurrentWidget(mainMenu);
}

void GUI::HTMLFileChosen() {
    controller.changeFileType("HTML");
    stackedWidget->setCurrentWidget(mainMenu);
}

void GUI::setupMainMenu() {
    mainMenu = new QWidget(this);

    auto *layout = new QVBoxLayout(mainMenu);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(layoutSpacing);

    adminButton = new QPushButton("Admin", this);
    userButton = new QPushButton("User", this);
    exitButton = new QPushButton("Exit", this);

    adminButton->setFixedSize(buttonWidth, buttonHeight);
    userButton->setFixedSize(buttonWidth, buttonHeight);
    exitButton->setFixedSize(buttonWidth, buttonHeight);

    layout->addWidget(adminButton);
    layout->addWidget(userButton);
    layout->addWidget(exitButton);

    connect(adminButton, &QPushButton::clicked, this, &GUI::showAdminMenu);
    connect(userButton, &QPushButton::clicked, this, &GUI::showUserMenu);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    stackedWidget->addWidget(mainMenu);
}


// ===================================================================================================


void GUI::setupAdminMenu() {
    adminMenu = new QWidget(this);
    auto *layout = new QVBoxLayout(adminMenu);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(layoutSpacing);

    addEventButton = new QPushButton("Add Event", this);
    removeEventButton = new QPushButton("Remove Event", this);
    updateEventButton = new QPushButton("Update Event", this);
    seeAllEventsButton = new QPushButton("See All Events", this);

    addEventButton->setFixedSize(buttonWidth, buttonHeight);
    removeEventButton->setFixedSize(buttonWidth, buttonHeight);
    updateEventButton->setFixedSize(buttonWidth, buttonHeight);
    seeAllEventsButton->setFixedSize(buttonWidth, buttonHeight);

    layout->addWidget(addEventButton);
    layout->addWidget(removeEventButton);
    layout->addWidget(updateEventButton);
    layout->addWidget(seeAllEventsButton);

    connect(addEventButton, &QPushButton::clicked, this, &GUI::showAddEventWidget);
    connect(removeEventButton, &QPushButton::clicked, this, &GUI::showRemoveEventWidget);
    connect(updateEventButton, &QPushButton::clicked, this, &GUI::showUpdateEventWidget);
    connect(seeAllEventsButton, &QPushButton::clicked, this, &GUI::showSeeAllEventsWidget);

    stackedWidget->addWidget(adminMenu);
}

void GUI::setupAddEventWidget() {
    addEventWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(addEventWidget);

    titleInput = new QLineEdit(this);
    descriptionInput = new QLineEdit(this);
    dateInput = new QLineEdit(this);
    timeInput = new QLineEdit(this);
    participantsInput = new QLineEdit(this);
    linkInput = new QLineEdit(this);
    submitAddEventButton = new QPushButton("Submit", this);
    addEventBackButton = new QPushButton("Back", this);

    layout->addWidget(new QLabel("Title:"));
    layout->addWidget(titleInput);
    layout->addWidget(new QLabel("Description:"));
    layout->addWidget(descriptionInput);
    layout->addWidget(new QLabel("Date:"));
    layout->addWidget(dateInput);
    layout->addWidget(new QLabel("Time:"));
    layout->addWidget(timeInput);
    layout->addWidget(new QLabel("Participants:"));
    layout->addWidget(participantsInput);
    layout->addWidget(new QLabel("Link:"));
    layout->addWidget(linkInput);
    layout->addWidget(submitAddEventButton);
    layout->addWidget(addEventBackButton);

    connect(submitAddEventButton, &QPushButton::clicked, this, &GUI::addEvent);
    connect(addEventBackButton, &QPushButton::clicked, this, &GUI::backToAdminMenu);

    stackedWidget->addWidget(addEventWidget);
}

void GUI::setupRemoveEventWidget() {
    removeEventWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(removeEventWidget);

    removeTitleInput = new QLineEdit(this);
    removeDateInput = new QLineEdit(this);
    submitRemoveEventButton = new QPushButton("Submit", this);
    removeEventBackButton = new QPushButton("Back", this);

    layout->addWidget(new QLabel("Title:"));
    layout->addWidget(removeTitleInput);
    layout->addWidget(new QLabel("Date:"));
    layout->addWidget(removeDateInput);
    layout->addWidget(submitRemoveEventButton);
    layout->addWidget(removeEventBackButton);

    connect(submitRemoveEventButton, &QPushButton::clicked, this, &GUI::removeEvent);
    connect(removeEventBackButton, &QPushButton::clicked, this, &GUI::backToAdminMenu);

    stackedWidget->addWidget(removeEventWidget);
}

void GUI::setupUpdateEventWidget() {
    updateEventWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(updateEventWidget);

    currentTitleInput = new QLineEdit(this);
    currentDateInput = new QLineEdit(this);
    newTitleInput = new QLineEdit(this);
    newDescriptionInput = new QLineEdit(this);
    newDateInput = new QLineEdit(this);
    newTimeInput = new QLineEdit(this);
    newParticipantsInput = new QLineEdit(this);
    newLinkInput = new QLineEdit(this);
    submitUpdateEventButton = new QPushButton("Submit", this);
    updateEventBackButton = new QPushButton("Back", this);

    layout->addWidget(new QLabel("Current Title:"));
    layout->addWidget(currentTitleInput);
    layout->addWidget(new QLabel("Current Date:"));
    layout->addWidget(currentDateInput);
    layout->addWidget(new QLabel("New Title:"));
    layout->addWidget(newTitleInput);
    layout->addWidget(new QLabel("New Description:"));
    layout->addWidget(newDescriptionInput);
    layout->addWidget(new QLabel("New Date:"));
    layout->addWidget(newDateInput);
    layout->addWidget(new QLabel("New Time:"));
    layout->addWidget(newTimeInput);
    layout->addWidget(new QLabel("New Participants:"));
    layout->addWidget(newParticipantsInput);
    layout->addWidget(new QLabel("New Link:"));
    layout->addWidget(newLinkInput);
    layout->addWidget(submitUpdateEventButton);
    layout->addWidget(updateEventBackButton);

    connect(submitUpdateEventButton, &QPushButton::clicked, this, &GUI::updateEvent);
    connect(updateEventBackButton, &QPushButton::clicked, this, &GUI::backToAdminMenu);

    stackedWidget->addWidget(updateEventWidget);
}

void GUI::setupSeeAllEventsWidget() {
    seeAllEventsWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(seeAllEventsWidget);

    eventsDisplay = new QTextEdit(this);
    eventsDisplay->setReadOnly(true);

    seeAllEventsBackButton = new QPushButton("Back", this);

    layout->addWidget(eventsDisplay);
    layout->addWidget(seeAllEventsBackButton);

    connect(seeAllEventsBackButton, &QPushButton::clicked, this, &GUI::backToAdminMenu);

    stackedWidget->addWidget(seeAllEventsWidget);
}

void GUI::showAdminMenu() {
    stackedWidget->setCurrentWidget(adminMenu);
}

void GUI::showAddEventWidget() {
    stackedWidget->setCurrentWidget(addEventWidget);
}

void GUI::showRemoveEventWidget() {
    stackedWidget->setCurrentWidget(removeEventWidget);
}

void GUI::showUpdateEventWidget() {
    stackedWidget->setCurrentWidget(updateEventWidget);
}

void GUI::showSeeAllEventsWidget() {
    try {
        std::string events = controller.get_all_events(controller.getRepo());
        eventsDisplay->setPlainText(QString::fromStdString(events));
        stackedWidget->setCurrentWidget(seeAllEventsWidget);
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error", "An error occurred while fetching events.");
    }
    stackedWidget->setCurrentWidget(seeAllEventsWidget);

}

void GUI::addEvent() {
    QString title = titleInput->text();
    QString description = descriptionInput->text();
    QString date = dateInput->text();
    QString time = timeInput->text();
    int participants = participantsInput->text().toInt();
    QString link = linkInput->text();

    Event event(title.toStdString(), description.toStdString(), date.toStdString(), time.toStdString(), participants, link.toStdString());

    try {
        controller.addNewEvent(controller.getRepo(), event);

        QMessageBox::information(this, "Success", "Event added successfully.");

        titleInput->clear();
        descriptionInput->clear();
        dateInput->clear();
        timeInput->clear();
        participantsInput->clear();
        linkInput->clear();

        stackedWidget->setCurrentWidget(adminMenu);
    } catch (const ValidatorException& ex) {
        QMessageBox::warning(this, "Validation Error", ex.what());
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error", "An error occurred while adding the event.");
    }
}

void GUI::removeEvent() {
    QString title = removeTitleInput->text();
    QString date = removeDateInput->text();

    try {
        controller.removeEvent(controller.getRepo(), title.toStdString(), date.toStdString());

        QMessageBox::information(this, "Success", "Event removed successfully.");

        removeTitleInput->clear();
        removeDateInput->clear();

        stackedWidget->setCurrentWidget(adminMenu);
    } catch (const ValidatorException& ex) {
        QMessageBox::warning(this, "Validation Error", ex.what());
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error", "An error occurred while removing the event.");
    }
}

void GUI::updateEvent() {
    QString currentTitle = currentTitleInput->text();
    QString currentDate = currentDateInput->text();
    QString newTitle = newTitleInput->text();
    QString newDescription = newDescriptionInput->text();
    QString newDate = newDateInput->text();
    QString newTime = newTimeInput->text();
    int newParticipants = newParticipantsInput->text().toInt();
    QString newLink = newLinkInput->text();

    try {
        controller.updateEvent(controller.getRepo(),
                               currentTitle.toStdString(), currentDate.toStdString(),
                               newTitle.toStdString(), newDescription.toStdString(),
                               newDate.toStdString(), newTime.toStdString(),
                               newParticipants, newLink.toStdString());

        QMessageBox::information(this, "Success", "Event updated successfully.");

        currentTitleInput->clear();
        currentDateInput->clear();
        newTitleInput->clear();
        newDescriptionInput->clear();
        newDateInput->clear();
        newTimeInput->clear();
        newParticipantsInput->clear();
        newLinkInput->clear();

        stackedWidget->setCurrentWidget(adminMenu);
    } catch (const ValidatorException& ex) {
        QMessageBox::warning(this, "Validation Error", ex.what());
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error", "An error occurred while updating the event.");
    }
}


// ===================================================================================================


void GUI::setupUserMenu() {
    userMenu = new QWidget(this);
    auto *layout = new QVBoxLayout(userMenu);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(layoutSpacing);

    seeEventsButton = new QPushButton("See Events in a Month", this);
    deleteEventButton = new QPushButton("Delete Event from List", this);
    seeUserEventsButton = new QPushButton("See Signed Up Events", this);
    openFileButton = new QPushButton("Open Chosen File", this);

    seeEventsButton->setFixedSize(buttonWidth, buttonHeight);
    deleteEventButton->setFixedSize(buttonWidth, buttonHeight);
    seeUserEventsButton->setFixedSize(buttonWidth, buttonHeight);
    openFileButton->setFixedSize(buttonWidth, buttonHeight);

    layout->addWidget(seeEventsButton);
    layout->addWidget(deleteEventButton);
    layout->addWidget(seeUserEventsButton);
    layout->addWidget(openFileButton);

    connect(seeEventsButton, &QPushButton::clicked, this, &GUI::showGetEventsFromMonthWidget);
    connect(deleteEventButton, &QPushButton::clicked, this, &GUI::showRemoveUserEventWidget);
    connect(seeUserEventsButton, &QPushButton::clicked, this, &GUI::showSeeAllUserEventsWidget);
    connect(openFileButton, &QPushButton::clicked, this, &GUI::openChosenFile);

    stackedWidget->addWidget(userMenu);
}


void GUI::setupGetEventsFromMonthWidget() {
    getEventsFromMonthWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(getEventsFromMonthWidget);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(layoutSpacing);

    monthComboBox = new QComboBox(this);
    monthComboBox->addItems({"", "all", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"});

    monthEventsDisplay = new QTextEdit(this);
    monthEventsDisplay->setReadOnly(true);
    monthEventsDisplay->setFixedSize(buttonWidth, buttonHeight);

    signUpButton = new QPushButton("Sign Up", this);
    nextEventButton = new QPushButton("Next Event", this);
    getEventsFromMonthBackButton = new QPushButton("Back", this);

    signUpButton->setFixedSize(buttonWidth, buttonHeight);
    nextEventButton->setFixedSize(buttonWidth, buttonHeight);
    getEventsFromMonthBackButton->setFixedSize(buttonWidth, buttonHeight);

    auto label = new QLabel("Select Month:");
    label->setFixedSize(buttonWidth, buttonHeight);
    monthComboBox->setFixedSize(buttonWidth, 25);

    layout->addWidget(label);
    layout->addWidget(monthComboBox);
    layout->addWidget(monthEventsDisplay);
    layout->addWidget(signUpButton);
    layout->addWidget(nextEventButton);
    layout->addWidget(getEventsFromMonthBackButton);

    connect(monthComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GUI::getEventsFromMonth);
    connect(signUpButton, &QPushButton::clicked, this, &GUI::signUpForEvent);
    connect(nextEventButton, &QPushButton::clicked, this, &GUI::showNextEvent);
    connect(getEventsFromMonthBackButton, &QPushButton::clicked, this, &GUI::backToUserMenu);

    stackedWidget->addWidget(getEventsFromMonthWidget);
}

void GUI::showGetEventsFromMonthWidget() {
//    getEventsFromMonth();
    stackedWidget->setCurrentWidget(getEventsFromMonthWidget);
}

void GUI::getEventsFromMonth() {
    QString month = monthComboBox->currentText();
    currentMonthEvents = controller.getEventsInMonth(month.toStdString());
    currentEventIndex = 0;
    showEventDetails();
}

void GUI::showEventDetails() {
    if (currentMonthEvents.getSize() == 0) {
        monthEventsDisplay->setPlainText("No events found for the selected month.");
        signUpButton->setDisabled(true);
        nextEventButton->setDisabled(true);
    } else {
        const Event &event = currentMonthEvents[currentEventIndex];
        monthEventsDisplay->setPlainText(QString::fromStdString(event.toStringDetailed()));
        signUpButton->setEnabled(true);
        nextEventButton->setEnabled(true);
    }
}

void GUI::signUpForEvent() {
    try {
        Event &event = currentMonthEvents[currentEventIndex];
        controller.addNewEvent(controller.getUserRepo(), event);
        controller.modifyUserCount(controller.getUserRepo(), event, 1);
        controller.modifyUserCount(controller.getRepo(), event, 1);
        QMessageBox::information(this, "Success", "Signed up for event successfully.");
        showNextEvent();
    } catch (const RepoException &e) {
        QMessageBox::warning(this, "Error", e.what());
    } catch (const ValidatorException &e) {
        QMessageBox::warning(this, "Validation Error", e.what());
    }
}

void GUI::showNextEvent() {
    currentEventIndex++;
    if (currentEventIndex >= currentMonthEvents.getSize()) {
        QString month = monthComboBox->currentText();
        currentMonthEvents = controller.getEventsInMonth(month.toStdString());
        currentEventIndex = 0;
    }
    showEventDetails();
}

void GUI::setupRemoveUserEventWidget() {
    removeUserEventWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(removeUserEventWidget);

    removeUserTitleInput = new QLineEdit(this);
    removeUserDateInput = new QLineEdit(this);
    submitRemoveUserEventButton = new QPushButton("Submit", this);
    removeUserEventBackButton = new QPushButton("Back", this);

    layout->addWidget(new QLabel("Title:"));
    layout->addWidget(removeUserTitleInput);
    layout->addWidget(new QLabel("Date:"));
    layout->addWidget(removeUserDateInput);
    layout->addWidget(submitRemoveUserEventButton);
    layout->addWidget(removeUserEventBackButton);

    connect(submitRemoveUserEventButton, &QPushButton::clicked, this, &GUI::removeUserEvent);
    connect(removeUserEventBackButton, &QPushButton::clicked, this, &GUI::backToUserMenu);

    stackedWidget->addWidget(removeUserEventWidget);
}

void GUI::removeUserEvent() {
    QString title = removeUserTitleInput->text();
    QString date = removeUserDateInput->text();

    try {
        controller.removeEvent(controller.getUserRepo(), title.toStdString(), date.toStdString());
        Event event = Event(title.toStdString(), "", date.toStdString(), "", 0, "");
        controller.modifyUserCount(controller.getUserRepo(), event, -1);
        controller.modifyUserCount(controller.getRepo(), event, -1);

        QMessageBox::information(this, "Success", "Event removed successfully.");

        removeUserTitleInput->clear();
        removeUserDateInput->clear();

        stackedWidget->setCurrentWidget(userMenu);
    } catch (const ValidatorException& ex) {
        QMessageBox::warning(this, "Validation Error", ex.what());
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error", "An error occurred while removing the event.");
    }
}

void GUI::showRemoveUserEventWidget() {
    stackedWidget->setCurrentWidget(removeUserEventWidget);
}

void GUI::openChosenFile() {
    controller.openChosenFile();
}

void GUI::showUserMenu() {
    stackedWidget->setCurrentWidget(userMenu);
}

void GUI::setupSeeAllUserEventsWidget() {
    seeAllUserEventsWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(seeAllUserEventsWidget);

    userEventsDisplay = new QTextEdit(this);
    userEventsDisplay->setReadOnly(true);

    seeAllUserEventsBackButton = new QPushButton("Back", this);

    layout->addWidget(userEventsDisplay);
    layout->addWidget(seeAllUserEventsBackButton);

    connect(seeAllUserEventsBackButton, &QPushButton::clicked, this, &GUI::backToUserMenu);

    stackedWidget->addWidget(seeAllUserEventsWidget);
}

void GUI::showSeeAllUserEventsWidget() {
    try {
        std::string events = controller.get_all_events(controller.getUserRepo());
        userEventsDisplay->setPlainText(QString::fromStdString(events));
        stackedWidget->setCurrentWidget(seeAllUserEventsWidget);
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error", "An error occurred while fetching events.");
    }
    stackedWidget->setCurrentWidget(seeAllUserEventsWidget);

}

// ========================================================================================

void GUI::backToAdminMenu() {
    stackedWidget->setCurrentWidget(adminMenu);
}

void GUI::backToUserMenu() {
    stackedWidget->setCurrentWidget(userMenu);
}
