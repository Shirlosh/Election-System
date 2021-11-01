#pragma warning (disable: 4996)
#include "read.h"
#include <string>
using namespace std;

const int MAX_SIZE = 20;

void Read:: readProvince(Elections& e)
{
	string provinceName;
	int candidateNum;
	int provinceType;

	cout << "province name: ";
	cin >> provinceName;
	cout << "number of candidate: ";
	cin >> candidateNum;

	// read province type:
	while (true)
	{
		cout << "province type (enter 1 for uniform, 2 for divided): ";
		cin >> provinceType;
		try
		{
			if (provinceType != UNIFORM_PROVINCE && provinceType !=DIVIDED_PROVINCE)
				throw invalid_argument("incorrect province type, try again.");
			break;
		}
		catch (invalid_argument& ex) { cout << "Error: " << ex.what() << endl; }
	}

	try { e.addProvince(provinceName, candidateNum, provinceType); }
	catch (bad_alloc &ex) { cout << "Error: " << ex.what() << endl; }
	catch (invalid_argument &ex) { cout << "Error: " << ex.what() << endl; }


}

void Read::readCitizen(Elections& e)
{
	string citizenName;
	int id, birthYear, provinceSerial = 0;
	cout << "Citizen name: ";
	cin >> citizenName;
	cout << "Citizen id: ";
	cin >> id;
	cout << "Citizen birth year: ";
	cin >> birthYear;

	if (typeid(e).name() == typeid(Elections).name()) // if this is normal elections read province serial
	{
		cout << "Province serial number: ";
		cin >> provinceSerial;
	}

	Citizen* c = nullptr;

	try {c = e.addCitizen(citizenName, id, birthYear, provinceSerial); }
	catch (invalid_argument& ex)	{ cout << "Error: " << ex.what() << endl; delete[] c; }
	catch (bad_alloc &ex)			{ cout << "Error: " << ex.what() << endl; }
}

void Read::readParty(Elections& e)
{
	string partyName;
	int cID;

	cout << "Party name: ";
	cin >> partyName;
	cout << "President candidate ID: ";
	cin >> cID;

	try { e.addParty(partyName, cID); }
	catch (invalid_argument &ex)	 { cout << "Error: " << ex.what() << endl; }
	catch (bad_alloc& ex)			 { cout << "Error: " << ex.what() << endl; }
}

void Read::readCandidate(Elections &e)
{
	int id, partySerial, provinceSerial = 0;
	int res;

	cout << "Candidate ID: ";
	cin >> id;
	cout << "Party Serial: ";
	cin >> partySerial;
	
	if (typeid(e).name() == typeid(Elections).name()) // if this is normal elections read province serial
	{
		cout << "Province serial number: ";
		cin >> provinceSerial;
	}

	try { e.addCandidate(id, partySerial, provinceSerial); }
	catch (invalid_argument& ex)	 { cout << "Error: " << ex.what() << endl; }
	catch (bad_alloc& ex)			 { cout << "Error: " << ex.what() << endl; }

}

void Read::addVote(Elections& e)
{
	int id, partySerial;
 	cout << "Voter ID: ";
	cin >> id;
	cout << "Party serial: ";
	cin >> partySerial;

	try { e.addVote(id, partySerial); }
	catch (invalid_argument& ex)			{ cout << "Error: " << ex.what() << endl; }
	catch (runtime_error& ex)				{ cout << "Error: " << ex.what() << endl; }
	catch (...)							    { cout << "unknown Error." << endl; }
}


Elections* Read::createNewElections()
{
	enum ELECTIONSTYPE { SIMPLE_ELECTIONS = 1, NORMAL_ELECTIONS };
	int d, m, y;
	int electionSettings;
	cout << "For simple Elections please enter 1 , for normal Elections please enter 2:" << endl;
	cin >> electionSettings;
	cout << "please enter Elections date: " << endl;
	cin >> d >> m >> y;

	Elections* e = nullptr;

	if (electionSettings == SIMPLE_ELECTIONS)
	{
		int numofcandidates;
		cout << "candidates amount:";
		cin >> numofcandidates;
		e = new simpleElections(d, m, y, numofcandidates);
	}

	else if (electionSettings == NORMAL_ELECTIONS)
		e = new Elections(d, m, y); 				//normal elections
	
	else
		throw invalid_argument("incorrect input");

	return e;
}


Elections* Read::loadExistElections()
{
	Elections* e = nullptr;
	char fileName[MAX_SIZE];
	cout << "File name: " << endl;
	cin >> fileName;

	ifstream in(fileName, ios::binary);

	// check if found and open correctly:
	if (!in) 
		throw invalid_argument("couldn't open the file");
	

	//get elections type:
	char type[TYPE_LEN + 1];
	in.read(rcastc(&type), TYPE_LEN);
	type[TYPE_LEN] = '\0';
	
	if (strncmp(typeid(simpleElections).name() + 6, type, TYPE_LEN) == 0)
		e = new simpleElections(in);

	if (strncmp(typeid(Elections).name() + 6, type, TYPE_LEN) == 0)
		e = new Elections(in);

	in.close();
	return e;
}

void Read::saveElections(Elections* e)
{
	char fileName[MAX_SIZE];

	cout << "enter file name: ";
	cin >> fileName;
	try {
		ofstream out(fileName, ios::binary, ios::trunc);

		if (!out)
			throw runtime_error("couldnt create a file please try again later");

		e->save(out);
		out.close();
	}

	catch (runtime_error& ex) { cout << "An error has occurred: " << ex.what() << endl; }
}