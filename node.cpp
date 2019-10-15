#include "node.h"


DateComparisonNode::DateComparisonNode(Comparison comparison, const Date& value) {
	comparison_ = comparison;
	value_ = value;
}

bool DateComparisonNode::Evaluate(const Date & date, const string & event) const
{	
	vector<int> d = { date.GetYear() ,date.GetMonth(),date.GetDay() };
	vector<int> v = { value_.GetYear() ,value_.GetMonth(),value_.GetDay() };
	switch (comparison_) {
	case (Comparison::Less):
		return d < v;
	case (Comparison::LessOrEqual):
		return d <= v;
	case (Comparison::Greater):
		return d > v;
	case (Comparison::GreaterOrEqual):
		return d >= v;
	case (Comparison::Equal):
		return d == v;
	case (Comparison::NotEqual):
		return d != v;
	}
	
	return true;
}

EventComparisonNode::EventComparisonNode(Comparison comparison, const string& value) {
	comparison_ = comparison;
	value_ = value;
}

bool EventComparisonNode::Evaluate(const Date & date, const string & event) const
{	
	switch (comparison_) {
	case (Comparison::Less):
		return event < value_;
	case (Comparison::LessOrEqual):
		return event <= value_;
	case (Comparison::Greater):
		return event > value_;
	case (Comparison::GreaterOrEqual):
		return event >= value_;
	case (Comparison::Equal):
		return event == value_;
	case (Comparison::NotEqual):
		return event != value_;
	}
	return true;
}



LogicalOperationNode::LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) :
	operation_(op), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date & date, const string & event) const
{
	
	switch (operation_) {
	case (LogicalOperation::Or):
		return (*left_).Evaluate(date, event) || (*right_).Evaluate(date, event);
	case (LogicalOperation::And):
		return (*left_).Evaluate(date, event) && (*right_).Evaluate(date, event);
	}
	
	return true;
}

bool EmptyNode::Evaluate(const Date & date, const string & event) const
{
	return true;
}
