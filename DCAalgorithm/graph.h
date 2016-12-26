#pragma once

#include"Arc.h"
#include"node.h"
#include"clique.h"
#include"graphLoader.h"
#include"proteinExpression.h"

class Graph
{
public:
	std::vector<Node*> m_NodeArray;
	std::vector<Clique*> m_CliqueArray;
	int m_nNumEdges;
	int m_nNumNodes;
	int m_nCliques;
public:

	Graph() {
		m_nNumEdges = 0;
		m_nNumNodes = 0;
		m_nCliques = 0;
	}
	Graph(const char* scFileName);
	~Graph() {
		ClearNodes();
		ClearClique();
	}
	void clearGraph() {
		ClearNodes();
		ClearClique();
		m_nNumEdges = 0;
		m_nNumNodes = 0;
		m_nCliques = 0;
	}
	Graph& operator=(const Graph& g) {
		for (size_t i = 0; i < g.m_NodeArray.size(); i++) {
			if (!g.m_NodeArray[i]) {
				m_NodeArray.push_back(new Node());
				m_NodeArray[i] = NULL;
			}
			else {
				Node* node = new Node();
				*node = *g.m_NodeArray[i];
				m_NodeArray.push_back(node);
			}
		}
		m_nNumEdges = g.m_nNumEdges;
		for (size_t i = 0; i < g.m_CliqueArray.size(); i++) {
			m_CliqueArray.push_back(new Clique(*g.m_CliqueArray[i]));
		}
		m_nNumNodes = g.m_nNumNodes;
		m_nCliques = g.m_nCliques;
		return *this;
	}
	void ClearNodes() {
		for (size_t i = 0; i < m_NodeArray.size(); ++i) {
			if (m_NodeArray[i] != NULL)
				delete m_NodeArray[i];
		}
		m_NodeArray.clear();
		m_nNumNodes = 0;
	}
	void ClearClique() {
		for (size_t i = 0; i < m_CliqueArray.size(); ++i) {
			if (m_CliqueArray[i] != 0)
				delete m_CliqueArray[i];
			m_CliqueArray[i] = 0;
		}
		m_nCliques = 0;
		m_CliqueArray.clear();
	}
	Node* GetNode(int iIndex)
	{
		return m_NodeArray[iIndex];
	}
	Node* GetNode(char m_szName[]) {
		for (size_t i = 0; i < m_NodeArray.size(); i++) {
			if (m_NodeArray[i] == NULL)
				continue;
			if (strcmp(m_NodeArray[i]->m_szName, m_szName) == 0) {
				return m_NodeArray[i];
			}
		}
		return NULL;
	}

	bool IsIncludedInClique(int inode, Clique *clique);
	void getEdgeECC();
	template <class ProteinType> void getNormSuvivalTime(const ProteinVec<ProteinType> &expressionMatrix, int k) {
		double maxSuvival = 0, minSurvival = 100;
		double suvTime;
		for (size_t i = 0;i < expressionMatrix.ProteinVex.size();i++) {
			for (int j = 0;j < SampleNum;j++) {
				suvTime = expressionMatrix.ProteinVex[i]->consecutiveActiveTimePointNums(j);
				if (suvTime > maxSuvival)
					maxSuvival = suvTime;
				if (suvTime < minSurvival)
					minSurvival = suvTime;
			}
		}
		for (size_t i = 0;i < m_NodeArray.size();i++) {
			Node *nodex = m_NodeArray[i];
			Protein *p = expressionMatrix.search(nodex->m_szName);
			suvTime = p->consecutiveActiveTimePointNums(k);
			nodex->suvivalTime[k] = (suvTime - minSurvival) / (maxSuvival - minSurvival);

		}
	}
	void FilterClique_NodeIDs(double tvOverlap);
	void FilterClique_NodeNames(double tvOverlap);
	void outPutIntervalComplex(const string scFileName);
	void outPutAllComplex(const string scFileName);
	void outPutAllComplexLog(const string scFileName);
	double getWeightOfNode2Clique(const Node* node, Clique *clique, int interval, double alpha);
	double getAveNodeWeight(Clique *clique, int interval, double alpha);
	int FindNodeWithMinWeightInClique(Clique *clique, int interval, double alpha);
	void getWeight(int interval, double alpha, double beta);
	void getCliques(int interval, double tv, double cliqueAveWtv, double outTV, double alpha);

};