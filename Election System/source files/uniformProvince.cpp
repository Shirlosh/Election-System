#include "uniformProvince.h"

void uniformProvince::electorsDistribution()
{	
	Party* provinceWin = result.getWinner();

	if (provinceWin != nullptr)
		provinceWin->addElectors(numOfCandidates);

}

void uniformProvince::toOs(ostream& os) const
{
	os << "Province type: Uniform" << endl;

}


