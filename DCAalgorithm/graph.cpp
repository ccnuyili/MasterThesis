#include "stdafx.h"
#include"graph.h"
#include"math.h"

bool Graph::IsIncludedInClique(int inode, Clique *clique) {
	for (size_t i = 0; i < clique->m_CliqueNodeIDs.size(); i++) {
		if (inode == clique->m_CliqueNodeIDs[i]) {
			return true;
		}
	}
	return false;
}

void  Graph::getEdgeECC() {//图中每条边的ecc，以及每个节点的ecc，即节点的每条边的ecc之和		
	double mNum = 0;
	double ecc = 0;
	double nodeEcc = 0;
	double dx = 0, dy = 0, mindeg;
	//	double maxecc = -1, minecc = 100;
	for (size_t i = 0;i < m_NodeArray.size();i++) {
		//对于节点x
		nodeEcc = 0;
		Node *nodex = m_NodeArray[i];
		dx = nodex->m_iDegree;
		Arc *arcxy = nodex->m_pFirst;
		while (arcxy != NULL) {//对于x的所有邻居节点Y：
			mNum = 0;
			Node *nodey = m_NodeArray[arcxy->m_iNodeTo];//与x相连的节点y
			dy = nodey->m_iDegree;
			Arc *arcxm = nodex->m_pFirst;//与x相连的节点m
			for (;arcxm != NULL;arcxm = arcxm->m_pNextArc) {//对于x的所有邻居（除了Y外）M：
				if (arcxm != arcxy) {
					Node *nodem = m_NodeArray[arcxm->m_iNodeTo];
					Arc *arcmy = nodem->m_pFirst;
					while (arcmy != NULL) {//遍历与M相连的节点，若与Y与M相连：
						if (arcmy->m_iNodeTo == nodey->m_iNode)
						{
							mNum++;
							break;
						}
						arcmy = arcmy->m_pNextArc;
					}
				}
			}
			if (dx < 2 || dy < 2)
				ecc = 0;
			else {
				mindeg = (dx < dy ? dx - 1 : dy - 1);
				ecc = mNum / mindeg;
			}
			arcxy->m_fWeight = ecc;
			arcxy = arcxy->m_pNextArc;
			nodeEcc += ecc;
		}
		nodex->ECC = nodeEcc;
	}

}

void  Graph::FilterClique_NodeIDs(double  tvOverlap)
{
	sort(m_CliqueArray.begin(), m_CliqueArray.end(), CompCliqueSizeDecend_CliqueNodes());
	int findNum;
	int mi;
	int mj;
	double overlap;
	std::vector<int>::iterator iter;
	for (size_t i = 0; i < m_CliqueArray.size(); i++) {
		m_CliqueArray[i]->match = true;
	}
	for (int i = 0; i < (int)m_CliqueArray.size() - 1; i++) {
		if (m_CliqueArray[i]->match == false)
			continue;
		for (size_t j = i + 1; j < m_CliqueArray.size(); j++) {
			if (m_CliqueArray[j]->match == false)
				continue;
			findNum = 0;
			mi = m_CliqueArray[i]->m_CliqueNodeIDs.size();
			mj = m_CliqueArray[j]->m_CliqueNodeIDs.size();
			for (int jd = 0; jd < mj; jd++)
			{
				for (iter = m_CliqueArray[i]->m_CliqueNodeIDs.begin(); iter != m_CliqueArray[i]->m_CliqueNodeIDs.end(); iter++)
				{
					if (*iter == m_CliqueArray[j]->m_CliqueNodeIDs[jd])
					{
						findNum++;
						break;
					}
				}
			}
			if ((mi != 0) && (mj != 0))
			{
				overlap = (double)(findNum*findNum) / (mi*mj);
			}
			if (findNum == mj || (overlap - tvOverlap >= 0)) {
				m_CliqueArray[j]->match = false;
			}
		}
	}
}
void  Graph::FilterClique_NodeNames(double  tvOverlap)
{
	sort(m_CliqueArray.begin(), m_CliqueArray.end(), CompCliqueSizeDecend_CliqueProteins());

	int findNum;
	int mi;
	int mj;
	double overlap;
	std::vector<string>::iterator iter;
	for (size_t i = 0; i < m_CliqueArray.size(); i++) {
		m_CliqueArray[i]->match = true;
	}
	for (int i = 0; i < (int)m_CliqueArray.size() - 1; i++) {
		if (m_CliqueArray[i]->match == false)
			continue;
		for (size_t j = i + 1; j < m_CliqueArray.size(); j++) {
			if (m_CliqueArray[j]->match == false)
				continue;
			findNum = 0;
			mi = m_CliqueArray[i]->m_CliqueNodeNames.size();
			mj = m_CliqueArray[j]->m_CliqueNodeNames.size();
			for (int jd = 0; jd < mj; jd++)
			{
				for (iter = m_CliqueArray[i]->m_CliqueNodeNames.begin(); iter != m_CliqueArray[i]->m_CliqueNodeNames.end(); iter++)
				{
					if (*iter == m_CliqueArray[j]->m_CliqueNodeNames[jd])
					{
						findNum++;
						break;
					}
				}
			}
			if ((mi != 0) && (mj != 0))
			{
				overlap = (double)(findNum*findNum) / (mi*mj);
			}
			if (findNum == mj || (overlap - tvOverlap >= 0)) {
				m_CliqueArray[j]->match = false;
			}
		}
	}
}
void Graph::outPutIntervalComplex(const string scFileName)
{
	std::ofstream OutFile;
	OutFile.open(scFileName, ios::out);
	if (!OutFile)
	{
		std::cout << "Can't create OutPut file COMPLEX!" << std::endl;
	}

	for (size_t i = 0; i < m_CliqueArray.size(); i++)
	{
		if (m_CliqueArray[i]->match == true) {
			for (size_t j = 0; j < m_CliqueArray[i]->m_CliqueNodeIDs.size(); j++)
			{
				OutFile << m_NodeArray[m_CliqueArray[i]->m_CliqueNodeIDs[j]]->m_szName << '\t';

			}
			OutFile << std::endl;
		}
	}
	if (OutFile)
		OutFile.close();
}
void Graph::outPutAllComplex(const string scFileName)
{
	std::ofstream OutFile;
	OutFile.open(scFileName, ios::out);
	if (!OutFile)
	{
		std::cout << "Can't create OutPut file COMPLEX!" << std::endl;
	}

	for (size_t i = 0; i < m_CliqueArray.size(); i++)
	{
		if (m_CliqueArray[i]->match == true) {
			for (size_t j = 0; j < m_CliqueArray[i]->m_CliqueNodeNames.size(); j++)
			{
				OutFile << m_CliqueArray[i]->m_CliqueNodeNames[j] << '\t';

			}
			OutFile << std::endl;
		}
	}
	if (OutFile)
		OutFile.close();
}

void Graph::outPutAllComplexLog(const string scFileName)
{
	std::ofstream OutFile;
	OutFile.open(scFileName, ios::out);
	if (!OutFile)
	{
		std::cout << "Can't create OutPutLOG file!" << std::endl;
	}

	for (size_t i = 0; i < m_CliqueArray.size(); i++)
	{
		if (m_CliqueArray[i]->match == true) {
			OutFile << m_CliqueArray[i]->sliceID << " ";
			for (size_t c = 0;c < m_CliqueArray[i]->m_CoreNodes.size();c++)
				OutFile << m_CliqueArray[i]->m_CoreNodes[c] << " ";
			OutFile << "| ";
			for (size_t a = 0;a < m_CliqueArray[i]->m_AttachNodes.size();a++)
				OutFile << m_CliqueArray[i]->m_AttachNodes[a] << " ";
			OutFile << endl;
		}
	}
	if (OutFile)
		OutFile.close();
}

double Graph::getWeightOfNode2Clique(const Node* node, Clique *clique, int interval, double alpha) {
	//团内的所有节点对另一个节点node的权值所做的贡献值,ecc之和加suvtime
	if (node->m_iDegree <= 1)
	{
		return 0;
	}
	double ecc = 0;
	Clique *neighborInClique = new Clique();
	Arc *arc = node->m_pFirst;
	while (arc&&IsIncludedInClique(arc->m_iNodeTo, clique)) {
		neighborInClique->m_CliqueNodeIDs.push_back(arc->m_iNodeTo);
		ecc += arc->m_fWeight;
		arc = arc->m_pNextArc;
	}
	double neighborNum = neighborInClique->m_CliqueNodeIDs.size();
	if (neighborNum == 0) {
		delete neighborInClique;
		return 0;
	}
	delete neighborInClique;
	return ecc*alpha + (1 - alpha)*node->suvivalTime[interval];
}
double Graph::getAveNodeWeight(Clique *clique, int interval, double alpha) {
	if (clique->m_CliqueNodeIDs.size() == 0)
		return 0;
	double aveweight = 0;
	double nodeWeight = 0;
	for (size_t inode = 0; inode < clique->m_CliqueNodeIDs.size(); inode++)
	{
		nodeWeight = getWeightOfNode2Clique(m_NodeArray[clique->m_CliqueNodeIDs[inode]], clique, interval, alpha);
		aveweight += nodeWeight;
	}
	return aveweight / clique->m_CliqueNodeIDs.size();

}
int Graph::FindNodeWithMinWeightInClique(Clique *clique, int interval, double alpha)
{
	double min = 100;
	int index = -1;
	double nodeWeight = 0;
	for (size_t nodeIndex = 0; nodeIndex < clique->m_CliqueNodeIDs.size(); nodeIndex++) {
		nodeWeight = getWeightOfNode2Clique(m_NodeArray[clique->m_CliqueNodeIDs[nodeIndex]], clique, interval, alpha);
		if (nodeWeight < min)
		{
			min = nodeWeight;
			index = clique->m_CliqueNodeIDs[nodeIndex];
		}
	}
	return index;
}

void Graph::getWeight(int interval, double alpha, double beta) {
	for (size_t i = 0; i < m_NodeArray.size(); i++) {
		Node *nodex = m_NodeArray[i];
		nodex->weight = nodex->ECC*alpha + nodex->suvivalTime[interval] * beta;
		//	cout << nodex->weight<<"	";
	}
}

void Graph::getCliques(int interval, double seedtv, double cliqueAveWtv, double outTV, double alpha) {
	int cliqueNo = 0;
	for (size_t nodeIndex = 0; nodeIndex < m_NodeArray.size(); nodeIndex++)
	{
		if (m_NodeArray[nodeIndex]->weight > seedtv) {
			Clique* clique = new Clique(cliqueNo++, interval + 1);
			clique->m_CliqueNodeIDs.push_back(nodeIndex); //种子节点加入
			Arc* arc = m_NodeArray[nodeIndex]->m_pFirst;
			while (arc)
			{	//种子的邻居都加入
				clique->m_CliqueNodeIDs.push_back(arc->m_iNodeTo);
				arc = arc->m_pNextArc;
			}

			while (getAveNodeWeight(clique, interval, alpha) < cliqueAveWtv) {
				if (clique->m_CliqueNodeIDs.size() <= 2)
				{
					clique->match = false;
					break;
				}
				int inode = FindNodeWithMinWeightInClique(clique, interval, alpha);
				if (find(clique->m_CliqueNodeIDs.begin(), clique->m_CliqueNodeIDs.end(), inode) == clique->m_CliqueNodeIDs.end())
				{
					break;
				}
				clique->m_CliqueNodeIDs.erase(find(clique->m_CliqueNodeIDs.begin(), clique->m_CliqueNodeIDs.end(), inode));
			}

			if (!clique->match)
			{
				delete clique;
				continue;
			}

			for (size_t j = 0; j < clique->m_CliqueNodeIDs.size(); j++) {
				char* protein = m_NodeArray[clique->m_CliqueNodeIDs[j]]->m_szName;
				clique->m_CoreNodes.push_back(protein);
			}

			//团外重要节点
			std::vector<int> ExtendNodes;
			for (size_t j = 0; j < clique->m_CliqueNodeIDs.size(); j++)
			{
				Arc* pArc = m_NodeArray[clique->m_CliqueNodeIDs[j]]->m_pFirst;
				while (pArc != NULL)
				{
					std::vector<int>::iterator begin = ExtendNodes.begin();
					std::vector<int>::iterator end = ExtendNodes.end();
					std::vector<int>::iterator result = find(begin, end, pArc->m_iNodeTo);

					if (!IsIncludedInClique(pArc->m_iNodeTo, clique) && result == ExtendNodes.end())
					{
						ExtendNodes.push_back(pArc->m_iNodeTo);
					}
					pArc = pArc->m_pNextArc;
				}
			}
			for (size_t m = 0; m < ExtendNodes.size(); m++)
			{
				if (getWeightOfNode2Clique(m_NodeArray[ExtendNodes[m]], clique, interval, alpha) - m_NodeArray[ExtendNodes[m]]->suvivalTime[interval]  > outTV)
				{
					clique->m_CliqueNodeIDs.push_back(ExtendNodes[m]);
					char* protein = m_NodeArray[ExtendNodes[m]]->m_szName;
					clique->m_AttachNodes.push_back(protein);
				}
			}
			m_CliqueArray.push_back(clique);
		}
	}
}


