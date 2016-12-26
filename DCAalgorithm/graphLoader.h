#pragma once
#include"myheader.h"

class GraphArc {
public:
	char m_szFrom[16];
	char m_szTo[16];
	double m_fWeight;
public:
	GraphArc()
	{
		m_fWeight = 1.0f;
	}
	GraphArc(char szFrom[16], char szTo[16], double fWeight)
	{
		strcpy_s(m_szFrom, szFrom);
		strcpy_s(m_szTo, szTo);
		m_fWeight = fWeight;
	}
};

class GraphLoader
{
public:
	std::vector<GraphArc>	m_RawGraph;
	size_t		m_nArcs;
public:
	GraphLoader() {
		m_nArcs = 0;
	}
	GraphLoader(const char* szFileName);
};
