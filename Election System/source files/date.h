#pragma once
#include <iostream>
#include <fstream>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;

public:

	Date(int d, int m, int y);
	Date(ifstream &in);
	Date(const Date &other);
	
	/*GETTERS*/
	int getDay()	const;
	int getMonth()  const;
	int getYear()	const;
	
	/*SETTERS*/
	void setDay(int d);
	void setMonth(int m);
	void setYear(int y);

	const Date& operator=(const Date& other);
	friend std::ostream& operator<<(std::ostream& os, const Date& d);

	/*FILES OPERATIONS*/
	//saving in 3 intigers day,month,year
	bool save(ofstream& out) const;

};