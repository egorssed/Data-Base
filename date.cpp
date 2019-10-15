#include "date.h"


Date::Date() {
	year = 0;
	month = 0;
	day = 0;
}
Date::Date(const int& y, const int& m, const int& d) {

	if (m > 12 || m < 1) {
		throw invalid_argument("Month value is invalid: " + to_string(m));
	}
	if (d > 31 || d < 1) {
		throw invalid_argument("Day value is invalid: " + to_string(d));
	}
	year = y;
	month = m;
	day = d;
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


ostream& operator<<(ostream& stream, const Date& date) {
	if (date.GetYear() >= 0) {
		stream << setw(4) << setfill('0') << date.GetYear()
			<< '-' << setw(2) << setfill('0') << date.GetMonth()
			<< '-' << setw(2) << setfill('0') << date.GetDay();
	}
	else {
		stream << "-" << setw(4) << setfill('0') << -date.GetYear()
			<< '-' << setw(2) << setfill('0') << date.GetMonth()
			<< '-' << setw(2) << setfill('0') << date.GetDay();
	}

	return stream;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return (lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() == rhs.GetMonth()) && (lhs.GetDay() == rhs.GetDay());
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) return lhs.GetYear() < rhs.GetYear();
	else if (lhs.GetMonth() != rhs.GetMonth()) return lhs.GetMonth() < rhs.GetMonth();
	else return lhs.GetDay() < rhs.GetDay();
}

Date ParseDate(istream& is) {
	string date;
	is >> date;
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

Date ParseDate(istringstream& is) {
	string date;
	is >> date;
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