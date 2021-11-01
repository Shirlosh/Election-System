#include "voteslist.h"
#include <cmath>

VotesList::VotesList(int candidatesAmount) 
{
	numofProvinceCandidates = candidatesAmount;
}

void VotesList::AddTail(Party *p, int percentage, int NumofVote, int numofCandidates) 
{
	VotesNode newNode;
	newNode.party = p;
	newNode.Percentage = percentage;
	newNode.NumOfvote = NumofVote;
	newNode.numofcandidates = numofCandidates;
	
	push_back(newNode);
}

// update the vote list with the new requested vote
// returns true if the party is succeed and false if the party couldnt be found
void VotesList::addVote(int partyserial)
{
	iterator itr = begin();
	sumOfVotes++;

	for (; itr != end(); itr++)
	{
		int PartySerial = itr->party->getSerial();

		if (PartySerial == partyserial)
		{
			itr->NumOfvote++;
			itr->party->addVote();
			updatePercentage();
			updatePartiesCandidates();
			break;
		}
	}

	if(itr == end()) // if itr got to end - then the serial doesnt exist
		throw invalid_argument("incorrect party serial number.");
}

void VotesList:: setWinner()
{
	iterator cur = begin(), max=begin();

	for (; cur != end(); cur++)
	{
		if (cur->NumOfvote > max->NumOfvote) // if the cur node is greater
			max = cur;

		else if (cur->NumOfvote == max->NumOfvote) // if there is a tie - the lower serial takes
		{
			if (cur->party->getSerial() < max->party->getSerial())
				max = cur;
		}
	}

	winner = max->party;
}

void VotesList::setnumOfCandidates(int numofCandidates)
{
	numofProvinceCandidates = numofCandidates;
}

void VotesList::updatePercentage()
{
	iterator cur = begin();
	
	if(sumOfVotes == 0)
		throw runtime_error("cannot calculate percentage for unvoted province (dividion by 0)");

	for (; cur != end(); cur++)
	{
		double temp = (double)cur->NumOfvote / (double)sumOfVotes;
		cur->Percentage = temp * 100;
	}
}

void VotesList::resetCandidatesLists()
{
	iterator cur = begin();

	for (; cur != end(); cur++)
		cur->list.clear();
}

// utilize the numOfcandidate the party provides
void VotesList::updatePartiesCandidates()
{
	iterator cur = begin();
	
	double votesPerCan,temp;
	double candidatesLeft = numofProvinceCandidates;

	for (; cur != end(); cur++) // candidate division by percentage
	{
		votesPerCan = (double)sumOfVotes / (double)numofProvinceCandidates; // how many vote provides a candidate
		temp = (double)cur->NumOfvote / votesPerCan; 
		cur->numofcandidates = (int)floor(temp);
		cur->rest = (double)cur->NumOfvote - cur->numofcandidates * temp ;//remain
		candidatesLeft -= cur->numofcandidates;
	}

	while (candidatesLeft != 0) { // division of the remain candidates

		VotesNode *p = getMaxRest();
		p->numofcandidates++;
		p->rest = 0;
		candidatesLeft--;
	}

	
	for (cur = begin(); cur != end(); cur++)  // update party candidate variable
		cur->party->setNumOfCandidates(cur->numofcandidates);

}
//candidates assignation 
void VotesList:: updateList(CandidateMap& clst)
{
	iterator cur = begin();
	CandidateMap::iterator itr;
	Candidate* newCandidate = nullptr;
	int i;

	for (; cur != end(); cur++)
	{
		int idx = cur->party->candidateIdx;
		itr = cur->party->getCandidateList()->getindex(idx);

		for (i=0; i< cur->numofcandidates; i++,itr++) // get the party candidate and concatenate them toghter
		{
			if (itr == cur->party->getCandidateList()->end())
			{
				cur->party->candidateIdx = 0;
				throw runtime_error("there are not enough candidates in the party");
			}

			else
				cur->list.insert((*itr)); // add the requested node to the end of the candidates list
		}

		cur->party->candidateIdx += i;
	}

}

VotesNode* VotesList::getMaxRest()
{
	iterator cur = begin(), max = begin();

	for (; cur != end(); cur++)
	{
		if (cur->rest > max->rest)
			max = cur;
	}

	return &(*max);
}


Party* VotesList::getParty(int idx) const
{	
	if (empty())
		return nullptr;

	const_iterator cur = begin();
	
	for (; cur != end(); cur++)
	{
		if (cur->party->getSerial() == idx)
			cur->party;
	}

	return cur->party;
}

ostream& operator<<(ostream& os, const VotesList& v) 
{
	VotesList::const_iterator cur = v.begin();

	for (; cur != v.end(); cur++)
	{
		os << "\tParty Name: " << cur->getParty()->getName() << endl;
		os << "\tAmount of voters: " << cur->getNumOfVotes() << endl;
		os << "\tVoters Percentage: " << cur->getPercentage() << "%" <<endl;
		os << "\tthe party Candidates are: " << endl;
		os << cur->getCandidateMap() ;
	}

	return os;
}


void VotesList::save(ofstream& out) const
{
	int serial;
	if (winner != nullptr)
		serial = winner->getSerial();
	else
		serial = -1; // if there is no winner yet, serial is -1 - undifined

	const_iterator cur = begin();
	int _size = size();

	out.write(rcastcc(&numofProvinceCandidates), sizeof(numofProvinceCandidates)); 
	out.write(rcastcc(&sumOfVotes), sizeof(sumOfVotes));
	out.write(rcastcc(&serial), sizeof(serial)); 
	out.write(rcastcc(&_size), sizeof(_size));

	for (; cur != end(); cur++)
	{
		int partySerial = cur->party->getSerial();
		
		out.write(rcastcc(&partySerial), sizeof(partySerial));
		out.write(rcastcc(&(cur->NumOfvote)), sizeof(cur->NumOfvote) );
		out.write(rcastcc(&(cur->Percentage)), sizeof(cur->Percentage));
		out.write(rcastcc(&(cur->numofcandidates)), sizeof(cur->numofcandidates));

		cur->list.saveIDs(out);
	}
}

void VotesList::load(ifstream& in, PartyList* list)
{
	int winningParty;
	int size;
	Party* p;
	in.read(rcastc(&numofProvinceCandidates), sizeof(numofProvinceCandidates));
	in.read(rcastc(&sumOfVotes), sizeof(sumOfVotes));
	
	//utilize winning party:
	in.read(rcastc(&winningParty), sizeof(winningParty));
	
	if (winningParty == -1)
		p = nullptr;

	else
	{
		p = list->getParty(winningParty);
		winner = p;
	}	

	//read list nodes:
	in.read(rcastc(&size), sizeof(size));

	for (int i = 0; i < size; i++) 
	{
		//get party:
		int partySerial;
		in.read(rcastc(&partySerial), sizeof(partySerial));
		p = list->getParty(partySerial);
		// load and add the node:
		loadNode(in, p);
		
	}
}

void VotesList::loadNode(ifstream& in, Party* p)
{
	VotesNode newNode;

	newNode.party = p;
	in.read(rcastc(&newNode.NumOfvote), sizeof(newNode.NumOfvote));
	in.read(rcastc(&newNode.Percentage), sizeof(newNode.Percentage));
	in.read(rcastc(&newNode.numofcandidates), sizeof(newNode.numofcandidates));
	//load candidates list:
	newNode.list.loadExist(in, p->getCandidateList());

	push_back(newNode);
}
