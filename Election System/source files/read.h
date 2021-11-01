#pragma once
#include "elections.h"
#include "simpleElections.h"
#include <iostream>


class Read
{
public:
	static void readProvince(Elections& e);
	static void readCitizen(Elections& e);
	static void readCandidate(Elections& e);
	static void readParty(Elections& e);
	static void addVote(Elections& e);

	static void saveElections(Elections *e);

	static Elections* createNewElections();
	static Elections* loadExistElections();

};


