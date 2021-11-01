#pragma warning (disable: 4996)
#include "province.h"
#include "citizen.h"
#include <iostream>
#include "party.h"
#include "partylist.h"

Province::Province(string province, int numOfCandidates)
{
	setNumOfCandidates(numOfCandidates);
	result.setnumOfCandidates(this->numOfCandidates);
	setName(province);
	Percentage = 0;
}

Province::Province(ifstream& in, CitizenMap* list,PartyList* plist) : result(in,plist)
{
	load(in, list);
}

Province::Province(const Province& other) : result(numOfCandidates)
{
	*this = other;
}

Province::~Province()
{
	allowVote.clear();
	choosenCandidates.~CandidateMap();
	result.clear();
}

void Province::setName(string name)
{
	if (ProvinceName.empty())
		ProvinceName.clear();

	ProvinceName = name;
}
void Province::setSerialNum(int serial)
{
	serialNum = serial;
}

void Province::setAllowVote(Citizen* node)
{
	allowVote.insert(pair<int, Citizen*>(node->getID(), node));
}

void Province::setPercentage()
{
	Percentage = calculatePercentage(); 
}

void Province:: setNumOfCandidates(int numOfCandidates) 
{
	try
	{
		if (numOfCandidates < 0)
			throw invalid_argument("number of candidates must be positive, try again.");

		this->numOfCandidates = numOfCandidates;
	}

	catch (invalid_argument& ex) 
	{
		cout << "Error: " << ex.what() << endl; 
		cout << "number of candidate: ";
		cin >> numOfCandidates;
		setNumOfCandidates(numOfCandidates);
	}
}

void Province::setChoosenCandidates(CandidateMap &cList)
{
	choosenCandidates = cList;
}

void Province::setResult(int partySerial)
{
	result.addVote(partySerial);
	setPercentage();
	result.setWinner();
}

const Province& Province::operator=(const Province& other)
{
	setName(other.ProvinceName);
	serialNum = other.serialNum;
	allowVote = other.allowVote;
	Percentage = other.Percentage;
	setNumOfCandidates(other.numOfCandidates);
	choosenCandidates = other.choosenCandidates;
	result = other.result;

	return *this;
}

ostream& operator<<(ostream& os, const Province& p) 
{
	p.toOs(os);
	os << "Province Name: " << p.ProvinceName << endl;
	os << "Province Serial Number: " << p.serialNum << endl;
	os << "Candidates amount: " << p.numOfCandidates << endl;

	return os;
}

double Province:: calculatePercentage() 
{
	int canVote = allowVote.size();
	int Voters = result.getSum();
	if (canVote == 0)
		throw runtime_error("cannot calculate percentage for an empty province(dividion by 0)");

	double temp = ((double)Voters / (double)canVote);
	return temp * 100;
}

bool Province::save(ofstream& out) const
{
	saveType(out);
	result.save(out);

	int nameLen = ProvinceName.length();
	out.write(rcastcc(&nameLen), sizeof(nameLen));
	out.write(rcastcc(&ProvinceName[0]), nameLen);


	out.write(rcastcc(&serialNum), sizeof(serialNum));
	out.write(rcastcc(&Percentage), sizeof(Percentage));
	out.write(rcastcc(&numOfCandidates), sizeof(numOfCandidates));

	allowVote.saveIDs(out); 	
	return out.good();
}

bool Province::saveType(ofstream& out) const
{
	char type[TYPE_LEN + 1];
	strncpy(type, typeid(*this).name() + 6, TYPE_LEN);

	out.write(rcastcc(type), TYPE_LEN); 
	return out.good();
}


void Province::load(ifstream& in, CitizenMap* list)
{
	int nameLen;
	//load name:
	in.read(rcastc(&nameLen), sizeof(nameLen));
	ProvinceName.resize(nameLen);
	in.read(rcastc(&ProvinceName[0]), nameLen);

	in.read(rcastc(&serialNum), sizeof(serialNum));
	in.read(rcastc(&Percentage), sizeof(Percentage));
	in.read(rcastc(&numOfCandidates), sizeof(numOfCandidates));

	allowVote.loadExist(in, list, this);
}