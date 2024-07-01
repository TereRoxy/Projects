#include "EventsManager.h"

EventsManager::EventsManager(QWidget* parent)
    : QMainWindow(parent)
{
    //Create child windows
    userWindow = new UserWindow;
    adminWindow = new AdminWindow;
	//fileDialog = new SelectFileWindow;
	adminButton = new QPushButton("Admin Mode", this);
	userButton = new QPushButton("User Mode", this);
	exitButton = new QPushButton("Exit", this);
    
    setupUi();
	connectSignals();
}

EventsManager::~EventsManager()
{
	delete userWindow;
	delete adminWindow;
	delete adminButton;
	delete userButton;
	delete exitButton;
    
}

void EventsManager::setupUi()
{
    // Create main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;

    // Add title label
    QLabel* titleLabel = new QLabel("Life after school", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Add buttons for admin mode and user mode
    mainLayout->addWidget(adminButton);
    mainLayout->addWidget(userButton);

    // Add exit button
    mainLayout->addWidget(exitButton);

    // Create central widget and set main layout
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Set window title and size
    setWindowTitle("Life After School");
    resize(300, 200);
}

void EventsManager::connectSignals()
{
	// Connect buttons to slots
	connect(adminButton, &QPushButton::clicked, this, &EventsManager::handleAdminMode);
	connect(userButton, &QPushButton::clicked, this, &EventsManager::handleUserMode);
	connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);
}

void EventsManager::handleAdminMode()
{
	// Handle admin mode
    connect(adminWindow, &AdminWindow::backToMain, this, &EventsManager::showMain);
	adminWindow->show();
	this->hide();
}

void EventsManager::handleUserMode()
{
	// Handle user mode
    
	connect(userWindow, &UserWindow::backToMain, this, &EventsManager::showMain);
	userWindow->showWithDialog();
	this->hide();
}

void EventsManager::showMain()
{
	// Show main window
	show();
	//Hide adminWindow
	if (adminWindow->isVisible())
        adminWindow->hide();

	//Hide userWindow
	if (userWindow->isVisible())
        userWindow->hide();
}