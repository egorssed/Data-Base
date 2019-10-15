#pragma once

#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>
using namespace std;

class Date {
public:
	Date();
	Date(const int& y, const int& m, const int& d);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;
};

ostream& operator<<(ostream& stream, const Date& date);

Date ParseDate(istream& is);

bool operator==(const Date& lhs, const Date& rhs);

bool operator<(const Date& lhs, const Date& rhs);