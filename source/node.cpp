#include "node.h"

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
  return true;
}

ComparisonNode::ComparisonNode(const Comparison &new_cmp)
        : cmp(new_cmp) {
}

DateComparisonNode::DateComparisonNode(const Comparison &new_cmp, const Date &new_date)
        : ComparisonNode(new_cmp), date(new_date) {
}

bool DateComparisonNode::Evaluate(const Date &d, const string &e) const {
  return Compare(d, date, cmp);
}

EventComparisonNode::EventComparisonNode(const Comparison &new_cmp, const string &new_event)
        : ComparisonNode(new_cmp), event(new_event) {
}

bool EventComparisonNode::Evaluate(const Date &d, const string &e) const {
  return Compare(e, event, cmp);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &new_operation, const shared_ptr<Node> &new_lhs,
                                           const shared_ptr<Node> &new_rhs)
        : operation(new_operation), lhs(new_lhs), rhs(new_rhs) {
}

bool LogicalOperationNode::Evaluate(const Date &d, const string &e) const {
  const bool l_evaluation = lhs->Evaluate(d, e);
  const bool r_evaluation = rhs->Evaluate(d, e);
  switch (operation) {
    case LogicalOperation::Or:
      return l_evaluation || r_evaluation;
    case LogicalOperation::And:
      return l_evaluation && r_evaluation;
    default:
      throw std::invalid_argument("No such operation available");
  }
}
