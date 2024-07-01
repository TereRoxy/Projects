#pragma once

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include "EventListTable.h"

class UserEventsWindow : public QWidget
{
    Q_OBJECT

public:
    UserEventsWindow(QWidget* parent = nullptr);
    ~UserEventsWindow();

    void setEvents(const std::vector<Event>& events);

private:
    QTableView* tableView;
    EventListTable* model;
    QPushButton* closeButton;
    QVBoxLayout* layout;
};
