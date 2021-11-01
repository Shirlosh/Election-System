#pragma warning (disable: 4996)
#include "elections.h"

using namespace std;

template <class T>
void saveStruct(const T& obj, ofstream& out)
{
	int _size = obj.size();
	out.write(rcastcc(&_size), sizeof(_size));

	for (auto itr = obj.begin(); itr != obj.end(); ++itr)
		(*itr)->save(out);


	if (!out.good())
		throw runtime_error("The attempt to save the file has failed");
}


Elections::Elections(int d, int m, int y) : Electionsdate(d, m, y)
{}

Elections::Elections(ifstream& in) : Electionsdate(in),voterRegister(in)
{
	PartiesList.load(in, &voterRegister);
	ProvincesList.load(in, &voterRegister,&PartiesList);
	CandidateMap::updateCandidates(&voterRegister, &PartiesList); // update province information for all candidates
}

Elections::~Elections()
{
	voterRegister.clear();
	PartiesList.clear();
	ProvincesList.clear();
}

void Elections::showDate() const
{
	cout << Electionsdate << endl;
}

void Elections::showCitizenList() const 
{
	cout << voterRegister << endl;
}

void Elections::showPartyList() const 
{
	cout << PartiesList << endl;
}
void Elections::showProvinceList() const
{
	cout << ProvincesList << endl;
}

Citizen* Elections::addCitizen(string cname, int id,int birthyear,int provSerial)
{
	if (ProvincesList.size() <= provSerial) // if the provided serial is bigger then the counter then is invalid prov num
		throw invalid_argument("province doesn't exist");

	if (voterRegister.isExist(id))
		throw invalid_argument("this citizen id is already exist");

	Province* p = ProvincesList.getNode(provSerial);
	Citizen* c = voterRegister.addTail(cname, id, birthyear, p, Electionsdate.getYear());

	p->setAllowVote(c);

	return c;
}

void Elections::addCandidate(int id, int partySerial, int provinceSerial)
{
	Citizen *temp;
	temp = voterRegister.isExist(id);

	if (!temp)
		throw invalid_argument("citizen id doesn't exist");

	else
	{
		if (provinceSerial > ProvincesList.size())
			throw invalid_argument("province serial doesn't exist");


		Candidate *c = new Candidate(*temp,partySerial, provinceSerial); 
		Party *party = PartiesList.getParty( c->getPartySerial() ); 
		
		if (party)
			party->addToList(*c);

		else
			throw invalid_argument("party serial doens't exist");
	}
}

void Elections::addParty(string pName, int cID)
{
	Citizen* president = voterRegister.isExist(cID);
	int counter = PartiesList.size();

	if (!president)
		throw invalid_argument("citizen id doesnt exist");

	Party *p = new Party(pName, *president);

	p->setSerial(counter);
	PartiesList.push_back(p);
	ProvincesList.addParty(p);
}

void Elections::addProvince(string provinceName,int candidateNum, int provinceType)
{
	Province* p;

	if (provinceType == UNIFORM_PROVINCE)	// as we marked at read func - 1 for uniform
		p = new uniformProvince(provinceName, candidateNum);

	else
		p = new dividedProvince(provinceName, candidateNum);

	int serial = ProvincesList.size();
	p->setSerialNum(serial);
	ProvincesList.push_back(p);	
}

void Elections::addVote(int ID, int PartySerial)
{
	Citizen* c = voterRegister.isExist(ID);
	if (c == nullptr )
		throw invalid_argument("incorrect citizen id number.");
	if (c->getVote())
		throw invalid_argument("citizen already voted");

	if (PartiesList.size() < PartySerial)
		throw invalid_argument("incorrect party serial number.");

	c->setVote();												// mark the citizen as voted 

	int provinceSerial = c->getProvinceSerialNum();
	Province* p = ProvincesList.getNode(provinceSerial);

	p->setResult(PartySerial);									// utlize result array with the new vote

	try { ProvincesList.candidatesAssignation(&PartiesList); } // update all the candidates lists
	catch (invalid_argument& ex)			{ cout << "Error: " << ex.what() << endl; }

	ProvincesList.setElectors(&PartiesList);				// set the electors of each province
	PartiesList.ArrangeParties();							// arrange the parties by electors
}


void Elections::showResult() const
{	
	ProvinceList::const_iterator iProvince = ProvincesList.begin();

	cout << "******************* " << Electionsdate << " *******************" << endl;

	for (; iProvince != ProvincesList.end(); iProvince++)
	{
		cout << "province " << (*iProvince)->getName()<< endl;
		cout << "province winner: " << (*iProvince)->getResult().getWinner()->getPcandidate() << endl;
		cout << "amount of candidates: " << (*iProvince)->getNumOfCandidates() << endl;
		cout << "the total voting percentage in the province is: " << (*iProvince)->getPercentage() << "%" << endl;
		cout << "and parties are: " << endl;
		cout << (*iProvince)->getResult();
	}

	PartyList::const_iterator iParty = PartiesList.begin();
	for (int counter = 1; iParty != PartiesList.end(); iParty++, counter++)
	{
		cout << "#" << counter <<" " << (*iParty)->getPcandidate() << " recived " << (*iParty)->getElectors() << " electors";
		cout << " and got " << (*iParty)->getVotes() << " votes" << endl;
	}	
}


void Elections::save(ofstream& out) const
{
	saveType(out);
	Electionsdate.save(out);
	voterRegister.save(out);
	saveStruct(PartiesList, out);
	saveStruct(ProvincesList, out);
	
	if (!out.good())
		throw runtime_error("The attempt to save the file has failed");
}

void Elections::saveType(ofstream& out) const
{
	char type[TYPE_LEN + 1];
	strncpy(type, typeid(*this).name() + 6, TYPE_LEN);
	out.write(rcastcc(type), TYPE_LEN);

	if (!out.good())
		throw runtime_error("The attempt to save the file has failed");
}
