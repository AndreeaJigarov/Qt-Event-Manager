#include "ChartWindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <algorithm>

MonthChart::MonthChart(QWidget* parent, Service* serv) : QWidget(parent), serv(serv) {
    this->setWindowTitle("Events per Month Chart");
    this->resize(700, 400);
    this->calculateMonthCounts();

    monthLabels = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    colors = { Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta,
               Qt::gray, Qt::darkRed, Qt::darkGreen, Qt::darkBlue, Qt::darkCyan, Qt::darkMagenta };
}

//void MonthChart::calculateMonthCounts() {
//    auto events = serv->getAllEvents();
//    monthCounts.clear();
//
//    for (const auto& ev : events) {
//        int month = ev.get_date().getMonth();
//        monthCounts[month]++;
//    }
//}
void MonthChart::calculateMonthCounts() {
    monthCounts.clear();
    for (int i = 1; i <= 12; ++i)
        monthCounts[i] = 0;

    auto events = serv->getAllEvents();
    for (const auto& ev : events) {
        int month = ev.get_date().getMonth();// 1 to 12
        monthCounts[month]++;
    }
}

//void MonthChart::paintEvent(QPaintEvent* event) {
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing); //smoother lines
//
//    int left = 50;
//    int bottom = height() - 50;
//    int top = 50;
//    int barWidth = 40;
//
//    int maxCount = 0;
//    for (const auto& [month, count] : monthCounts)
//        maxCount = std::max(maxCount, count); //tofind max nr of events in any month, to scale bars proportionally
//
//    painter.drawLine(left, bottom, left + 12 * barWidth + 20, bottom); // X-axis - long for all 12 bars and 20 more for space
//    painter.drawLine(left, top, left, bottom); // Y-axis (Xa,Ya)->(Xb,Yb)
//
//    for (int i = 1; i <= 12; ++i) {
//        int x = left + (i - 1) * barWidth + 10; //calculate x position of current bar
//        
//        //ADDED THIS
//        int count = 0;
//        auto it = monthCounts.find(i);
//        if (it != monthCounts.end())
//            count = it->second;
//        //FINAL
//        int barHeight = (count * (bottom - top)) / (maxCount == 0 ? 1 : maxCount);// calculate height of bar based on event count
//        //                                   max height   /   maxcount (if all 0, divide by 1 ;else divide by maxCount)
//        int y = bottom - barHeight; //y coordinate where beggins
//
//        painter.setBrush(colors[i - 1]);
//        painter.drawRect(x, y, barWidth - 10, barHeight);
//                              // cat de lat    cat de lung
//        //rotate month labels
//        painter.save();
//        painter.translate(x + 5, bottom + 15); //moves to position bellow the bar
//        painter.rotate(45); // to write on diagonal
//        painter.drawText(0, 0, monthLabels[i - 1]);
//        painter.restore(); //restore orientation
//    }
//
//    // Y-axis labels  
//    int yTicks = 4; //for 0 , 25%, 50%, 75% and 100
//    for (int i = 0; i <= yTicks; ++i) {
//        int y = bottom - i * (bottom - top) / yTicks; //compute how high the line should go
//        int val = i * maxCount / yTicks; //computed after the maximum
//        painter.drawText(left - 30, y + 5, QString::number(val));
//        painter.drawLine(left - 5, y, left, y);
//        
//    }
//
//    painter.drawText(width() / 2 - 30, bottom + 40, "Month");
//    painter.drawText(10, top - 10, "Events");
//}

void MonthChart::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//smoother lines

    int left = 50;
    int bottom = height() - 50;
    int top = 50;
    int barWidth = 40;

    //Calculate maxCount for scaling
    int maxCount = 0;
    for (const auto& [month, count] : monthCounts)
        maxCount = std::max(maxCount, count);

    //Ensure maxCount is at least 1 to avoid divide-by-zero
    maxCount = std::max(maxCount, 1); //tofind max nr of events in any month, to scale bars proportionally

    //Draw axes
    painter.drawLine(left, bottom, left + 12 * barWidth + 20, bottom); // X-axis
    painter.drawLine(left, top, left, bottom); // Y-axis

    //Draw bars
    for (int i = 1; i <= 12; ++i) {
        int x = left + (i - 1) * barWidth + 10;

        int count = 0;
        auto it = monthCounts.find(i);
        if (it != monthCounts.end())
            count = it->second;

        int barHeight = (count * (bottom - top)) / maxCount;
        int y = bottom - barHeight;

        painter.setBrush(colors[i - 1]);
        painter.drawRect(x, y, barWidth - 10, barHeight);

        //rotate and draw month label
        painter.save();
        painter.translate(x + (barWidth - 10) / 2, bottom + 15);
        painter.rotate(45);
        painter.drawText(0, 0, monthLabels[i - 1]);
        painter.restore();
    }

    //draw Y-axis ticks
    int yTicks = std::min(maxCount, 10); //Up to 10 ticks max
    for (int i = 0; i <= yTicks; ++i) {
        int y = bottom - i * (bottom - top) / yTicks; //compute how high the tick should go
        int val = (i * maxCount + yTicks / 2) / yTicks; //computed after the maximum

        painter.drawLine(left - 5, y, left, y);
        painter.drawText(left - 35, y + 5, QString::number(val));
    }

    // Axis labels
    painter.drawText(width() / 2 - 30, bottom + 40, "Month");
    painter.drawText(10, top - 10, "Events");
}
