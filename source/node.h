#pragma once

#ifndef SOURCE_NODE_H
#define SOURCE_NODE_H

#include <memory>
#include "date.h"

using std::shared_ptr;

enum Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum LogicalOperation {
  Or,
  And
};

class Node {
public:
  virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

class EmptyNode : public Node {
public:
  bool Evaluate(const Date &date, const string &event) const override;
};

class ComparisonNode : public Node {
public:
  ComparisonNode(const Comparison &new_cmp);

protected:
  template<typename T>
  bool Compare(const T &lhs, const T &rhs, const Comparison &cmp) const {
    switch (cmp) {
      case Comparison::Equal:
        return lhs == rhs;
      case Comparison::GreaterOrEqual:
        return lhs >= rhs;
      case Comparison::Greater:
        return lhs > rhs;
      case Comparison::LessOrEqual:
        return lhs <= rhs;
      case Comparison::Less:
        return lhs < rhs;
      case Comparison::NotEqual:
        return lhs != rhs;
      default:
        throw std::invalid_argument("There is no such Comparison");
    }
  }

  const Comparison cmp;
};

class DateComparisonNode : public ComparisonNode {
public:
  DateComparisonNode(const Comparison &new_cmp, const Date &new_date);

  bool Evaluate(const Date &date, const string &event) const override;

private:
  const Date date;
};

class EventComparisonNode : public ComparisonNode {
public:
  EventComparisonNode(const Comparison &new_cmp, const string &new_event);

  bool Evaluate(const Date &date, const string &event) const override;

private:
  const string event;
};

class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(const LogicalOperation &new_operation, const shared_ptr<Node> &lhs, const shared_ptr<Node> &rhs);

  bool Evaluate(const Date &date, const string &event) const override;

private:
  const LogicalOperation operation;
  const shared_ptr<Node> lhs;
  const shared_ptr<Node> rhs;
};

#endif //SOURCE_NODE_H
