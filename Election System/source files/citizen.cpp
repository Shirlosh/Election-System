#pragma warning (disable: 4996)
#include <iostream>
#include "citizen.h"
#include "province.h"


Citizen::Citizen(string _name,int id, int birthYear ,Province *p, int electionYear)
{
	setName(_name);
	setID(id);
	setBirthYear(birthYear, electionYear);
	setProvince(p);
	isVoted = false;
}

Citizen::Citizen(ifstream& in)
{
	load(in);
	province = nullptr; // province variable will be utilized by provinceslist 

}

Citizen::~Citizen() {}

Citizen::Citizen(Citizen const &other) { *this = other; }

void Citizen::setName(string _name) 
{
	if (name.empty())
		name.clear();
	
	name = _name;
}

void Citizen::setID(int id) 
{
	int digChecker = id, counter = 0;


	while (digChecker)
	{
		digChecker /= 10;
		counter++;
	}

	if (counter !=9)
		throw invalid_argument("citizen id must contain 9 digits");

	this->id = id;
}
void Citizen::setBirthYear(int BirthYear,int electionYear)
{
	if (electionYear - BirthYear < 18)
		throw invalid_argument("citizen must be at least 18 years old");
	
	birthYear = BirthYear;
}


void Citizen::setVote()
{
	isVoted = true;
}

void Citizen::setProvince(Province* p)
{
	if (p == nullptr)
		throw invalid_argument("incorrect province serial");

	province = p;
}

int Citizen::getProvinceSerialNum() const 
{
	return province->getSerialNum();
}

Province* Citizen::getProvince() const 
{
	return province;
}
string Citizen::getProvinceName() const
{
	return province->getName();
}


const Citizen& Citizen::operator=(const Citizen& other)
{
	setName(other.name);
	setID(other.id);
	province = other.province;
	birthYear = other.birthYear;

	return *this;
}

ostream& operator<<(ostream& os, const Citizen& c) {

	os << "Name: " << c.name << endl;
	os << "ID: " << c.id << endl;
	os << "Birthyear: " << c.birthYear << endl;
	os << "Province: " << c.province->getName() << endl;

	return os;
}

void Citizen::save(ofstream& out) const
{
	//save name:
	int nameLen = name.length();
	out.write(rcastcc(&nameLen), sizeof(nameLen));
	out.write(rcastcc(&name[0]), nameLen);
	
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&birthYear), sizeof(birthYear));
	out.write(rcastcc(&isVoted), sizeof(isVoted));

}

void Citizen::load(ifstream& in)
{
	int nameLen;
	//load name:
	in.read(rcastc(&nameLen), sizeof(nameLen));
	name.resize(nameLen);
	in.read(rcastc(&name[0]), nameLen);
	
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&birthYear), sizeof(birthYear));
	in.read(rcastc(&isVoted), sizeof(isVoted));
}

