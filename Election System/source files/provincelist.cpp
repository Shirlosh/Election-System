#include "provincelist.h"

using namespace std;

// get a serial and search for the requested node
// return the province with this serial
Province *ProvinceList::getNode(int serial) const
{
	if (empty())
		return nullptr;

	const_iterator itr = begin();

	for (; itr != end(); itr++)
	{
		if ((*itr)->getSerialNum() == serial)
			return *itr;
	}

	return nullptr;
}

// insert the new party to each of the province
// intialize it votes to 0
void ProvinceList::addParty(Party* p) 
{
	const_iterator itr = begin();

	for (; itr != end(); itr++)
		(*itr)->getResult().AddTail(p);	
}

void ProvinceList::resetAllCandidateLists()
{
	const_iterator itr = begin();

	for (; itr != end(); itr++)
	{
		(*itr)->getResult().resetCandidatesLists();
		(*itr)->resetCandidateList();
	} 
}

// assign candidate from the party to the province
// if there is not enought candidates at the party to assign it returns false
void ProvinceList::candidatesAssignation(PartyList *p)
{
	resetAllCandidateLists();
	p->resetIdx();

	const_iterator itr = begin();
	for (; itr != end(); itr++)
		(*itr)->getResult().updateList((*itr)->getChoosenCandidates());// update the candidate list of the province
	
}

// get partylist reset its electors and update its electors.
void ProvinceList::setElectors(PartyList* partylist)
{
	partylist->resetElectors();
	
	const_iterator itr = begin();

	for (; itr != end(); itr++)
		(*itr)->electorsDistribution(); // goes to the province type and distribuite the electors as requested.
	
}

ostream& operator<<(ostream& os, const ProvinceList& p) {
	
	ProvinceList::const_iterator itr = p.begin();

	for (; itr != p.end(); itr++)
		os << *(*itr) << endl;
	
	return os;
}


void ProvinceList::load(ifstream& in,CitizenMap *list, PartyList* plist)
{
	int size;
	char type[TYPE_LEN+1];

	in.read(rcastc(&size), sizeof(size));
	for (int i = 0; i < size; i++)
	{
		Province* p = nullptr;

		in.read(rcastc(&type), TYPE_LEN);
		type[TYPE_LEN] = '\0';

		if (strncmp(typeid(dividedProvince).name() + 6, type, TYPE_LEN) == 0)
			p = new dividedProvince(in, list,plist);

		if (strncmp(typeid(uniformProvince).name() + 6, type, TYPE_LEN) == 0)
			p = new uniformProvince(in,list,plist);

		this->push_back(p);
	}
}