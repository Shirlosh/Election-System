#include "dividedProvince.h"
#include "voteslist.h"

void dividedProvince::electorsDistribution()
{
	VotesList::iterator cur = result.begin();

	for (; cur != result.end(); cur++) 
	{
		int add = cur->getParty()->getNumOfCandidates();
		cur->getParty()->addElectors(add);
	}
	
}

void dividedProvince::toOs(ostream& os) const
{
	os << "Province type: Divided" << endl;
}

