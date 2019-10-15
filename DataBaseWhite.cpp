#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <exception>
#include <sstream>
#include <iomanip>
using namespace std;


class Date {
public:
	Date() {
		year = 0;
		month = 0;
		day = 0;
	}
	Date(const int& y, const int& m, const int& d) {

		if (m>12 || m <1) {
			throw invalid_argument("Month value is invalid: " + to_string(m));
		}
		if (d>31 || d <1) {
			throw invalid_argument("Day value is invalid: " + to_string(d));
		}
		year = y;
		month = m;
		day = d;
	}
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay()<rhs.GetDay();
		}
		else return lhs.GetMonth()<rhs.GetMonth();
	}
	else return lhs.GetYear()<rhs.GetYear();
}

ostream& operator<<(ostream& stream, const Date& date) {
	if (date.GetYear() >= 0) {
		cout << setw(4) << setfill('0') << date.GetYear()
			<< '-' << setw(2) << setfill('0') << date.GetMonth()
			<< '-' << setw(2) << setfill('0') << date.GetDay();
	}
	else {
		cout << "-" << setw(4) << setfill('0') << -date.GetYear()
			<< '-' << setw(2) << setfill('0') << date.GetMonth()
			<< '-' << setw(2) << setfill('0') << date.GetDay();
	}

	return stream;
}


Date ParseDate(const string& date) {
	istringstream ObtDate(date);
	bool correct = true;

	int year;
	correct = ObtDate >> year && ObtDate.peek() == '-' && correct;
	ObtDate.ignore(1);

	int month;
	correct = ObtDate >> month && ObtDate.peek() == '-' && correct;
	ObtDate.ignore(1);

	int day;
	correct = ObtDate >> day && ObtDate.eof() && correct;

	if (!correct) {
		throw invalid_argument("Wrong date format: " + date);
	}
	return Date(year, month, day);
}




class DataBase {
public:
	void AddEvent(const Date& date, const string& event) {
		base[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		if (base.count(date) > 0) {
			if (base[date].count(event) > 0) {
				base[date].erase(event);
				return true;
			}
		}
		return false;
	}
	int  DeleteDate(const Date& date) {
		if (base.count(date) > 0) {
			int N = base[date].size();
			base.erase(date);
			return N;
		}
		return 0;
	}
	void Find(const Date& date) const {
		if (base.count(date) > 0) {
			set<string> value;
			value = base.at(date);
			for (const auto& i : value) {
				cout << i << endl;
			}
		}
		else  throw invalid_argument("");
	}

	void Print() const {
		for (const auto& list : base) {
			for (const auto& event : list.second) {
				if (list.first.GetYear() >= 0) {
					cout << list.first << " " << event << endl;
				}
			}
		}
	}


private:
	map <Date, set<string>> base;
};



int main() {
	DataBase db;
	string s;
	while (getline(cin, s)) {
		stringstream ObtCommand(s);
		string command;
		string StrDate;
		string event;
		try {
			ObtCommand >> command;
			if (command == "Add") {
				Date date;
				ObtCommand >> StrDate;
				date = ParseDate(StrDate);
				ObtCommand >> event;
				db.AddEvent(date, event);
				continue;
			}
			if (command == "Del") {
				Date date;
				ObtCommand >> StrDate;
				date = ParseDate(StrDate);
				ObtCommand >> event;
				if (event.size() == 0) {
					int N = db.DeleteDate(date);
					cout << "Deleted " << N << " events" << endl;
				}
				else {
					if (db.DeleteEvent(date, event)) {
						cout << "Deleted successfully" << endl;
					}
					else {
						cout << "Event not found" << endl;
					}
				}
				continue;
			}
			if (command == "Find") {
				Date date;
				ObtCommand >> StrDate;
				date = ParseDate(StrDate);
				db.Find(date);
				continue;
			}
			if (command == "Print") {
				db.Print();
				continue;
			}
			if (command.size() == 0) {
				continue;
			}
			cout << "Unknown command: " << command << endl;
			break;
		}
		catch (invalid_argument& e) {
			cout << e.what() << endl;
			break;
		}
	}
	return 0;
}
