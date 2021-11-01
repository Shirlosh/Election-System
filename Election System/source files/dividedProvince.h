#pragma once
#include "province.h"

class dividedProvince : public Province
{
public:
	
	dividedProvince(string province, int numOfCandidates) : Province(province,numOfCandidates) {}
	dividedProvince(ifstream& in, CitizenMap* list,PartyList* plist) : Province(in, list,plist) {}

	virtual void electorsDistribution() override;
	virtual void toOs(ostream& os) const override;
};

