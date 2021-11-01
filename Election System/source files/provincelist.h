#pragma once
#include "province.h"
#include "partylist.h"
#include "dividedProvince.h"
#include "uniformProvince.h"
#include <list>
#include "dynamicArray.h"

class ProvinceList : public DynamicArray<Province*>
{
public:
	Province* getNode(int serial) const noexcept(false);

	/*GENERAL*/
	void addParty(Party *p); //if there is a new party - add it to votelist
	void setElectors(PartyList* partylist);
	void resetAllCandidateLists();
	void candidatesAssignation(PartyList* p); // assign candidates to the province

	friend std::ostream& operator<<(std::ostream& os, const ProvinceList& p);

	/*FILES OPERATIONS*/
	// saving to a file in the following order:
	// list len, province details
	bool save(ofstream& out) const;
	void load(ifstream& in, CitizenMap* list, PartyList* plist);
};
