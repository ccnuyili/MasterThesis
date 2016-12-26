
class Graph          //���ڽ��б��ʾ��ͼ�ṹ;
{
public:
	std::vector<Node*>	 m_NodeArray;             //�ڵ�����;
	int					 m_nNumEdges;
	std::vector<Clique> m_ComplexArray;	//��ѡ�����Ӽ���;
	std::vector<Clique> m_allComplexArray;	//12��ʱ���ȫ����
public:
	Graph(){	
	}
	Graph(GraphLoader&	rawGraph)
	{
		LoadGraphFromRawGraph(rawGraph);
	}
	void Graph::loadGraph(const char* szFileName,const char* scFileName,const char* allcomFileName, double inf, double outf,bool mark);   //�����ʼ��ͼ��Ϣ;
	void Graph::LoadGraphFromRawGraph(GraphLoader	rawGraph);//���ݳ�ʼ�����ԭʼͼ��Ϣ����ȡͼ�ṹ���ܵ���˵�Ǹ��ݱ��𽥹���ͼ;
	void  Graph::GetSeeds();//�ҵ����ӽڵ�;
	void Graph::GetFirstExtension(double inf);//��һ����չ;
	void Graph::GetSecondExtension(double outf);//�ڶ�����չ;
	void  Graph::FilterClique();//�����ص���Ľڵ㼯��;     
	void Graph::getComplex();
	void  Graph::allFilterClique();
	void  Graph::outPutallComplex(const char* scFileName);
};


void Graph::loadGraph(const char* szFileName,const char* scFileName,const char* allcomFileName,double inf, double outf,bool mark){ 
	GraphLoader	rawGraph(szFileName); //����һ��GraphLoader���ʵ����������һ�������Ĺ��췽������ʼ����ʵ��
	LoadGraphFromRawGraph(rawGraph);
	GetSeeds();	   
	GetFirstExtension(inf);	
	GetSecondExtension(outf);
	sort(m_ComplexArray.begin(),m_ComplexArray.end(),CompCliqueSizeDcend());
	FilterClique();//���˱������ĺ���ͬ��
	getComplex();	//ͬһ�������µĲ�ͬʱ�̵�Ԥ��ĸ������Ⱥϲ����������
	if(mark==true){
		sort(m_allComplexArray.begin(),m_allComplexArray.end(),CompCliqueSizeDcend());
		cout<<"filterallclique..."<<endl;
		allFilterClique(); //�����ص��ϴ��
		outPutallComplex(allcomFileName);
		m_allComplexArray.clear();
	}
}

//���ݳ�ʼ�����ԭʼͼ��Ϣ����ȡͼ�ṹ���ܵ���˵�Ǹ��ݱ��𽥹���ͼ;
void Graph::LoadGraphFromRawGraph(GraphLoader rawGraph)
{
	for(int i=0;i<rawGraph.m_nArcs;i++)	//��rawGraph�ж�ȡ�ߵ���Ϣ;
	{
		int j,k;
		bool bFoundFrom=false;
		bool bFoundTo=false;

		//�տ�ʼʱ�ڵ�������Ϊ�յģ��Ǹ���ԭʼͼ��Ϣ������ӽڵ��;
		for(j=0;j<m_NodeArray.size();j++)	 //�鿴�ߵ���ʼ�ڵ��Ƿ���ڣ�j�����˸ı���ʼ���λ��;
		{
			if(m_NodeArray[j]->m_szName==rawGraph.m_RawGraph[i].m_szFrom)//�Ƚ�2���ַ����Ĵ�С����;
			{
				bFoundFrom=true;
				break;
			}

		}		
		for(k=0;k<m_NodeArray.size();k++)					    //�鿴�ߵ���ֹ�ڵ��Ƿ����, k�����˸ı���ʼ���λ��;
		{
			if(m_NodeArray[k]->m_szName==rawGraph.m_RawGraph[i].m_szTo)
			{
				bFoundTo=true;
				break;
			}
		}
		
		if(bFoundFrom==false)									//��������ڣ��򴴽�һ���µĽڵ�;
		{
			Node* pNode=new Node(m_NodeArray.size(),rawGraph.m_RawGraph[i].m_szFrom);
			m_NodeArray.push_back(pNode);
			j=m_NodeArray.size()-1;												 //j��������m_NodeArray�еĸı���ʼ���λ��;
		}
		if(bFoundTo==false)											//��������ڣ��򴴽�һ���µĽڵ�;
		{
			Node* pNode=new Node(m_NodeArray.size(),rawGraph.m_RawGraph[i].m_szTo);
			m_NodeArray.push_back(pNode);
			k=m_NodeArray.size()-1;												 //k�����˸ı���ֹ���λ��;
		}

		m_NodeArray[j]->InsertArc(rawGraph.m_RawGraph[i].m_szTo,k,rawGraph.m_RawGraph[i].m_fWeight); //�����������һ����;
		m_NodeArray[j]->m_iDegree++;
		m_NodeArray[k]->InsertArc(rawGraph.m_RawGraph[i].m_szFrom,j,rawGraph.m_RawGraph[i].m_fWeight);   //�����������һ����;
		m_NodeArray[k]->m_iDegree++;		   		
	}

	m_nNumEdges=rawGraph.m_nArcs;//��ϵ�ĸ����ȼ��ڱߵĸ���;
	std::cout<<" the total edges are:"<<m_nNumEdges<<std::endl;
	std::cout<<" the total nodes are:"<<m_NodeArray.size()<<std::endl;
	std::cout<<"Finish the txt To graph......;"<<std::endl;
}

//�˺����ǵõ��˺�ѡ�����Ӽ���;
void Graph::GetSeeds()
{
	double Ave_Degree = 0.0;
	double Ave_AF = 0.0;
	for (int i = 0; i < m_NodeArray.size(); i++)
	{
		Ave_Degree += m_NodeArray[i]->m_iDegree;
		Arc* pArc = m_NodeArray[i]->m_pFirst;
		while(pArc!=NULL){
			Ave_AF += pArc->m_fWeight;
			pArc = pArc->m_pNextArc;
		}		
	}
	Ave_Degree = Ave_Degree/m_NodeArray.size();
	Ave_AF = Ave_AF/(m_NodeArray.size());


	int iHubs=0;
	for (int i = 0; i < m_NodeArray.size(); i++)
	{	
		double TempAF = 0.0;
		Arc* pArc = m_NodeArray[i]->m_pFirst;
		while(pArc!=NULL){
			TempAF += pArc->m_fWeight;
			pArc = pArc->m_pNextArc;
		}	
		if (m_NodeArray[i]->m_iDegree >= Ave_Degree  || TempAF >= Ave_AF)
		{
			Clique pClique(iHubs);
			++iHubs;
			pClique.m_CliqueNodes.push_back(m_NodeArray[i]);
			m_ComplexArray.push_back(pClique);
		}	
	}
}


//�˺����ǵõ������ӽ��е�һ����չ�����ں���չ;
void Graph::GetFirstExtension(double inf)
{

	for (int i = 0;i<m_ComplexArray.size();i++)
	{
		Arc* pArc = m_ComplexArray[i].m_CliqueNodes[0]->m_pFirst;//��Ϊ��ʼ������ֻ��һ���ڵ㣬���Կ��Զ�λ��������0;
		while(pArc!=NULL){
			m_ComplexArray[i].m_CliqueNodes.push_back(m_NodeArray[pArc->m_iNodeTo]);
			pArc = pArc->m_pNextArc;		
		}
	}

	for (int i=0;i<m_ComplexArray.size();i++)
	{
		double TotalWeight = getNodesetWeights(m_ComplexArray[i]);
		double AveWeight = 2*TotalWeight/(m_ComplexArray[i].m_CliqueNodes.size()*(m_ComplexArray[i].m_CliqueNodes.size()-1));
		while (AveWeight < inf && m_ComplexArray[i].m_CliqueNodes.size()>2)
		{
			int m = FindMinVectorWeigthNode(m_ComplexArray[i]);		  //�ڵ�Ȩ����С��AF��

			std::vector<Node*>::iterator begin = m_ComplexArray[i].m_CliqueNodes.begin();
			std::vector<Node*>::iterator end = m_ComplexArray[i].m_CliqueNodes.end();
			m_ComplexArray[i].m_CliqueNodes.erase(find(begin,end,m_ComplexArray[i].m_CliqueNodes[m]));

			TotalWeight = getNodesetWeights(m_ComplexArray[i]);
			AveWeight = 2*TotalWeight/(m_ComplexArray[i].m_CliqueNodes.size()*(m_ComplexArray[i].m_CliqueNodes.size()-1));
		}
	}
}

//�˺����ǵõ������ӽ��еڶ�����չ���������չ;
void Graph::GetSecondExtension( double outf)
{
	for (int i=0;i<m_ComplexArray.size();i++)
	{
		std::vector<Node*> FromNodes;//�Ѿ��ҵ���Ҫ��չ���ŵĽڵ㣬�����ظ�
		for (int j = 0; j<m_ComplexArray[i].m_CliqueNodes.size(); j++)
		{
			Arc* pArc = m_ComplexArray[i].m_CliqueNodes[j]->m_pFirst;
			while(pArc!=NULL)
			{
				std::vector<Node*>::iterator begin = FromNodes.begin();
				std::vector<Node*>::iterator end = FromNodes.end();
				std::vector<Node*>::iterator result = find(begin,end,m_NodeArray[pArc->m_iNodeTo]);

				if (!IsIncludedInClique(m_NodeArray[pArc->m_iNodeTo], m_ComplexArray[i]) && result == FromNodes.end())
				{
					double getAdjEdgesWeight = getAdjEdges(m_NodeArray[pArc->m_iNodeTo], m_ComplexArray[i]);
					if ((getAdjEdgesWeight/m_ComplexArray[i].m_CliqueNodes.size()) > (outf))
					{
						FromNodes.push_back( m_NodeArray[pArc->m_iNodeTo]);
					}
					//break;
				}
				pArc = pArc->m_pNextArc;		
			}		
		}
		for (int m=0;m<FromNodes.size();m++)
		{
			m_ComplexArray[i].m_CliqueNodes.push_back(FromNodes[m]);
		}
	}

}

void  Graph::FilterClique()
{ //�Ѿ����������С�������У�������ǰ����ȣ����Ǻ���Ҫ��Ҫɾ
	int findNum;
	int mi;
	int mj;
	double overlap;
	std::vector<Node*>::iterator iter;
	for (int i=0;i<m_ComplexArray.size();i++){
		m_ComplexArray[i].mark=true;
	}
	for(int i=0;i<m_ComplexArray.size()-1;i++){
		if(m_ComplexArray[i].mark==false)continue;
		for(int j=i+1;j<m_ComplexArray.size();j++){
			if(m_ComplexArray[j].mark==false)continue;
			findNum=0;
			mi=m_ComplexArray[i].m_CliqueNodes.size();
			mj=m_ComplexArray[j].m_CliqueNodes.size();
			for(int jd=0;jd<mj;jd++)
			{
				for(iter=m_ComplexArray[i].m_CliqueNodes.begin();iter!=m_ComplexArray[i].m_CliqueNodes.end();iter++)
				{	//���ҵ�
					if((*iter)->m_szName==m_ComplexArray[j].m_CliqueNodes[jd]->m_szName)
					{
						findNum++;
						break;
					}
				}
			}
			if ((mi!=0) && (mj!=0))
			{
				overlap = (double) (findNum*findNum)/(mi*mj);
			}
			if (findNum == mj||(overlap-1>=0)){
				m_ComplexArray[j].mark=false;
			}
		}
	}
}

void  Graph::getComplex()
{
	for (int i=0;i<m_ComplexArray.size();i++)
	{ 
		if(m_ComplexArray[i].mark==true)
		{
			m_allComplexArray.push_back(m_ComplexArray[i]);
		}
	}
}

void  Graph::allFilterClique()
{ //�Ѿ����������С�������У�������ǰ����ȣ����Ǻ���Ҫ��Ҫɾ
	int findNum;
	int mi;
	int mj;
	double overlap;
	std::vector<Node*>::iterator iter;
	for(int i=0;i<m_allComplexArray.size()-1;i++){
		m_allComplexArray[i].mark=true;
	}
	for(int i=0;i<m_allComplexArray.size()-1;i++){
		if(m_allComplexArray[i].mark==false)continue;
		for(int j=i+1;j<m_allComplexArray.size();j++){
			if(m_allComplexArray[j].mark==false)continue;
			findNum=0;
			mi=m_allComplexArray[i].m_CliqueNodes.size();
			mj=m_allComplexArray[j].m_CliqueNodes.size();
			for(int jd=0;jd<mj;jd++)
			{
				for(iter=m_allComplexArray[i].m_CliqueNodes.begin();iter!=m_allComplexArray[i].m_CliqueNodes.end();iter++)
				{	//���ҵ�
					if((*iter)->m_szName==m_allComplexArray[j].m_CliqueNodes[jd]->m_szName)
					{
						findNum++;
						break;
					}
				}
			}
			if ((mi!=0) && (mj!=0))
			{
				overlap = (double) (findNum*findNum)/(mi*mj);
			}
			if (findNum == mj||(overlap-tvOverlap>=0)){

				m_allComplexArray[j].mark=false;
			}
		}
	}
}

void  Graph::outPutallComplex(const char* scFileName)
{//�����ʽ��
	//	node1  node2  ...
	//	node1  node2  ...
	//		...
	std::ofstream OutFile;
	OutFile.open(scFileName);
	if (!OutFile)
	{
		std::cout<<"Can't create OutPut file COMPLEX!"<<std::endl;
	}

	for (int i=0;i<m_allComplexArray.size();i++)
	{  
		if(m_allComplexArray[i].mark==true){
			for (int j=0;j<m_allComplexArray[i].m_CliqueNodes.size();j++)
			{ 
				OutFile<<m_allComplexArray[i].m_CliqueNodes[j]->m_szName<<"  ";

			}
			OutFile<<std::endl;
		}
	}
	if(OutFile)
		OutFile.close();
}
