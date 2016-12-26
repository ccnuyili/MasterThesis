#pragma once
#include"myheader.h"

class Arc
{
public:
	int m_iNodeTo;
	double m_fWeight;
	Arc* m_pNextArc;
public:
	Arc()
	{
		m_iNodeTo = -1;
		m_fWeight = 0;
		m_pNextArc = NULL;
	}
	Arc(int iNodeTo, double fWeight, Arc* pNextArc)
	{
		m_iNodeTo = iNodeTo;
		m_fWeight = fWeight;
		m_pNextArc = pNextArc;
	}
	~Arc()
	{
		if (m_pNextArc)
			delete m_pNextArc;
	}
	Arc& operator=(const Arc &arc) {
		m_iNodeTo = arc.m_iNodeTo;
		m_fWeight = arc.m_fWeight;
		if (arc.m_pNextArc != NULL)
			m_pNextArc = new Arc(*(arc.m_pNextArc));
		else
			m_pNextArc = NULL;
		return *this;
	}
};