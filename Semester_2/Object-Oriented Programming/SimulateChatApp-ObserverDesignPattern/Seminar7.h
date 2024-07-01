#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Seminar7.h"

class Seminar7 : public QMainWindow
{
    Q_OBJECT

public:
    Seminar7(QWidget *parent = nullptr);
    ~Seminar7();

private:
    Ui::Seminar7Class ui;
};
