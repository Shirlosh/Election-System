#pragma once
#include "province.h"


class uniformProvince : public Province
{

public:

	uniformProvince(string province, int numOfCandidates) : Province(province, numOfCandidates) {}
	uniformProvince(ifstream& in, CitizenMap* list, PartyList* plist) : Province(in, list,plist) {}

	virtual void electorsDistribution() override;

	virtual void toOs(ostream &os) const override;
};

