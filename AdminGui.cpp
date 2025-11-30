#include "AdminGui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QString>

AdminGui::AdminGui(QWidget* parent, Service* serv)
    : QWidget(parent), serv(serv) {
    this->setWindowTitle("ADMIN PAGE");
    this->initGui();
    this->populateList();
    this->resize(700, 400);

    connect(addButton, &QPushButton::clicked, this, &AdminGui::addButtonHandler);
    connect(deleteButton, &QPushButton::clicked, this, &AdminGui::deleteButtonHandler);
    connect(updateButton, &QPushButton::clicked, this, &AdminGui::updateButtonHandler);
    connect(exitButton, &QPushButton::clicked, this, &AdminGui::exitButtonHandler);
    
    
    connect(chartButton, &QPushButton::clicked, this, [=]() {
        auto* chart = new MonthChart(nullptr, this->serv);
        chart->setAttribute(Qt::WA_DeleteOnClose);
        chart->show();
        });

    //connect(chartButton, &QPushButton::clicked, this, [=]() {
    //    auto* chartWin = new ChartWindow(this->serv);
    //    chartWin->setAttribute(Qt::WA_DeleteOnClose);  // auto delete
    //    chartWin->show();
    //    });

}

void AdminGui::initGui() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    eventListWidget = new QListWidget{};
    mainLayout->addWidget(eventListWidget);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    QFormLayout* formLayout = new QFormLayout;

    titleEdit = new QLineEdit{};
    descriptionEdit = new QLineEdit{};
    peopleEdit = new QLineEdit{};
    linkEdit = new QLineEdit{};
    yearEdit = new QLineEdit{};
    monthEdit = new QLineEdit{};
    dayEdit = new QLineEdit{};
    hourEdit = new QLineEdit{};
    minuteEdit = new QLineEdit{};


    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("People Going:", peopleEdit);
    formLayout->addRow("Link:", linkEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Month:", monthEdit);
    formLayout->addRow("Day:", dayEdit);
    formLayout->addRow("Hour:", hourEdit);
    formLayout->addRow("Minute:", minuteEdit);

    rightLayout->addLayout(formLayout);

    addButton = new QPushButton("Add");
    deleteButton = new QPushButton("Delete");
    updateButton = new QPushButton("Update");
    chartButton = new QPushButton("Show Monthly Chart"); // store in class field
    exitButton = new QPushButton("Exit");
   // QPushButton* chartButton = new QPushButton("Show Chart"); //added for points


    rightLayout->addWidget(addButton);
    rightLayout->addWidget(deleteButton);
    rightLayout->addWidget(updateButton);
    rightLayout->addWidget(exitButton);
    rightLayout->addWidget(chartButton); // make sure it appears

    mainLayout->addLayout(rightLayout);
}

void AdminGui::populateList() {
    eventListWidget->clear();
    for (const auto& ev : serv->getAllEvents()) {
        QString item = QString::fromStdString(ev.get_title() + " | " +
            ev.get_description() + " | " +
            std::to_string(ev.get_no_of_people()) + " | " +
            ev.get_date().date_to_string()+ " | " + ev.get_link());
        eventListWidget->addItem(item);
    }
}

void AdminGui::clearInputs() {
    titleEdit->clear();
    descriptionEdit->clear();
    peopleEdit->clear();
    linkEdit->clear();
    yearEdit->clear();
    monthEdit->clear();
    dayEdit->clear();
    hourEdit->clear();
    minuteEdit->clear();
}

void AdminGui::addButtonHandler() {
    try {
        std::string title = titleEdit->text().toStdString();
        std::string description = descriptionEdit->text().toStdString();
        std::string link = linkEdit->text().toStdString();
        int people = std::stoi(peopleEdit->text().toStdString());
        int year = std::stoi(yearEdit->text().toStdString());
        int month = std::stoi(monthEdit->text().toStdString());
        int day = std::stoi(dayEdit->text().toStdString());
        int hour = std::stoi(hourEdit->text().toStdString());
        int minute = std::stoi(minuteEdit->text().toStdString());

        DateTime date(year, month, day, hour, minute);
        serv->addEvent(title, description, date, people, link);
        populateList();
        clearInputs();
        QMessageBox::information(this, "Success", "Event added!");
    }
    catch (ValidationException& e) {
        QMessageBox::warning(this, "Validation Error", QString::fromStdString(e.getMessage()));
    }
    catch (...) {
        QMessageBox::warning(this, "Error", "Invalid input format.");
    }
}

//toDo make clearing of inputs
void AdminGui::deleteButtonHandler() {
    try {
        std::string link = linkEdit->text().toStdString();
        serv->removeEvent(link);
        populateList();
        clearInputs();// here
        QMessageBox::information(this, "Success", "Event deleted!");
    }
    catch (ValidationException& e) {
        QMessageBox::warning(this, "Validation Error", QString::fromStdString(e.getMessage()));
    }
}

void AdminGui::updateButtonHandler() {
    try {
        std::string title = titleEdit->text().toStdString();
        std::string description = descriptionEdit->text().toStdString();
        std::string link = linkEdit->text().toStdString();
        int people = std::stoi(peopleEdit->text().toStdString());
        int year = std::stoi(yearEdit->text().toStdString());
        int month = std::stoi(monthEdit->text().toStdString());
        int day = std::stoi(dayEdit->text().toStdString());
        int hour = std::stoi(hourEdit->text().toStdString());
        int minute = std::stoi(minuteEdit->text().toStdString());

        DateTime date(year, month, day, hour, minute);
        serv->updateEvent(link, title, description, date, people);
        populateList();
        clearInputs(); //and here
        QMessageBox::information(this, "Success", "Event updated!");
    }
    catch (ValidationException& e) {
        QMessageBox::warning(this, "Validation Error", QString::fromStdString(e.getMessage()));
    }
    catch (...) {
        QMessageBox::warning(this, "Error", "Invalid input format.");
    }
}

void AdminGui::exitButtonHandler() {
    this->close();
}
