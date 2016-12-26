#pragma once
#include"myheader.h"
#include"Arc.h"

class Node
{
public:
	int		m_iNode;
	char	m_szName[16];
	bool	m_bMarked;
	int		m_iDegree;
	Arc*	m_pFirst;
	double weight;
	double ECC;
	double suvivalTime[SampleNum];

public:
	Node() {
		m_iNode = 0;
		m_szName[0] = '\0';
		m_bMarked = false;
		m_iDegree = 0;
		m_pFirst = 0;
		weight = 0;
		ECC = 0;
	}
	Node(int iNode, char szName[16])
	{
		m_iNode = iNode;
		strcpy_s(m_szName, szName);
		m_bMarked = false;
		m_iDegree = 0;
		m_pFirst = 0;
		weight = 0;
		ECC = 0;
	}
	~Node() {
		if (m_pFirst)
			delete m_pFirst;
	}
public:
	void InsertArc(int iTo, double fWeight)
	{
		Arc* newArc = new Arc(iTo, fWeight, m_pFirst);
		m_pFirst = newArc;
	}

	Node& operator=(const Node &node) {
		m_iNode = node.m_iNode;
		strcat_s(m_szName, node.m_szName);
		m_bMarked = node.m_bMarked;
		m_iDegree = node.m_iDegree;
		if (node.m_pFirst == NULL)
			m_pFirst = NULL;
		else {
			Arc* FirstArc = new Arc();
			*FirstArc = *node.m_pFirst;
			m_pFirst = FirstArc;
			Arc* oldNextArc = node.m_pFirst->m_pNextArc;
			Arc* pArc = m_pFirst;
			while (oldNextArc) {
				Arc* newNextArc = new Arc();
				*newNextArc = *oldNextArc;
				pArc->m_pNextArc = newNextArc;
				oldNextArc = oldNextArc->m_pNextArc;
				pArc = pArc->m_pNextArc;
			}
			pArc->m_pNextArc = NULL;
		}
		weight = node.weight;
		ECC = node.ECC;
		for (int j = 0;j < SampleNum;j++)
			suvivalTime[j] = node.suvivalTime[j];
		return *this;
	}
};

