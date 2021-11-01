#include "date.h"
using namespace std;

Date::Date(int d, int m, int y) 
{
	setMonth(m);
	setDay(d);
	setYear(y);
}

Date::Date(ifstream& in)
{
	in.read(rcastc(&day), sizeof(day));
	in.read(rcastc(&month), sizeof(month));
	in.read(rcastc(&year), sizeof(year));
}

Date::Date(const Date &other) { *this = other; }

void Date::setDay(int d) {

	if (d < 1 || d>31)
		throw invalid_argument("day must be in the range of 1-31");
	
	if (month == 2 && d > 28)
		throw invalid_argument("there is only 28 days in February");

	day = d;
}

void Date::setMonth(int m) {

	if (m < 1 || m>12)
		throw invalid_argument("invalid month value");

	month = m;
}
void Date::setYear(int y) {
	
	if (y < 0)
		throw invalid_argument("year must be a positive number");
	year = y;
}

int Date::getDay() const {
	return day;
}
int Date::getMonth() const {
	return month;
}
int Date::getYear() const {
	return year;
}

const Date& Date:: operator=(const Date& other) {
	day = other.day;
	month = other.month;
	year = other.year;

	return *this;
}

ostream& operator<<(ostream& os, const Date& d)
{
	os << d.getDay() << '/' << d.getMonth() << '/' << d.getYear();
	return os;

}

bool Date::save(ofstream& out) const
{
	out.write(rcastcc(&day), sizeof(day));
	out.write(rcastcc(&month), sizeof(month));
	out.write(rcastcc(&year), sizeof(year));
	
	if (!out.good())
		throw runtime_error("The attempt to save the file has failed");
}