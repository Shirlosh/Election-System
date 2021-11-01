#include "party.h"
#include "partylist.h"

using namespace std;
void PartyList::ArrangeParties()
{
	iterator itr = begin();

	for (; itr != end(); itr++)
		maxToHead(itr);
}

Party* PartyList::getParty(int partySerial) const
{
	const_iterator itr = begin();

	for (; itr != end(); itr++)
	{
		if ((*itr)->getSerial() == partySerial)
			return (*itr);
	}

	return nullptr;
}

void PartyList::resetIdx()
{
	const_iterator itr = begin();

	for (; itr != end(); itr++)
		(*itr)->candidateIdx = 0;
}

void PartyList::maxToHead(iterator head)
{
	iterator cur = head;
	iterator max = head;

	for (; cur != end(); cur++) //get MAX and his Prev
	{
		if ((*cur)->getElectors() > (*max)->getElectors())
			max = cur;
	}

	iter_swap(max, head);
}

void PartyList:: resetElectors()
{
	const_iterator itr = begin();

	for (; itr != end(); itr++)
		(*itr)->resetElectors();
}

ostream& operator<<(ostream& os, const PartyList& p) {
	PartyList::const_iterator itr = p.begin();

	for (; itr != p.end(); itr++)
		os << *(*itr) << endl;

	return os;
}


void PartyList::load(ifstream& in,CitizenMap* list)
{
	int size;
	int presidentid;

	in.read(rcastc(&size), sizeof(size));
	for (int i = 0; i < size; i++)
	{
		in.read(rcastc(&presidentid), sizeof(presidentid)); // get the president
		Citizen *c = list->isExist(presidentid);

		Party* p = new Party(in,*c,list);
		push_back(p);
	}
}