#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Service.h"
#include "ChartWindow.h"

class AdminGui : public QWidget {
    Q_OBJECT

private:
    Service* serv;

    QListWidget* eventListWidget;

    QLineEdit* titleEdit;
    QLineEdit* descriptionEdit;
    QLineEdit* peopleEdit;
    QLineEdit* linkEdit;
    QLineEdit* yearEdit;
    QLineEdit* monthEdit;
    QLineEdit* dayEdit;
    QLineEdit* hourEdit;
    QLineEdit* minuteEdit;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* exitButton;

    QPushButton* chartButton; // added this

    void initGui();
    void populateList();
    void clearInputs();

public:
    AdminGui(QWidget* parent = nullptr, Service* serv = nullptr);

private slots:
    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
    void exitButtonHandler();
};
