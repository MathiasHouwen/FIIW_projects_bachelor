//
// Created by robin on 16/10/2024.
//

#include "DateTime.h"

DateTime::DateTime(int mHour, int mDay, int mMonth, int mYear)
    : DateTime(0, mHour, mDay, mMonth, mYear) {}

DateTime::DateTime(int mMin, int mHour, int mDay, int mMonth, int mYear) : m_min(mMin), m_hour(mHour), m_day(mDay),
                                                                           m_month(mMonth), m_year(mYear) {}

int DateTime::getMin() const {
    return m_min;
}

int DateTime::getHour() const {
    return m_hour;
}

int DateTime::getDay() const {
    return m_day;
}

int DateTime::getMonth() const {
    return m_month;
}

int DateTime::getYear() const {
    return m_year;
}
