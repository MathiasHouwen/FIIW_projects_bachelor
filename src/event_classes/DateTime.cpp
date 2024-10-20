//
// Created by robin on 16/10/2024.
//

#include <string>
#include <sstream>
#include <iomanip>
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

std::string DateTime::toString() {
    std::ostringstream string;
    string << std::setw(2) << std::setfill('0') << m_day << "-"
        << std::setw(2) << std::setfill('0') << m_month << "-"
        << m_year << " "
        << m_hour << ":"
        << std::setw(2) << std::setfill('0') << m_min;   
    return string.str();
}

DateTime DateTime::parseDateTime(const std::string &input) {
    int day, month, year, hour, min;
    char sep1, sep2, sep3; // '-', '-' en ':'
    std::istringstream iss(input);
    iss >> day >> sep1 >> month >> sep2 >> year >> hour >> sep3 >> min;

    if (sep1 == '-' && sep2 == '-' && sep3 == ':') {
        return DateTime(min, hour, day, month, year);
    } else {
        throw std::invalid_argument("Invalid date format");
    }
}


bool DateTime::operator<(const DateTime &other) const {
    if (this->getYear() != other.getYear())
        return this->getYear() < other.getYear();
    if (this->getMonth() != other.getMonth())
        return this->getMonth() < other.getMonth();
    if (this->getDay() != other.getDay())
        return this->getDay() < other.getDay();
    if (this->getHour() != other.getHour())
        return this->getHour() < other.getHour();
    return this->getMin() < other.getMin();
}