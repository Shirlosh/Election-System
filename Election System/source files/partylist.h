#pragma once
#include "party.h"
#include <iostream>
#include <fstream>
#include "citizenmap.h"
#include <list>

class PartyList : public list<Party*>
{
public:
	
	/*GETTERS*/
	Party* getParty(int partySerial) const;
	
	/*Resets*/
	void resetElectors();
	void resetIdx();

	void ArrangeParties();
	friend std::ostream& operator<<(std::ostream& os, const PartyList& p);

	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	// list len, party details
	void save(ofstream& out) const;
	void load(ifstream& in, CitizenMap *list);


private:
	void maxToHead(iterator head); // get part of list and send the max to the head

};

