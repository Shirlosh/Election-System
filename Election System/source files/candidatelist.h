#pragma once
#include "candidate.h"
#include <iostream>

class PartyList;

class CandidateMap : public map<int,Candidate*>
{
public:

	Candidate* isExist(int id);
	iterator getindex(int idx);
	//runs over the parties and update provinces
	static void updateCandidates(CitizenMap* clist,PartyList* Plist);
	void setProvinces(CitizenMap* clist);

	friend std::ostream& operator<<(std::ostream& os, const CandidateMap& c);


	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	// list len, candidate details
	void save(ofstream& out) const;
	void saveIDs(ofstream& out) const;
	void load(ifstream& in, CitizenMap* list);
	void loadExist(ifstream& in, CandidateMap* clist); // create a list of exist citizen by loading citizens ids

};

