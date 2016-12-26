
#include "stdafx.h"
#include"graph.h"

Graph::Graph(const char* scFileName) {//
	GraphLoader	rawGraph(scFileName);
	for (size_t i = 0;i < rawGraph.m_nArcs;i++)	//
	{
		size_t j, k;
		bool bFoundFrom = false;
		bool bFoundTo = false;
		for (j = 0;j < m_NodeArray.size();j++)	 //
		{
			if (!strcmp(m_NodeArray[j]->m_szName, rawGraph.m_RawGraph[i].m_szFrom))//
																				   //s1=s2??strcmp(s1,s2) == 0;
																				   //s1>s2, strcmp(s1,s2) == 1;
																				   //s1<s2, strcmp(s1,s2) == -1;
			{
				bFoundFrom = true;
				break;
			}

		}
		for (k = 0;k < m_NodeArray.size();k++)
		{
			if (!strcmp(m_NodeArray[k]->m_szName, rawGraph.m_RawGraph[i].m_szTo))
			{
				bFoundTo = true;
				break;
			}
		}
		if (bFoundFrom == false)
		{
			Node* pNode = new Node(m_NodeArray.size(), rawGraph.m_RawGraph[i].m_szFrom);
			m_NodeArray.push_back(pNode);
			j = m_NodeArray.size() - 1;
		}
		if (bFoundTo == false)
		{
			Node* pNode = new Node(m_NodeArray.size(), rawGraph.m_RawGraph[i].m_szTo);
			m_NodeArray.push_back(pNode);
			k = m_NodeArray.size() - 1;
		}

		m_NodeArray[j]->InsertArc(k, rawGraph.m_RawGraph[i].m_fWeight);
		m_NodeArray[j]->m_iDegree++;
		m_NodeArray[k]->InsertArc(j, rawGraph.m_RawGraph[i].m_fWeight);
		m_NodeArray[k]->m_iDegree++;

	}
	m_nNumEdges = rawGraph.m_nArcs;
	m_nNumNodes = m_NodeArray.size();
}

GraphLoader::GraphLoader(const char* szFileName)
{
	m_RawGraph.clear();
	GraphArc arc;
	if (szFileName != "") {

		std::ifstream InFile(szFileName);
		if (!InFile)
		{
			std::cout << "Can't Open The Input File!" << std::endl;
			return;
		}
		for (;;)
		{
			if (!InFile)
				break;
			//	InFile >> arc.m_szFrom >> arc.m_szTo >> arc.m_fWeight;
			InFile >> arc.m_szFrom >> arc.m_szTo;
			if (strcmp(arc.m_szFrom, arc.m_szTo) == 0)
				continue;
			m_RawGraph.push_back(arc);

		}
		InFile.close();
	}
	else {

		do {
			//cin >> arc.m_szFrom >> arc.m_szTo >> arc.m_fWeight;
			cin >> arc.m_szFrom >> arc.m_szTo;
			m_RawGraph.push_back(arc);
		} while (strcmp(arc.m_szFrom, "#") && strcmp(arc.m_szTo, "#"));
	}
	//	m_RawGraph.pop_back();
	m_nArcs = (int)m_RawGraph.size();
}