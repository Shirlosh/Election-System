#pragma warning (disable: 4996)
#include "party.h"
#include <iostream>


Party::Party(string name, Citizen &president) : President(president)
{
	setName(name);
	electors = 0;
}

Party::Party(ifstream &in,Citizen& president,CitizenMap* list) : President(president)
{
	load(in,list);
}

Party::~Party() { }

Party::Party(Party const& other) : President(other.President)
{ *this = other; }

void Party::setName(string n)
{
	if (!partyName.empty())
		partyName.clear();

	partyName = n;

}
void Party::setSerial(int serial) 
{
	PartySerial = serial;
}

void Party::setNumOfCandidates(int num)
{
	numOfcandidates = num;
}


void Party::setCandidatesList(CandidateMap &lst)
{
	candidatesList = lst;
}

const Party& Party::operator=(const Party& other)
{
	setName(other.partyName);
	President = other.President;
	candidatesList = other.candidatesList;
	return *this;
}

void Party::addToList(Candidate &node)
{
	candidatesList.insert(pair<int, Candidate*>(node.getID(),&node));
}

ostream& operator<<(ostream& os, const Party& p)
{
	os << "Party Name: " << p.getName() << endl;
	os << "Party Serial: " << p.getSerial() << endl;
	os << "the choosen candidate name: " << p.getPcandidate() << endl;
	os << "\tCandidate List: " << endl << p.candidatesList << endl;

	return os;
}

bool Party::save(ofstream& out) const
{
	int nameLen = partyName.length();
	//save president:
	int id = President.getID();
	out.write(rcastcc(&id), sizeof(id));
	//save party name:
	out.write(rcastcc(&nameLen), sizeof(nameLen));
	out.write(rcastcc(&partyName[0]), nameLen);

	out.write(rcastcc(&PartySerial), sizeof(PartySerial));
	out.write(rcastcc(&electors), sizeof(electors));
	out.write(rcastcc(&votes), sizeof(votes));
	out.write(rcastcc(&numOfcandidates), sizeof(numOfcandidates));

	candidatesList.save(out);

	return out.good();
}

void Party::load(ifstream& in, CitizenMap* list)
{
	int nameLen;
	
	//load name:
	in.read(rcastc(&nameLen), sizeof(nameLen));
	partyName.resize(nameLen);
	in.read(rcastc(&partyName[0]), nameLen);
	
	in.read(rcastc(&PartySerial), sizeof(PartySerial));
	in.read(rcastc(&electors), sizeof(electors));
	in.read(rcastc(&votes), sizeof(votes));
	in.read(rcastc(&numOfcandidates), sizeof(numOfcandidates));

	candidatesList.load(in,list);
}