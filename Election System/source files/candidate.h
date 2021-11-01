#pragma once
#include "citizenmap.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class Candidate : public Citizen
{
private:
	int partySerialNumber;
	int ProvinceSerialNumber;

public:
	Candidate(Citizen &c,int PartySerial, int ProvinceSerial);
	Candidate(ifstream& in, Citizen& c);
	Candidate(const Citizen &other);
	Candidate(const Candidate &other);

	/*SETTERS*/
	bool setPartySerial(int serial);
	bool setProvinceSerial(int serial);

	/*GETTERS*/
	int getPartySerial() const		 { return partySerialNumber; }
	int getProvinceSerial() const	 { return ProvinceSerialNumber; }


	const Candidate& operator=(const Candidate& other);
	const Candidate& operator=(const Citizen& other);
	friend std::ostream& operator<<(std::ostream& os, const Candidate& c);


	/*FILES OPERATIONS*/

	// saving to a file in the following order:
	// citizen details,party serial,province serial
	void save(ofstream& out) const;
	void load(ifstream& in);

};
