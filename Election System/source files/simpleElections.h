#pragma once
#include "elections.h"

class simpleElections : public Elections
{

public:
	simpleElections(int d, int m, int y, int numofcandidates);
	simpleElections(ifstream& in) : Elections(in) {}
	virtual void addProvince(string provinceName, int candidateNum, int provinceType) override ;
	virtual void showProvinceList() const override;


};

