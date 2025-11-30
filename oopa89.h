#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_oopa89.h"

class oopa89 : public QMainWindow
{
    Q_OBJECT

public:
    oopa89(QWidget *parent = nullptr);
    ~oopa89();

private:
    Ui::oopa89Class ui;
};
