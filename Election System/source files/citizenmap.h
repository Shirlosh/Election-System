#pragma once
#include "citizen.h"
#include <iostream>
#include <fstream>
#include <map>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

class CitizenMap : public map<int, Citizen*>
{
public:
	CitizenMap(){}
	CitizenMap(ifstream& in);
	Citizen* isExist(int id);

	Citizen* addTail(string cname,int id,int birthyear,Province* p,int Eyear);
	friend ostream& operator<<(ostream& os, const CitizenMap& c);

	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	// list len, citizen details
	bool save(ofstream& out) const;
	bool saveIDs(ofstream& out) const; // saves citizens ids only use if citizen is already exist
	void load(ifstream& in);
	void loadExist(ifstream& in, CitizenMap* clist, Province* p); // create a list of exist citizen by loading citizens ids
};

