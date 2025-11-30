#include "UserGui.h"


UserGui::UserGui(QWidget* parent, Service* serv): QWidget(parent), serv(serv)
{
	this->setWindowTitle("USER MODE");
	this->initFormatGui();
	this->resize(400, 200);
}

void UserGui::initFormatGui()
{
	QVBoxLayout* wind_layout = new QVBoxLayout(this);
	QHBoxLayout* layout = new QHBoxLayout(this);
	csvButton = new QRadioButton("CSV");
	htmlButton = new QRadioButton("HTML");
	selectFormatButton = new QPushButton("Ok");

	layout->addWidget(csvButton);
	layout->addWidget(htmlButton);
	wind_layout->addLayout(layout);
	wind_layout->addWidget(selectFormatButton);

	connect(selectFormatButton, &QPushButton::clicked, this, &UserGui::formatSelectedHandler);

}

void UserGui::formatSelectedHandler() {
	if (csvButton->isChecked())
		serv->setEventsList(new CSVEventsList{ "list.csv" });
	else if (htmlButton->isChecked())
		serv->setEventsList(new HTMLEventsList{ "list.html" });
	else {
		QMessageBox::warning(this, "Warning", "Please select a format.");
		return;
	}

	this->hide();
	this->showMainUserWindow();
}

void UserGui::initMainUserGUI() {
	mainUserWindow = new QWidget();
	QVBoxLayout* layout = new QVBoxLayout(mainUserWindow);

	QFormLayout* formLayout = new QFormLayout;
	monthEdit = new QLineEdit();
	formLayout->addRow("Month (0 for all):", monthEdit);

	layout->addLayout(formLayout);
	parseButton = new QPushButton("Parse Events");
	openListButton = new QPushButton("Open List Externally");
	exitButton = new QPushButton("Exit");

	layout->addWidget(parseButton);
	layout->addWidget(openListButton);
	layout->addWidget(exitButton);

	connect(parseButton, &QPushButton::clicked, this, &UserGui::parseButtonHandler);
	connect(openListButton, &QPushButton::clicked, this, &UserGui::openListHandler);
	connect(exitButton, &QPushButton::clicked, this, &UserGui::exitHandler);
}

void UserGui::showFormatSelection()
{
	this->initFormatGui();
	this->show();
}

void UserGui::showMainUserWindow() {
	this->initMainUserGUI();
	mainUserWindow->setWindowTitle("User Panel");
	mainUserWindow->resize(400, 200);
	mainUserWindow->show();
}

void UserGui::initEventBrowserGui() {
	browserWindow = new QWidget();
	browserWindow->setWindowTitle("Browse Events");
	browserWindow->resize(600, 300);

	QHBoxLayout* mainLayout = new QHBoxLayout(browserWindow);
	currentEventDetails = new QLabel;
	currentEventDetails->setWordWrap(true);  // Allow multiline text
	mainLayout->addWidget(currentEventDetails);
	personalListWidget = new QListWidget();

	QVBoxLayout* buttonLayout = new QVBoxLayout;
	addButton = new QPushButton("Add to List");
	removeButton = new QPushButton("Remove from List");
	nextButton = new QPushButton("Next");
	doneButton = new QPushButton("Done");

	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(removeButton);
	buttonLayout->addWidget(nextButton);
	buttonLayout->addWidget(doneButton);

	mainLayout->addWidget(personalListWidget);
	mainLayout->addLayout(buttonLayout);

	connect(addButton, &QPushButton::clicked, this, &UserGui::addButtonHandler);
	connect(removeButton, &QPushButton::clicked, this, &UserGui::removeButtonHandler);
	connect(nextButton, &QPushButton::clicked, this, &UserGui::nextButtonHandler);
	connect(doneButton, &QPushButton::clicked, this, &UserGui::doneButtonHandler);

	populatePersonalList();
	if (!filteredEvents.empty())
		displayCurrentEvent();
}

void UserGui::populatePersonalList()
{
	personalListWidget->clear();
	const auto& list = serv->get_all_from_list();
	for (const auto& event : list) {
		QString itemText = QString::fromStdString(event.get_title() + " | " + event.get_date().date_to_string());
		personalListWidget->addItem(itemText);
	}
}

void UserGui::clearInputs()
{
	monthEdit->clear();
}

void UserGui::showEventBrowserWindow() {
	initEventBrowserGui();
	browserWindow->show();
}

void UserGui::displayCurrentEvent() {
	if (filteredEvents.empty()) {
		currentEventDetails->setText("No events found.");
		return;
	}
	if (currentEventIndex >= filteredEvents.size())
		currentEventIndex = 0;

	const Event& ev = filteredEvents[currentEventIndex];
	QString details = QString::fromStdString(
		"Title: " + ev.get_title() + "\n" +
		"Description: " + ev.get_description() + "\n" +
		"People Going: " + std::to_string(ev.get_no_of_people()) + "\n" +
		"Date: " + ev.get_date().date_to_string() + "\n" +
		"Link: " + ev.get_link()
	);
	currentEventDetails->setText(details);

	// Automatically open browser
	QDesktopServices::openUrl(QUrl(QString::fromStdString(ev.get_link())));
}


void UserGui::parseButtonHandler() {
	try {
		int month = std::stoi(monthEdit->text().toStdString());
		filteredEvents = serv->getEventsmonth(month);
		currentEventIndex = 0;

		if (filteredEvents.empty()) {
			QMessageBox::information(this, "No Events", "No events found for this month.");
			return;
		}
		showEventBrowserWindow();
	}
	catch (...) {
		QMessageBox::warning(mainUserWindow, "Error", "Invalid month input.");
	}
}
void UserGui::openListHandler() {
	serv->open_list();
}

void UserGui::exitHandler()
{
	QApplication::quit();
}

void UserGui::nextButtonHandler() {
	if (filteredEvents.empty()) return;
	currentEventIndex++;
	displayCurrentEvent();
}

void UserGui::addButtonHandler() {
	const Event& ev = filteredEvents[currentEventIndex];
	try {
		if (serv->add_to_list(ev))
			QMessageBox::information(browserWindow, "Success", "Event added to your personal list.");
		else
			QMessageBox::warning(browserWindow, "Duplicate", "Event already in your personal list.");

		populatePersonalList();
	}
	catch (...){
		QMessageBox::warning(browserWindow, "Error", "Invalid month input.");

	}
}


void UserGui::removeButtonHandler() {
	const Event& ev = filteredEvents[currentEventIndex];
	if (serv->remove_from_list(ev))
		QMessageBox::information(browserWindow, "Removed", "Event removed from your personal list.");
	else
		QMessageBox::warning(browserWindow, "Not Found", "This event is not in your personal list.");

	populatePersonalList();
}

void UserGui::doneButtonHandler() {
	browserWindow->close();
}

