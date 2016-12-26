
class Arc
{
public:
	string m_iNodeToName;
	int m_iNodeTo;
	double m_fWeight;
	Arc* m_pNextArc;
public:
	Arc()
	{
		m_pNextArc = NULL;
	}
	Arc(string iNodeToName,int iNodeTo, double fWeight, Arc* pNextArc)
	{
		m_iNodeToName=iNodeToName;
		m_iNodeTo = iNodeTo;
		m_fWeight = fWeight;
		m_pNextArc = pNextArc;
	}
};

class Node
{
public:
	bool	m_bMarked;//�ڵ��־;
	int		m_iNode;//�ڵ���;
	string	m_szName;//�ڵ�����;
	int		m_iDegree;//�ڵ��;
	Arc*	m_pFirst;//��ڵ������ĵ�һ����;
	int		m_iComplex;//��ǰ����Complex;
	double AF;

public:
	Node()
	{	AF=0;
		m_iNode=0;
		m_pFirst=0;
		m_iDegree=0;
		m_szName[0]='\0';
	}
	Node(int iNode,string szName)
	{   AF=0;
		m_szName=szName;
		m_iNode=iNode;
		m_pFirst=0;
		m_iDegree=0;
		m_bMarked=false;
		m_iComplex=0;
	}
	Node(string szName)
	{  AF=0;
		m_szName=szName;

	}
	~Node()
	{
		if(m_pFirst) 
			delete m_pFirst;
	}
	void InsertArc(string m_szName,int iTo,double fWeight)
	{
		Arc* newArc=new Arc(m_szName,iTo,fWeight,m_pFirst);//����������ͷ���뷨
		m_pFirst=newArc;
	}
};

class Clique//����;
{
public:
	std::vector<Node*>	m_CliqueNodes;//�ŵĽڵ�����;
	bool  mark ;
	int m_CliqueNodesID;  //�ű��
	int NodeNum;
	double os;
public:
	Clique(){
	}
	Clique(int CliqueNodesID)
	{
		m_CliqueNodesID = CliqueNodesID;
		NodeNum=0;
		mark = true;
	}
};

class GraphArc
{
public:
	string m_szFrom;//
	string m_szTo;//
	double m_fWeight;//
	bool arcMark;
public:
	GraphArc()
	{
		m_fWeight = 1.0f;
		arcMark = false;
	}
	GraphArc(string szFrom, string szTo,double fWeight,bool Arcmark)
	{
		m_szFrom=szFrom;
		m_szTo=szTo;
		m_fWeight = fWeight;
		arcMark = Arcmark;
	}
};

class GraphLoader
{
public:
	std::vector<GraphArc>  m_RawGraph;//��ʼ�ıߵ����ݱ���������;
	int m_nArcs;//�ߵĸ�������������֮���ж�������ϵ;

public:
	GraphLoader()
	{
		m_nArcs = 0;
	}
	GraphLoader(const char* szFileName)
	{
		LoadGraphFromFile(szFileName);
	}
	void LoadGraphFromFile(const char* szFileName)
	{
		m_RawGraph.clear();
		std::ifstream InFile(szFileName);
		if (!InFile)
		{
			std::cout<<"can not open the file LOADFROMFILE!"<<std::endl;
			return;
		}
		GraphArc arc;
		int i=0;
		while(!InFile.eof())  {
//			InFile>>arc.m_szFrom>>arc.m_szTo>>arc.m_fWeight;
			InFile >> arc.m_szFrom >> arc.m_szTo;
			arc.m_fWeight = 1.0;
			m_RawGraph.push_back(arc); //�ں������
		}
		m_nArcs = (int)m_RawGraph.size();
		if (InFile)
			InFile.close();
	}
};

class CompCliqueSizeDcend  //����
{  
public:  
	bool operator ()(const  Clique& stItem1, const  Clique& stItem2)  
	{  
		return stItem1.m_CliqueNodes.size() > stItem2.m_CliqueNodes.size();  
	}  
};
