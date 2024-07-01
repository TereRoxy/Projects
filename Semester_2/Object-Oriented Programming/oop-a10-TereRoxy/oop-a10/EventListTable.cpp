#include <QAbstractTableModel>
#include "EventListTable.h"

EventListTable::EventListTable(const std::vector<Event>& events, QObject* parent)
    : QAbstractTableModel(parent), events(events) {}

int EventListTable::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return events.size();
}

int EventListTable::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return headers.size();
}

QVariant EventListTable::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Event& event = events[index.row()];
    switch (index.column()) {
    case 0: return QString::number(event.getPeopleNr());
    case 1: return QString::fromStdString(event.getTitle());
    case 2: return QString::fromStdString(event.getDescription());
    case 3: return QString::fromStdString(event.getDate());
    case 4: return QString::fromStdString(event.getTime());
    case 5: return QString::fromStdString(event.getLink());
    default: return QVariant();
    }
}

QVariant EventListTable::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return headers[section];
    }
    else {
        return QString::number(section + 1);
    }
}

void EventListTable::setEvents(const std::vector<Event>& events) {
    beginResetModel();
    this->events = events;
    endResetModel();
}
