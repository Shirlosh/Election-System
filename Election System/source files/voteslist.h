#pragma once
#include <iostream>
#include "partylist.h"
using namespace std;

class VotesNode
{
	Party* party = nullptr;
	int NumOfvote = 0;			 // party votes
	double Percentage = 0;		 // party votes percentage
	int numofcandidates = 0;	 // how many candidates the party provides
	double rest = 0;
	CandidateMap list;
	friend class VotesList;

public:
	Party* getParty() { return party; }
	const Party* getParty()	const { return party; }
	int getPercentage() const { return Percentage; }
	int getNumOfVotes() const { return NumOfvote; }
	const CandidateMap& getCandidateMap() const { return list; }

};


class VotesList : public list<VotesNode>
{
private:
	int numofProvinceCandidates=0;									// how many candidate the province has 
	int sumOfVotes=0;												// total province votes
	Party *winner = nullptr;

public:
	VotesList(){}
	VotesList(int candidatesAmount);
	VotesList(ifstream& in, PartyList* plist) { load(in,plist); }	// implemention missing

	/*GETTERS*/
	Party* getWinner() const			  { return winner; }
	const int getSum() const			  { return sumOfVotes; }	// returns the sum of all votes
	VotesNode* getMaxRest();
	Party* getParty(int idx) const;
	void setWinner();
	

	/*LIST*/
	void AddTail(Party *p,int percentage = 0, int NumofVote = 0, int numofCandidates = 0);
	
	/*VOTE FUNCS*/
	void addVote(int partyserial);								    	// add vote to the votelist
	void resetCandidatesLists();
	void setnumOfCandidates(int numofCandidates);
	void updatePercentage()				noexcept(false);		     //update voteNode percentage
	void updatePartiesCandidates();								    //update voteNode numofCandidates
	void updateList(CandidateMap &clst) noexcept(false); 			//update a specific the candidate for a specific province 

	friend ostream& operator<<(ostream& os, const VotesList& v);


	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	// num of province candidates,sum of votes, winning party serial, size of list,
	// the node: party serial,num of votes, percentage, num of candidates.
	void save(ofstream& out) const;
	void load(ifstream& in,PartyList *list);
	void loadNode(ifstream& in,Party* p);
};

