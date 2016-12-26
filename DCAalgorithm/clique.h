#pragma once
#include"myheader.h"

class Clique
{
public:
	vector<string>		m_CoreNodes;
	vector<string>		m_AttachNodes;
	vector<int>			m_CliqueNodeIDs;
	vector<string>	m_CliqueNodeNames;
	double os;
	bool match;
	int sliceID;

public:
	Clique()
	{
		os = 0;
		match = true;
	}

	Clique(int No, int sid)
	{
		os = 0;
		match = true;
		sliceID = sid;
	}
/*
	Clique& operator=(const Clique &c) {
		m_CoreNodes = c.m_CoreNodes;
		m_AttachNodes = c.m_AttachNodes;
		m_CliqueNodeIDs = c.m_CliqueNodeIDs;
		m_CliqueNodeNames = c.m_CliqueNodeNames;
		os = c.os;
		match = c.match;
		sliceID = c.sliceID;
		return *this;
	}
	*/

	friend inline ostream& operator<<(ostream& out, const Clique& s)
	{
		out <<"sliceID:"<< s.sliceID<<"\tOS:"<<s.os << "\t";
		for (size_t i = 0;i < s.m_CoreNodes.size();i++)
			out << s.m_CoreNodes[i] << " ";
		out << " | ";
		for (size_t i = 0;i < s.m_AttachNodes.size();i++)
			out << s.m_AttachNodes[i] << " ";
		out <<endl;
		return out;
	}
};

class CompCliqueSizeDecend_CliqueNodes
{
public:
	bool operator ()(const Clique *stItem1, const Clique *stItem2) {
		return stItem1->m_CliqueNodeIDs.size() > stItem2->m_CliqueNodeIDs.size();
	}
};

class CompCliqueSizeDecend_CliqueProteins
{
public:
	bool operator ()(const Clique *stItem1, const Clique *stItem2) {
		return stItem1->m_CliqueNodeNames.size() > stItem2->m_CliqueNodeNames.size();
	}
};

class ComplexSet {

public:
	vector<Clique*> cliqueVex;
public:
	ComplexSet() {
	}

	~ComplexSet() {
		for (size_t i = 0;i < cliqueVex.size();i++) {
			delete cliqueVex[i];
		}
		cliqueVex.clear();
	}

	ComplexSet(const ComplexSet &other) {
		for (size_t i = 0;i < other.cliqueVex.size();i++) {
			cliqueVex.push_back(new Clique(*other.cliqueVex[i]));
		}
	}
};

