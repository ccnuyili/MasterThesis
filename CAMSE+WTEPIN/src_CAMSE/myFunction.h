
bool IsIncludedInClique(Node* node, Clique clique)//�ж�һ���ڵ��Ƿ�����һ���ţ�����ʱ����true��������ʱ����false;
{
	bool Ismark = false;
	for (int i=0;i<clique.m_CliqueNodes.size();i++)
	{
		if(node->m_iNode == clique.m_CliqueNodes[i]->m_iNode)
		{
			Ismark =true;
		}
	}
	return Ismark;
}

//��ȡ�������бߵ�Ȩ��֮�ͣ����еı�ֻ�ܰ��������ڣ�;
double getNodesetWeights(Clique clique)
{
	double nodeweight=0.0;
	for (int i=0;i<clique.m_CliqueNodes.size();i++)
	{
		Arc* pArc = clique.m_CliqueNodes[i]->m_pFirst;
		while (pArc != NULL)
		{
			for (int j=0;j<clique.m_CliqueNodes.size();j++)
			{
				if (pArc->m_iNodeTo == clique.m_CliqueNodes[j]->m_iNode)
				{
					nodeweight += pArc->m_fWeight;
				}
			}
			pArc =pArc->m_pNextArc;
		}
	}
	nodeweight = nodeweight/2.0;
	return nodeweight;
}

int GetCliqueEdges(Clique clique)//��ȡһ�����ڵ��ܵı���;
{
	int EdgesInClique = 0;
	for (int i=0;i<clique.m_CliqueNodes.size();i++)
	{
		Arc* pArc = clique.m_CliqueNodes[i]->m_pFirst;
		while (pArc != NULL)
		{
			for (int j=0;j<clique.m_CliqueNodes.size();j++)
			{
				if (pArc->m_iNodeTo == clique.m_CliqueNodes[j]->m_iNode)
				{
					EdgesInClique++;
				}
			}
			pArc = pArc->m_pNextArc;
		}

	}
	return (EdgesInClique/2);
}

int FindMinVectorWeigthNode(Clique clique)
{	//�ҵ�һ�����ڽڵ�Ȩ����С���Ǹ����������������еĽڵ����;
	double min = 100;
	int marknode = 0;
	int vectormarknode = 0;
	for (int i=0;i<clique.m_CliqueNodes.size();i++)
	{	
		//std::cout<<"****   ****    ****"<<std::endl;
		double nodeWeight = 0.0;
		Arc* pArc = clique.m_CliqueNodes[i]->m_pFirst;
		while (pArc != NULL)
		{
			for (int j=0;j<clique.m_CliqueNodes.size();j++)
			{
				if (pArc->m_iNodeTo == clique.m_CliqueNodes[j]->m_iNode)
				{
					nodeWeight += pArc->m_fWeight;
				}
			}
			pArc = pArc->m_pNextArc;
		}
		if(nodeWeight < min)
		{
			vectormarknode = i;
			min = nodeWeight;
			marknode = clique.m_CliqueNodes[i]->m_iNode;
		}
	}
	return vectormarknode;
}

double getAdjEdges(Node* mNode,Clique mClique)//��ȡmNode����mClique ֮���Ȩ�غ�;
{
	Arc* pArc = mNode->m_pFirst;
	double weightAdjEdge = 0.0;

	while (pArc!=NULL)
	{
		for (int i=0;i<mClique.m_CliqueNodes.size();i++)
		{
			if(pArc->m_iNodeTo == mClique.m_CliqueNodes[i]->m_iNode)
			{
				weightAdjEdge += pArc->m_fWeight;
			}
		}
		pArc = pArc->m_pNextArc;
	}
	return weightAdjEdge;

}


