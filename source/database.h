#pragma once

#ifndef SOURCE_DATABASE_H
#define SOURCE_DATABASE_H

#include <map>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

#include "date.h"

using std::string;
using std::map;
using std::set;
using std::pair;
using std::vector;

//const string kCommandInvalidString = "Unknown command: ";
//const string kEventNotFound = "Event not found";
//const string kEventRemoveSuccess = "Deleted successfully";
//const string kEventsRemovedZero = "Deleted 0 events";

class Database {
public:
  void Add(const Date &date, const string &event);

  void Print(ostream &stream) const;

  vector<pair<Date, string>> FindIf(const std::function<bool(Date, string)> &predicate) const;

  int RemoveIf(const std::function<bool(Date, string)> &predicate);

  string Last(const Date &date) const;

private:
  map<Date, set<string>> unique_events;
  map<Date, vector<string>> events;
};

ostream &operator<<(ostream &stream, const pair<Date, string> &event);

#endif //SOURCE_DATABASE_H
