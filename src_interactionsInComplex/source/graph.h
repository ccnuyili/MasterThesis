#include<cstring>
#include <vector>
#include<algorithm>

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
	GraphArc(char szFrom[100],char  szTo[100],double fWeight,bool Arcmark)
	{
		m_szFrom=szFrom;
		m_szTo=szTo;
		m_fWeight = fWeight;
		arcMark = Arcmark;
	}
	bool operator<(const GraphArc &arc) const {
		GraphArc arc1;
		if(m_szFrom>m_szTo)
		{
			arc1.m_szFrom=m_szTo;
			arc1.m_szTo=m_szFrom;			
		}
		else{
			arc1.m_szFrom=m_szFrom;
			arc1.m_szTo=m_szTo;			
		}
		
		GraphArc arc2;
		if(arc.m_szFrom>arc.m_szTo)
		{
			arc2.m_szFrom=arc.m_szTo;
			arc2.m_szTo=arc.m_szFrom;			
		}
		else{
			arc2.m_szFrom=arc.m_szFrom;
			arc2.m_szTo=arc.m_szTo;			
		}		
		if(arc1.m_szFrom<arc2.m_szFrom)
			return true;
		else if  (arc1.m_szFrom==arc2.m_szFrom){
			if  (arc1.m_szTo<arc2.m_szTo)
				return true;
			else 
				return false;
		}
		else 
			return false;
}
};

class GraphLoader
{
public:
	std::vector<GraphArc>  m_RawGraph;//初始的边的数据保存在这里;
	int m_nArcs;
public:
	GraphLoader()
	{	m_nArcs = 0;
	}
	GraphLoader(char szFileName[100])
	{
		LoadGraphFromFile(szFileName);
	}
	void LoadGraphFromFile(char szFileName[100])
	{
		m_RawGraph.clear();
		std::ifstream InFile(szFileName);	
		if (!InFile)
		{
			std::cout<<"can not open the file ppi file!"<<std::endl;
			return;
		}
		GraphArc arc;
		int i=0;
		while(!InFile.eof())  {
			InFile>>arc.m_szFrom>>arc.m_szTo;
			m_RawGraph.push_back(arc); //在后面插入
		}
	if(m_RawGraph.size()==0)
		return;
	std::vector<GraphArc>::iterator it;
	sort(m_RawGraph.begin(),m_RawGraph.end());
	
	std::ofstream outFile;
	outFile.open("filtered_ppi.txt");
	if(!outFile){
		cout<<"can not open the filtered_ppi file "<<endl;
		return;
	}	
	string current_proteinA;
	string current_proteinB;	
	double w;
	current_proteinA=m_RawGraph[0].m_szFrom;
	current_proteinB=m_RawGraph[0].m_szTo;
	w=m_RawGraph[0].m_fWeight;
	outFile<<current_proteinA<<'\t'<<current_proteinB<<'\t'<<w<<endl;
	
	string next_proteinA,next_proteinB;
	for(size_t i=1;i<m_RawGraph.size();i++)
	{	
		next_proteinA=m_RawGraph[i].m_szFrom;
		next_proteinB=m_RawGraph[i].m_szTo;
		w=m_RawGraph[i].m_fWeight;
		if(next_proteinA==current_proteinA && next_proteinB==current_proteinB)
			continue;
		else{
			outFile<<next_proteinA<<'\t'<<next_proteinB<<'\t'<<w<<endl;		
			current_proteinA=next_proteinA;
			current_proteinB=next_proteinB;
		}
	}
	if(outFile)
		outFile.close();	
//	it=unique(m_RawGraph.begin(),m_RawGraph.end());
//	m_RawGraph.erase(it,m_RawGraph.end());
		m_nArcs = (int)m_RawGraph.size();			
		if (InFile)
			InFile.close();		
	}
};



