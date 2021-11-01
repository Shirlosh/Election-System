#include <iostream>
#include "date.h"
#include "elections.h"
#include "read.h"
#include <list>

const int MAX_SIZE = 20;

enum elOPTIONS 
{
	READ_PROVINCE = 1, READ_CITIZEN, READ_PARTY,
	READ_CANDIDATE, SHOW_PROVINCE_LIST, SHOW_CITIZEN_LIST, SHOW_PARTY_LIST,
	ADD_VOTE, SHOW_RESULT, EXIT, SAVE_ELECTIONS, LOAD_ELECTIONS
};

using namespace std;

void elMenu(Elections* e) {

	int input = 0;

	cout << "please choose one of the actions: " << endl;
	cout << "1- to add a province" << endl;
	cout << "2- to add a citizen" << endl;
	cout << "3- to add a party" << endl;
	cout << "4- to add a candidate" << endl;
	cout << "5- to show provinces" << endl;
	cout << "6- to show citizens" << endl;
	cout << "7- to show parties" << endl;
	cout << "8- to vote" << endl;
	cout << "9- to show results" << endl;
	cout << "11- to save the elections" << endl;
	cout << "12- to load elections from file" << endl;

	while (input != EXIT) {
		cout << "\nplease choose an action (10 to exit): ";
		cin >> input;

		if (input == READ_PROVINCE)
			Read::readProvince(*e);

		else if (input == READ_CITIZEN)
			Read::readCitizen(*e);

		else if (input == READ_PARTY)
			Read::readParty(*e);

		else if (input == READ_CANDIDATE)
			Read::readCandidate(*e);

		else if (input == SHOW_PROVINCE_LIST)
			e->showProvinceList();

		else if (input == SHOW_CITIZEN_LIST)
			e->showCitizenList();

		else if (input == SHOW_PARTY_LIST)
			e->showPartyList();

		else if (input == ADD_VOTE)
			Read::addVote(*e);

		else if (input == SHOW_RESULT)
			e->showResult();

		else if (input == SAVE_ELECTIONS)
			Read::saveElections(e);

		else if (input == LOAD_ELECTIONS)
		{
			delete[] e;
			e = Read::loadExistElections();
		}

		else
			cout << "incorrect input - try again" << endl;
	}
}

int main() 
{	
	enum electionSetting { CREATE_NEW = 1, LOAD_EXIST };
	int input;
	Elections* e = nullptr;
	cout << "welcome to Elections system! please choose your one of the following options: " << endl;
	cout << "\tto create a new Elections day please enter 1" << endl;
	cout << "\tto load existing Elections please enter 2" << endl;
	cin >> input;

	try 
	{
	if (input == CREATE_NEW)
		e = Read::createNewElections();


	else if (input == LOAD_EXIST)
		e = Read::loadExistElections();

	else
		throw invalid_argument("incorrect input");	
	}

	catch (invalid_argument& ex)	 { cout <<"Error: "<< ex.what() << endl;	delete e;	exit(1); }
	catch (bad_alloc& ex)			 { cout <<"Error: "<< ex.what() << endl;				exit(1); }
	
	cout << "----------------------------------------" << endl;

	try { elMenu(e); }
	catch (...) { cout << "Error: unknown error occurred." << endl; }
	cout << "bye bye~!" << endl;
}
