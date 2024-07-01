#pragma once

#include <QAbstractTableModel>
#include <vector>
#include "Event.h"

class EventListTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    EventListTable(const std::vector<Event>& events, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setEvents(const std::vector<Event>& events);

private:
    std::vector<Event> events;
    QStringList headers = { "People Attending", "Title", "Description", "Date", "Time", "Link" };
};