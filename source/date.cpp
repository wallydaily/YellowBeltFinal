#include "date.h"

Date::Date(int new_year, int new_month, int new_day)
        : year(new_year), month(new_month), day(new_day) {
}

int Date::GetYear() const {
  return year;
}

int Date::GetMonth() const {
  return month;
}

int Date::GetDay() const {
  return day;
}

bool Date::operator<(const Date &rhs) const {
//  return ToString() < rhs.ToString();
  return MakeDateTuple() < rhs.MakeDateTuple();
}

bool Date::operator<=(const Date &rhs) const {
//  return ToString() <= rhs.ToString();
  return MakeDateTuple() <= rhs.MakeDateTuple();
}

bool Date::operator>(const Date &rhs) const {
//  return ToString() > rhs.ToString();
  return MakeDateTuple() > rhs.MakeDateTuple();
}

bool Date::operator>=(const Date &rhs) const {
//  return ToString() >= rhs.ToString();
  return MakeDateTuple() >= rhs.MakeDateTuple();
}

bool Date::operator==(const Date &rhs) const {
//  return ToString() == rhs.ToString();
  return MakeDateTuple() == rhs.MakeDateTuple();
}

bool Date::operator!=(const Date &rhs) const {
//  return ToString() != rhs.ToString();
  return MakeDateTuple() != rhs.MakeDateTuple();
}

string Date::ToString() const {
  ostringstream stream;
  stream << setw(4) << setfill('0') << to_string(year);
  stream << '-';
  stream << setw(2) << setfill('0') << to_string(month);
  stream << '-';
  stream << setw(2) << setfill('0') << to_string(day);
  return stream.str();
}

tuple<int, int, int> Date::MakeDateTuple() const {
  return tuple(year, month, day);
}

istream &operator>>(istream &is, Date &d) {
    int new_year, new_month, new_day;
    char sep;
    bool is_valid_date = true;
    string date_str;
    is >> date_str;

    istringstream stream(date_str);
    stream >> new_year;
    stream >> sep;
    is_valid_date &= sep == kDateSeparator;
    stream >> new_month;
    stream >> sep;
    is_valid_date &= sep == kDateSeparator;
    stream >> new_day;
    if (!stream || stream >> sep || !is_valid_date) {
      throw std::runtime_error(kDateInvalidString + date_str);
    }
    d = Date(new_year, new_month, new_day);
    return is;
}

ostream &operator<<(ostream &stream, const Date &date) {
  stream << date.ToString();
  return stream;
}

Date ParseDate(istream &is) {
  Date date;
  is >> date;
  return date;
}
