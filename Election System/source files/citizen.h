#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Province;

class Citizen
{
protected:
	string name;
	int id;
	int birthYear;
	Province *province;
	bool isVoted;

public:
	
	Citizen(string _name, int id, int birthYear, Province *p, int electionYear);
	Citizen(ifstream& in);
	Citizen(Citizen const &other);
	~Citizen();

	/*SETTERS*/
	void setName(string _name);
	void setID(int id);
	void setBirthYear(int BirthYear, int electionYear);
	void setVote();
	void setProvince(Province* p);

	/*GETTERS*/
	const string getName() const				 { return name; }
	int getID() const					 { return id; }
	int getBirhYear() const				 { return birthYear; }
	bool getVote() const				 { return isVoted; }
	int getProvinceSerialNum() const;
	string getProvinceName() const;
	Province* getProvince() const;

	const Citizen& operator=(const Citizen& other);
	friend std::ostream& operator<<(std::ostream& os, const Citizen& c);


	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	// namelen, name, id, birth year, province serial, is voted
	void save(ofstream& out) const;
	void load(ifstream& in);


};

