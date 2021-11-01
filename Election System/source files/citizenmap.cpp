#include "citizenmap.h"

using namespace std;

CitizenMap::CitizenMap(ifstream& in)
{
	load(in);
}

Citizen* CitizenMap::isExist(int id) 
{
	iterator itr = find(id);

	if (itr == end())
		return nullptr;

	return (*itr).second;
}

Citizen* CitizenMap::addTail(string cname, int id, int birthyear, Province* p, int Eyear)
{
	Citizen* c = new Citizen(cname, id, birthyear, p, Eyear);
	insert(pair<int, Citizen*>(c->getID(), c));

	return c;
}

ostream& operator<<(ostream& os, const CitizenMap& c) {

	CitizenMap::const_iterator itr = c.begin();

	for (; itr != c.end(); itr++)
		os << *(*itr).second << endl;

	return os;
}

bool CitizenMap::save(ofstream& out) const
{
	const_iterator itr = begin();
	int _size = size();

	out.write(rcastcc(&_size), sizeof(_size));

	for (; itr != end(); itr++)
		(*itr).second->save(out);
	

	if (!out.good())
		throw runtime_error("The attempt to save the file has failed");
}

bool CitizenMap::saveIDs(ofstream& out) const
{
	const_iterator itr = begin();
	int _size = size();

	out.write(rcastcc(&_size), sizeof(_size));

	for (; itr != end(); itr++)
	{
		int id = (*itr).second->getID();
		out.write(rcastcc(&id), sizeof(id));
	}

	return out.good();
}

void CitizenMap::load(ifstream& in)
{
	int size;

	in.read(rcastc(&size), sizeof(size));
	for (int i = 0; i < size; i++)
	{
		Citizen *c = new Citizen(in);
		insert(pair<int, Citizen*>(c->getID(), c) );
		
	}
}

void CitizenMap::loadExist(ifstream& in,CitizenMap *clist,Province *p)
{
	int id;
	int size;
	in.read(rcastc(&size), sizeof(size));

	for (int i = 0; i < size; i++)
	{
		in.read(rcastc(&id), sizeof(id));
		Citizen* c = clist->isExist(id);
		c->setProvince(p);
		insert(pair<int, Citizen*>(c->getID(), c));
	}
}