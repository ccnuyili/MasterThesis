void readPCTfile(NodeMatrix &complex,char PCTfile[100]){
	std::ifstream inFile;
	inFile.open(PCTfile);
	if(!inFile){
		cout<<"can not open the file "<<PCTfile<<endl;
		return;
	}
	const string strDelims="\t \n";
	vector<string> splitStrs;
	vector<string>::iterator iter; 
	char str[10000];
	char c='\0';
	int i=0;
	inFile>>noskipws;  
	string cliqueId;
	int proteinNum=0;
	char enter;
	while(!inFile.eof())  {		
		while(!inFile.eof() && c!='\n')
		{
			inFile>>c;
			str[i++]=c;
		}
		str[i]='\0';
		splitStrs.clear();
		int splitString(string &strSrc, const string &strDelims, vector<string>& strDest);
		string s(&str[0],&str[strlen(str)]);  
		splitString(s,strDelims,splitStrs);
		iter = splitStrs.begin(); 
		//		cliqueId=*iter;
		Clique* pClique = new Clique();
		//		++iter;
		while(iter != splitStrs.end()) {  
			s=(*iter);
			Node *node=new Node();
			node->setNodeName(s);
			pClique->m_CliqueNodes.push_back(node);
			++iter;
		}
		pClique->proteinNum=pClique->m_CliqueNodes.size();
		complex.CliqueVec.push_back(pClique);
		i=0;
		c='\0';
	}
	if(inFile)
		inFile.close();
	complex.cliqueNum=complex.CliqueVec.size();
}
void rebuildWeight(ExpressionSet expData,char fileName[],NodeMatrix complex,GraphLoader rawgraph,Graph graph){
	std::ofstream outFile;
	outFile.open(fileName);
	if(!outFile){
		cout<<"can not open the file "<<fileName<<endl;
		return;
	}
	bool isIncludeInComplex(string nodeA,string nodeB,Clique *acomplex);
	int GetCliqueEdges(Graph graph,Clique* clique);
	string proteinA;
	string proteinB;
	double weight=1.0;
	double nk=0;
	double rk=0;
	double cac=0;
	for(size_t i=0;i<rawgraph.m_RawGraph.size();i++)
	{	
		weight=0;
		nk=0;rk=0;
		cac=0;
		proteinA=rawgraph.m_RawGraph[i].m_szFrom;
		proteinB=rawgraph.m_RawGraph[i].m_szTo;
		for(int k=0;k<complex.CliqueVec.size();k++)
		{
			if(isIncludeInComplex(proteinA,proteinB,complex.CliqueVec[k])){
				nk=complex.CliqueVec[k]->m_CliqueNodes.size();
				rk=complex.CliqueVec[k]->NumEdges;
				if(rk==0)
				{	
					rk=GetCliqueEdges(graph,complex.CliqueVec[k]);
					complex.CliqueVec[k]->NumEdges=rk;
				}
				if(rk>0&&nk>0)
					cac+=(nk/rk);		
			}
		}
		double GetPCC(ExpressionSet expData,string proteinA,string proteinB);	
		weight=(cac+GetPCC(expData,proteinA,proteinB));	
		if(weight>0)		
			outFile<<proteinA<<'\t'<<proteinB<<'\t'<<weight<<endl;	
	}
	if(outFile)
		outFile.close();
}
double GetPCC(ExpressionSet expData,string proteinA,string proteinB){
	//��һ���໥���õĵ������ڻ����������е�PCC
	double pcc=0; //���ڱ��������û�ҵ��õ�����
	int pa=-1,pb=-1;
	bool ma=false,mb=false;
	double avea=0,aveb=0;
	for(size_t i=0;i<expData.ExpVex.size();i++){
		if(expData.ExpVex[i].protein==proteinA)
		{
			pa=i;ma=true;}
		if(expData.ExpVex[i].protein==proteinB)
		{
			pb=i;mb=true;}
		if(ma&&mb)break;	
	}
	if(pa!=-1&&pb!=-1){
		for(int i=0;i<36;i++)
		{	
			avea+=expData.ExpVex[pa].expValue[i];
			aveb+=expData.ExpVex[pb].expValue[i];		
		}
		avea/=36;aveb/=36;
		double up=0,down1=0,down2=0;
		for(int i=0;i<36;i++){
			up+=((expData.ExpVex[pa].expValue[i]-avea)*(expData.ExpVex[pb].expValue[i]-aveb));
			down1+=((expData.ExpVex[pa].expValue[i]-avea)*(expData.ExpVex[pa].expValue[i]-avea));
			down2+=((expData.ExpVex[pb].expValue[i]-aveb)*(expData.ExpVex[pb].expValue[i]-aveb));		
		}
		down1=sqrt(down1);
		down2=sqrt(down2);
		pcc=up/(down1*down2);	
	}
	return pcc;
}




/*
void GetECC(Graph &graph){	   
	//����ͼ�е�ÿһ���ߣ�����ECC,�ٽ����PCC,�ñߵ�Ȩ��weight=ecc*r+pcc*(1-r) .
	int mNum=0;
	double ecc=0;
	int dx=0,dy=0,mind;
	double pcc=0;
	for(size_t i=0;i<graph.m_NodeArray.size();i++){
		//���ڽڵ�x
		Node *nodex=&graph.m_NodeArray[i];
		dx=nodex->m_iDegree;
		Arc *arcxy=nodex->m_pFirst;		
		while(arcxy!=NULL){//����X�������ھӽڵ�Y��
			Node *nodey=&graph.m_NodeArray[arcxy->m_iNodeTo];//��x�����Ľڵ�y
			dy=nodey->m_iDegree;
			Arc *arcxm=graph.m_NodeArray[i].m_pFirst;//��x�����Ľڵ�m
			for(;arcxm!=NULL;arcxm=arcxm->m_pNextArc){//����X�������ھӣ�����Y�⣩M��
				if(arcxm!=arcxy){
					Node *nodem=&graph.m_NodeArray[arcxm->m_iNodeTo];				
					Arc *arcmy=nodem->m_pFirst;
					while(arcmy!=NULL){//������M�����Ľڵ㣬����Y��M������
						if(arcmy->m_iNodeTo==nodey->m_iNode)
						{	mNum++;
						break;
						}
						arcmy=arcmy->m_pNextArc;
					}
				}				
			}
			mind=(dx<dy?dx:dy);			
			arcxy->m_ecc=(double)mNum/mind;	

			arcxy=arcxy->m_pNextArc;
			mNum=0;
		}
	}
}			 
double GetECCab(Graph graph,string proteinA,string proteinB){	   
	int pa=-1,pb=-1;
	for(size_t i=0;i<graph.m_NodeArray.size();i++){
		if(graph.m_NodeArray[i].gName==proteinA)
			pa=i;
		if(graph.m_NodeArray[i].gName==proteinB)
			pb=i;
		if(pa>-1&&pb>-1)break;
	}
	Arc *arcm=graph.m_NodeArray[pa].m_pFirst;
	while(arcm!=NULL){//������M�����Ľڵ㣬����Y��M������
		if(arcm->m_iNodeTo==pb)
		{	return arcm->m_ecc;
		break;
		}
		arcm=arcm->m_pNextArc;
	}
	return 0;
}
*/

int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)  
{	/*�ָ��ַ���strSrc,�ָ���ΪstrDelims�еĸ����ַ����ָ�����ĸ�����������strDest*/
	typedef string::size_type ST;  
	string delims = strDelims;  
	std::string STR;  
	if(delims.empty())
		delims = "|";  
	ST pos=0, LEN = strSrc.size();  
	while(pos < LEN ){  
		STR="";   
		while((pos < LEN) && (delims.find(strSrc[pos]) != std::string::npos)) 
			++pos;  
		if(pos==LEN) 
			return strDest.size();  
		while( (pos < LEN)&&(delims.find(strSrc[pos]) == std::string::npos)) 
			STR += strSrc[pos++];  
		if( ! STR.empty() ) 
			strDest.push_back(STR);  
	}  
	return strDest.size();  
}  


/*���������ݶ�ppi�еĽڵ�ĸ�����*/
/*
double coverRate(Graph graph,ExpressionSet expSet){
double cov=0;
for(int i=0;i<graph.m_NodeArray.size();i++){
for(int j=0;j<expSet.expNum;j++){
if(expSet.ExpVex[j].protein==graph.m_NodeArray[i].gName)
{	cov++;
	break;
}	
}	
}	
return cov/graph.m_NodeArray.size();
}
*/
bool isIncludeInComplex(Node nodeB,Clique *clique){
	/*�ж�1���ڵ��Ƿ������һ����������*/

	for(int k=0;k<clique->m_CliqueNodes.size();k++){
		if(nodeB.gName==clique->m_CliqueNodes[k]->gName){
			return true;
			break;
		}
	}

}

bool isIncludeInComplex(string nodeA,string nodeB,Clique *clique){
	/*�ж�2���ڵ��Ƿ������һ����������*/
	bool marka=false;
	bool markb=false;
	for(int k=0;k<clique->m_CliqueNodes.size();k++){
		if(nodeA==clique->m_CliqueNodes[k]->gName){
			marka=true;			
		}
		if(nodeB==clique->m_CliqueNodes[k]->gName){
			markb=true;			
		}
		if(marka&markb)break;
	}

	return marka&markb;
}

int GetCliqueEdges(Graph graph,Clique* clique)//��ȡһ�����ڵ��ܵı���;

{	int EdgesInClique = 0;
Node *node;
Node node2;
bool isIncludeInComplex(Node nodeA,Clique* clique);
for (int i=0;i<clique->m_CliqueNodes.size();i++)
{	node=clique->m_CliqueNodes[i];

for (int k=0;k<graph.m_NodeArray.size();k++){
	if(graph.m_NodeArray[k].gName==node->gName){
		Arc* pArc = graph.m_NodeArray[k].m_pFirst;
		while (pArc != NULL)
		{
			for (int j=0;j<graph.m_NodeArray.size();j++)
			{	node2=graph.m_NodeArray[j];
			if (pArc->m_iNodeTo==graph.m_NodeArray[j].m_iNode&&isIncludeInComplex(node2,clique))
			{
				EdgesInClique++;
			}
			}
			pArc = pArc->m_pNextArc;
		}
	}
}
}
return (EdgesInClique/2);
}

void LoadGraphFromRawGraph(Graph &graph,GraphLoader rawGraph)
{
	for(int i=0;i<rawGraph.m_nArcs;i++)	//��rawGraph�ж�ȡ�ߵ���Ϣ;
	{
		int j,k;
		bool bFoundFrom=false;
		bool bFoundTo=false;

		//�տ�ʼʱ�ڵ�������Ϊ�յģ��Ǹ���ԭʼͼ��Ϣ������ӽڵ��;
		for(j=0;j<graph.m_NodeArray.size();j++)	 //�鿴�ߵ���ʼ�ڵ��Ƿ���ڣ�j�����˸ı���ʼ���λ��;
		{
			if(graph.m_NodeArray[j].gName==rawGraph.m_RawGraph[i].m_szFrom)//�Ƚ�2���ַ����Ĵ�С����;
			{
				bFoundFrom=true;
				break;
			}			
		}		
		for(k=0;k<graph.m_NodeArray.size();k++)					    //�鿴�ߵ���ֹ�ڵ��Ƿ����, k�����˸ı���ʼ���λ��;
		{
			if(graph.m_NodeArray[k].gName==rawGraph.m_RawGraph[i].m_szTo)
			{
				bFoundTo=true;
				break;
			}
		}
		if(bFoundFrom==false)									//��������ڣ��򴴽�һ���µĽڵ�;
		{	Node pNode(graph.m_NodeArray.size(),rawGraph.m_RawGraph[i].m_szFrom);
		graph.m_NodeArray.push_back(pNode);
		j=graph.m_NodeArray.size()-1;												 //j��������m_NodeArray�еĸı���ʼ���λ��;
		}
		if(bFoundTo==false)											//��������ڣ��򴴽�һ���µĽڵ�;
		{	Node pNode(graph.m_NodeArray.size(),rawGraph.m_RawGraph[i].m_szTo);
		graph.m_NodeArray.push_back(pNode);
		k=graph.m_NodeArray.size()-1;												 //k�����˸ı���ֹ���λ��;
		}
		graph.m_NodeArray[j].InsertArc(rawGraph.m_RawGraph[i].m_szTo,k,1.0); //�����������һ����;
		graph.m_NodeArray[j].m_iDegree++;
		graph.m_NodeArray[k].InsertArc(rawGraph.m_RawGraph[i].m_szFrom,j,1.0);   //�����������һ����;
		graph.m_NodeArray[k].m_iDegree++;		   		
	}
	graph.m_nNumEdges=rawGraph.m_nArcs;//��ϵ�ĸ����ȼ��ڱߵĸ���;
}
