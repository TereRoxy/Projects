#include "UserEventsWindow.h"

//UserEventsWindow::UserEventsWindow(QWidget* parent)
//    : QWidget(parent)
//{
//    model = new EventListTable({}, this);
//    tableView = new QTableView(this);
//    tableView->setModel(model);
//
//    closeButton = new QPushButton("Close", this);
//    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
//
//    layout = new QVBoxLayout(this);
//    layout->addWidget(tableView);
//    layout->addWidget(closeButton);
//
//    setLayout(layout);
//    setWindowTitle("User Events");
//    resize(800, 600);
//}

UserEventsWindow::UserEventsWindow(QWidget* parent)
    : QWidget(parent), tableView(new QTableView(this)), model(new EventListTable({}, this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    tableView->setModel(model);
    setLayout(layout);

    setWindowTitle("User Events"); // Set window title
    resize(600, 400); // Set window size
}

UserEventsWindow::~UserEventsWindow()
{
}

void UserEventsWindow::setEvents(const std::vector<Event>& events) {
    model->setEvents(events);
}
