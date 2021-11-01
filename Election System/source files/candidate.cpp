#include "candidate.h"
#include <iostream>

using namespace std;


Candidate::Candidate(Citizen &c, int PartySerial, int ProvinceSerial) : Citizen(c)
{
	partySerialNumber = PartySerial;
	ProvinceSerialNumber = ProvinceSerial;
}

Candidate::Candidate(ifstream& in, Citizen& c) : Citizen(c)
{
	load(in);
}

Candidate::Candidate(Citizen const &other) : Citizen(other){
	*this = other;
}

Candidate::Candidate(Candidate const &other) : Citizen(other)
{
	*this = other;
}

bool Candidate::setPartySerial(int serial) {
	partySerialNumber = serial;
	return true;
}
bool Candidate::setProvinceSerial(int serial) {
	ProvinceSerialNumber = serial;
	return true;
}

const Candidate& Candidate::operator=(const Candidate& other) 
{
	Citizen::operator=(other);
	setPartySerial(other.partySerialNumber);

	return *this;

}

const Candidate& Candidate::operator=(const Citizen& other) 
{
	Citizen::operator=(other);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Candidate& c) 
{
	os << (Citizen)c;
	os << "Party Serial Number: " << c.getPartySerial() << endl;
	os << "Represents Province Serial Number "<< c.getProvinceSerial() << endl; 

	return os;

}


void Candidate::save(ofstream& out) const 
{
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&partySerialNumber),sizeof(partySerialNumber));
	out.write(rcastcc(&ProvinceSerialNumber),sizeof(ProvinceSerialNumber));
}

void Candidate::load(ifstream& in)
{
	in.read(rcastc(&partySerialNumber), sizeof(partySerialNumber));
	in.read(rcastc(&ProvinceSerialNumber), sizeof(ProvinceSerialNumber));
}