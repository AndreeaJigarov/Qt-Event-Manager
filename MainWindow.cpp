#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    this->initGUI();

    Repository* repo = new TextRepo("file2.txt");
    EventsList* list = new CSVEventsList("list.csv");
    this->service = new Service(repo, list);

    QObject::connect(adminButton, &QPushButton::clicked, this, &MainWindow::adminHandler);
    QObject::connect(userButton, &QPushButton::clicked, this, &MainWindow::userHandler);
}

MainWindow::~MainWindow() {
    delete service;
}

void MainWindow::initGUI() {
    central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    QLabel* title = new QLabel("Welcome to Event Manager");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel* modeLabel = new QLabel("Choose Mode:");
    modeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(modeLabel);

    adminButton = new QPushButton("Admin");
    userButton = new QPushButton("User");

    QHBoxLayout* buttons = new QHBoxLayout();
    buttons->addWidget(adminButton);
    buttons->addWidget(userButton);
    layout->addLayout(buttons);

    setCentralWidget(central);
}

void MainWindow::adminHandler() {
    adminGui = new AdminGui(nullptr, service);
    adminGui->show();
}

void MainWindow::userHandler() {
    userGui = new UserGui(nullptr, service);
    userGui->show();
}
