#pragma once
#include "candidate.h"
#include "candidatelist.h"
#include <ostream>
#include <fstream>
#include "citizenmap.h"

using namespace std;

class Party 
{
private:
	string partyName;
	Citizen President;
	int PartySerial;
	CandidateMap candidatesList;
	int electors;
	int votes;
	int numOfcandidates;	 // how many candidates the party provides

public:
	
	Party(string name, Citizen &president);
	Party(ifstream &in, Citizen& president,CitizenMap *list);
	~Party();
	Party(Party const &other);

	/*SETTERS*/
	void setName(string n);
	void setCandidatesList(CandidateMap &lst);
	void setSerial(int serial);
	void setNumOfCandidates(int num);

	/*GETTERS*/
	string getName()const							 { return partyName; }
	CandidateMap const& getCandidateList() const	 { return candidatesList; }
	CandidateMap*		 getCandidateList()			 { return &candidatesList; }
	string getPcandidate() const					 { return President.getName(); }
	int getSerial() const							 { return PartySerial; }
	int getElectors() const							 { return electors; }
	int getVotes() const							 { return votes; }
	int getNumOfCandidates() const					 { return numOfcandidates; }
	int candidateIdx;

	void addVote()				{ votes++; }		 // update vote data
	void addElectors(int add)   { electors += add; } // update elector data
	void resetElectors()		{ electors = 0; }	 // reset electors data
	void addToList(Candidate &node);				 // add a candidate to candidate list

	const Party& operator=(const Party& other);
	friend ostream& operator<<(ostream& os, const Party& p);

	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	//  president id, namelen, party name, party serial,electors, votes , candidate list
	bool save(ofstream& out) const;
	void load(ifstream& in,CitizenMap *list);

};


