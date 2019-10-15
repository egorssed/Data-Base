#include "database.h"


void Database::Add(const Date& date, const string& event) {
	if (pairs.count({date,event}) == 0) {
		pairs.insert({ date,event });
		base[date].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for (const auto& list : base) {
		for (const auto& event : list.second) {
			if (list.first.GetYear() >= 0) {
				os << list.first << " " << event << endl;
			}
		}
	}
}

string Database::Last(const Date& date) const{
	auto it = base.upper_bound(date);
	if (it == base.begin()) {
		return "No entries";
	}
	stringstream s;
	s << prev(it)->first;
	s << " ";
	s << prev(it)->second.back();
	return s.str();
}

ostream& operator<<(ostream& stream, const pair<Date, string>& FindResult) {
	stream << FindResult.first << " " << FindResult.second;
	return stream;
}

bool operator<(const pair<Date, string>& lhs, const pair<Date, string>& rhs) {
	if (!(lhs.first == rhs.first)) return lhs.first < rhs.first;
	else return lhs.second < rhs.second;
}

bool operator==(const pair<Date, string>& lhs, const pair<Date, string>& rhs) {
	return lhs.first == rhs.first&&lhs.second == rhs.second;
}