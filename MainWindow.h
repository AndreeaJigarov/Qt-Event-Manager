#pragma once

#include <QMainWindow>
#include <QPushButton>
#include "Service.h"
#include "AdminGui.h"
#include "UserGui.h"
#include "Repository.h"
#include "EventsList.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QWidget* central;
    QPushButton* adminButton;
    QPushButton* userButton;

    Service* service;
    AdminGui* adminGui;
    UserGui* userGui;

    void initGUI();
    void adminHandler();
    void userHandler();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};
