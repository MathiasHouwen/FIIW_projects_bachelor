//
// Created by robin on 16/10/2024.
//

#ifndef DATETIME_H
#define DATETIME_H

#include <string>

class DateTime {
public:
    DateTime(int mHour, int mDay, int mMonth, int mYear);
    DateTime(int mMin, int mHour, int mDay, int mMonth, int mYear);

    int getMin() const;
    int getHour() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    std::string toString();

private:
    int m_min;
    int m_hour;
    int m_day;
    int m_month;
    int m_year;
};

#endif //DATETIME_H