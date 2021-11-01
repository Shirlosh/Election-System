#include "simpleElections.h"


simpleElections::simpleElections(int d, int m, int y, int numofcandidates) : Elections(d,m,y)
{
	char name[] = { "Province" };
	Elections::addProvince(name,numofcandidates,DIVIDED_PROVINCE);
}

void simpleElections::addProvince(string provinceName, int candidateNum, int provinceType)
{
	throw invalid_argument("invalid operation - add province option is unable in simple elections");
}

void simpleElections::showProvinceList() const
{
	throw invalid_argument("invalid operation - show province option is unable in simple elections");
}


