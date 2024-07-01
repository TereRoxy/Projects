#pragma once

#include <QtWidgets>
#include "AdminWindow.h"
#include "UserWindow.h"
#include "ui_EventsManager.h"

class EventsManager : public QMainWindow
{
    Q_OBJECT

public:
    EventsManager(QWidget* parent = nullptr);
    ~EventsManager();
    void setService(Service* serv) {
        service = serv; adminWindow->setService(serv); userWindow->setService(serv);
    };

private slots:
    void handleAdminMode();
    void showMain();
    void handleUserMode();

private:
    //Ui::EventsManagerClass ui;

	Service* service;
    
	void setupUi();
    void connectSignals();

    // Declare UI elements
    QPushButton* adminButton;
    QPushButton* userButton;
    QPushButton* exitButton;
    AdminWindow* adminWindow;
    UserWindow* userWindow;
};
