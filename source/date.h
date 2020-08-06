#pragma once

#ifndef SOURCE_DATE_H
#define SOURCE_DATE_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>

using std::istream;
using std::string;
using std::ostream;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
using std::tuple;
using std::setw;
using std::setfill;
using std::to_string;

const string kMonthInvalidArg = "Month value is invalid: ";
const string kDayInvalidArg = "Day value is invalid: ";
const string kDateInvalidString = "Wrong date format: ";
const char kDateSeparator = '-';

class Date {
public:
  Date(int new_year = 1, int new_month = 1, int new_day = 1);

  int GetYear() const;

  int GetMonth() const;

  int GetDay() const;

  tuple<int, int, int> MakeDateTuple() const;

  string ToString() const;

  bool operator<(const Date &rhs) const;

  bool operator<=(const Date &rhs) const;

  bool operator>(const Date &rhs) const;

  bool operator>=(const Date &rhs) const;

  bool operator==(const Date &rhs) const;

  bool operator!=(const Date &rhs) const;

private:
  int year;
  int month;
  int day;
};

istream &operator>>(istream &stream, Date &d);

ostream &operator<<(ostream &stream, const Date &date);

Date ParseDate(istream &is);

#endif //SOURCE_DATE_H
