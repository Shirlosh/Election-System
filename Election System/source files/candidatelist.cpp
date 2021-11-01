#include "candidatelist.h"
#include <iostream>
#include "partylist.h"

using namespace std;


Candidate* CandidateMap::isExist(int id)
{
	iterator itr = find(id);

	if (itr == end())
		return nullptr;

	return (*itr).second;
}

CandidateMap::iterator CandidateMap::getindex(int idx)
{
	iterator itr = begin();
	for (int i = 0; i < idx; i++)
	{
		itr++;
		if (itr == end())
			return end();
	}

	return itr;
}

void CandidateMap::updateCandidates(CitizenMap* clist, PartyList* Plist)
{
	int i = 0;
	
	PartyList::const_iterator itr = Plist->begin();
	
	for (; itr != Plist->end() ; itr++)
	{
		CandidateMap *c = (*itr)->getCandidateList();
		c->setProvinces(clist);
	}

}

void CandidateMap::setProvinces(CitizenMap* clist)
{
	iterator itr = begin();

	for (; itr != end(); itr++)
	{
		Citizen *c = clist->isExist((*itr).first);
		(*itr).second->setProvince(c->getProvince());
	}
}


ostream& operator<<(ostream& os, const CandidateMap& c) 
{
	CandidateMap::const_iterator itr =c.begin();

	for (; itr != c.end(); itr++)
		os << *(*itr).second << endl;

	return os;
}

void CandidateMap::save(ofstream& out) const
{
	const_iterator itr = begin();
	int _size = size();

	out.write(rcastcc(&_size), sizeof(_size));

	for (; itr != end(); itr++)
		(*itr).second->save(out);
}

void CandidateMap::saveIDs(ofstream& out) const
{
	const_iterator itr = begin();
	int _size = size();

	out.write(rcastcc(&_size), sizeof(_size));

	for (; itr != end(); itr++)
	{
		int id = (*itr).second->getID();
		out.write(rcastcc(&id), sizeof(id));
	}
}

void CandidateMap::load(ifstream& in, CitizenMap *list)
{
	int size;
	int id;
	in.read(rcastc(&size), sizeof(size));

	for (int i = 0; i < size; i++)
	{
		in.read(rcastc(&id), sizeof(id));
		Citizen* c = list->isExist(id);
		
		Candidate *newC = new Candidate(in,*c);
		insert(pair<int, Candidate*>(c->getID(), newC));
	}
	
}

void CandidateMap::loadExist(ifstream& in, CandidateMap* clist)
{
	int id;
	int size;
	in.read(rcastc(&size), sizeof(size));

	for (int i = 0; i < size; i++)
	{
		in.read(rcastc(&id), sizeof(id));
		Candidate* c = clist->isExist(id);
		insert(pair<int, Candidate*>(c->getID(), c));
	}
}
