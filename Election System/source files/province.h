#pragma once
#include "party.h"
#include "citizenmap.h"
#include "voteslist.h"
#include <iostream>
#include <fstream>
#include <string>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
static const int TYPE_LEN = 3;

using namespace std;

class Province
{
protected:
	string ProvinceName;
	int serialNum;
	CitizenMap allowVote;
	double Percentage;
	int numOfCandidates; // how many candidate the province has 
	CandidateMap choosenCandidates;
	VotesList result;

public:
	Province(string province, int numOfCandidates);
	Province(ifstream &in,CitizenMap* list,PartyList* plist);

	Province(const Province &other);
	virtual ~Province();

	/*GETTERS:*/
	const string getName()	const						 { return ProvinceName; }
	int getSerialNum()  const							 { return serialNum; }
	CitizenMap getAllowVote() const						 { return allowVote; }
	double getPercentage() const						 { return Percentage; }
	int getNumOfCandidates() const						 { return numOfCandidates; }
	const CandidateMap getChoosenCandidates() const		 { return choosenCandidates; }
	CandidateMap &getChoosenCandidates()				 { return choosenCandidates; }
	VotesList& getResult()								 { return result; }
	int getTotalVotes() const							 { return result.getSum(); }

	/*SETTERS*/
	void setName(string name);
	void setSerialNum(int serial);
	void setAllowVote(Citizen *node);
	void setPercentage();
	void setNumOfCandidates(int numOfCandidates);
	void setChoosenCandidates(CandidateMap &cList);
	void setResult(int partySerial);

	void resetCandidateList()							{ choosenCandidates.clear(); }

	const Province& operator=(const Province& other);
	friend std::ostream& operator<<(std::ostream& os, const Province& p);
	virtual void toOs(ostream& os) const = 0;

	virtual void electorsDistribution() = 0;

	/*FILES OPERATIONS*/
	//save to file with the following order:
	//province name,serial number,precentage, numofcandidates , choosen candidate ID, citizen ID list, result
	//the united func will save all these ids in an array the choosen will be the first to load (-1 if isnt exist)//
	bool save(ofstream& out) const;
	bool saveType(ofstream& out) const;
	void load(ifstream& in, CitizenMap* list);

protected:
	double calculatePercentage();

};



