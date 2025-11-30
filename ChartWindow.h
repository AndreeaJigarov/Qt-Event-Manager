#pragma once

#include <QWidget>
#include <QVector>
#include <QString>
#include <map>
#include "Service.h"

class MonthChart : public QWidget {
    Q_OBJECT

private:
    Service* serv;
    std::map<int, int> monthCounts;
    QVector<QString> monthLabels;
    QVector<QColor> colors;

    void calculateMonthCounts();

protected:
    void paintEvent(QPaintEvent* event) override;

public:
    MonthChart(QWidget* parent = nullptr, Service* serv = nullptr);
};
