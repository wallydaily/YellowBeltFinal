#include "database.h"

void Database::Add(const Date &date, const string &event) {
  if (unique_events.count(date) == 0 || unique_events[date].count(event) == 0) {
    unique_events[date].insert(event);
    events[date].emplace_back(event);
  }
}

void Database::Print(ostream &stream) const {
  for (const auto &[date, d_events] : events) {
    for (const auto &event : d_events) {
      stream << date << ' ' << event << '\n';
    }
  }
}

vector<pair<Date, string>> Database::FindIf(const std::function<bool(Date, string)> &predicate) const {
  vector<pair<Date, string>> output;
  for (const auto &[date, d_events] : events) {
    for (const auto &event : d_events) {
      if (predicate(date, event)) {
        output.emplace_back(date, event);
      }
    }
  }
  return output;
}

int Database::RemoveIf(const std::function<bool(Date, string)> &predicate) {
  int count = 0;
  auto it_events = events.begin();
  while (it_events != events.end()) {
    auto it_remove = stable_partition(it_events->second.begin(), it_events->second.end(), [&](const string &event) {
      return !predicate(it_events->first, event);
    });
    if (it_remove != it_events->second.end()) {
      count += distance(it_remove, it_events->second.end());
      it_events->second.erase(it_remove, it_events->second.end());
      unique_events[it_events->first].clear();
    }
    if (it_events->second.empty()) {
      unique_events.erase(it_events->first);
      it_events = events.erase(it_events);
    } else {
      unique_events[it_events->first].insert(it_events->second.begin(), it_events->second.end());
      ++it_events;
    }
  }
  return count;
}

string Database::Last(const Date &date) const {
  if (date < begin(unique_events)->first || events.empty()) {
    throw std::invalid_argument("");
  }
  auto it_date = unique_events.upper_bound(date);
  --it_date;
  ostringstream oss;
  oss << it_date->first << ' ' << events.at(it_date->first).back();
  return oss.str();
}

ostream &operator<<(ostream &stream, const pair<Date, string> &event) {
  return stream << event.first << ' ' << event.second;
}
