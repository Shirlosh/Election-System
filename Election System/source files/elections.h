#pragma once
#include "date.h"
#include "citizenmap.h"
#include "partylist.h"
#include "provincelist.h"
#include "dividedProvince.h"
#include "uniformProvince.h"


enum PROVINCE { UNIFORM_PROVINCE = 1, DIVIDED_PROVINCE };

class Elections
{
protected:
	Date Electionsdate;
	CitizenMap voterRegister;
	PartyList PartiesList;
	ProvinceList ProvincesList;

public:
	
	Elections(int d, int m, int y);
	Elections(ifstream& in);
	virtual ~Elections();

	/*SHOWS*/
	void showDate() const;
	void showCitizenList() const;
	void showPartyList() const;
	virtual void showProvinceList() const;
	void showResult() const;

	/*ADDERS*/
	Citizen* addCitizen(string cname, int id, int birthyear,int provSerial);
	void addCandidate(int id,int partySerial,int provinceSerial); 
	void addParty(string pName,int cID);
	virtual void addProvince(string provinceName, int candidateNum, int provinceType);
	void addVote(int ID, int PartySerial); 

	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	// date,votersRegister,PartiesList,ProvinceList
	void save(ofstream& out) const;
	void saveType(ofstream& out) const;
};

