#pragma once
#include<QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Service.h"
#include <QRadioButton>
#include <QApplication>
#include <QButtonGroup>
#include <QFormLayout>
#include <QMessageBox>
#include<QLabel>
#include<QDesktopServices>
#include <QUrl>
class UserGui : public QWidget
{
	Q_OBJECT
private:
	Service* serv;
	std::vector<Event> filteredEvents;
	int currentEventIndex = 0;
	QLabel* currentEventDetails;

	// Format selection
	QRadioButton* csvButton;
	QRadioButton* htmlButton;
	QPushButton* selectFormatButton;

	// Main user window
	QWidget* mainUserWindow;
	QLineEdit* monthEdit;
	QPushButton* parseButton;
	QPushButton* openListButton;
	QPushButton* exitButton;

	// Event browser window
	QWidget* browserWindow;
	QListWidget* personalListWidget;
	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* nextButton;
	QPushButton* doneButton;


	//The 3 main windows in user mode !!!!
	void showFormatSelection();
	void showMainUserWindow();
	void showEventBrowserWindow();

	void displayCurrentEvent();

	void initFormatGui();
	void initMainUserGUI();
	void initEventBrowserGui();

	void populatePersonalList();
	void clearInputs();

public:
	UserGui(QWidget* parent = nullptr, Service* serv = nullptr);
private slots:
	//handlers for main user window
	void formatSelectedHandler();
	void parseButtonHandler();
	void openListHandler();
	void exitHandler();

	//handlers for parse window
	void addButtonHandler();
	void removeButtonHandler();
	void nextButtonHandler();
	void doneButtonHandler();



};