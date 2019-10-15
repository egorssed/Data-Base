#pragma once
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include "date.h"



class Database {
public:
	void Add(const Date& date, const string& event);
	
	string Last(const Date& date) const;
		
	template <class Func> int RemoveIf(Func predicate) {
		int count = 0;
		for (auto it = base.begin(); it != base.end();) {
			Date d = it->first;
			for (auto vit = it->second.begin(); vit != it->second.end();) {
				if (predicate(d, *vit)) {
					pairs.erase(make_pair(d, *vit));
					vit = (it->second).erase(vit);
					++count;
				}
				else ++vit;
			}
			if (it->second.empty()) {
				it = base.erase(it++);
				continue;
			} ++it;
		}
		return count;
	}

	template<typename Func>
	vector<pair<Date, string>> FindIf(Func predicate) const {
		vector<pair<Date, string>> result;
		for (const auto& note : base) {
			for (const auto& value : note.second)
				if (predicate(note.first, value)) {
					result.push_back(make_pair(note.first, value));
				}
		}
		return result;
	}
	void Print(ostream& os) const;

private:
	set<pair<Date,string>> pairs;
	map <Date, vector<string>> base;
};

ostream& operator<<(ostream& stream, const pair<Date, string>& FindResult);

bool operator<(const pair<Date, string>& lhs, const pair<Date, string>& rhs);

bool operator==(const pair<Date, string>& lhs, const pair<Date, string>& rhs);