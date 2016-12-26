#include<cstring>
#include<string>
using namespace::std;

void getEdges(char fileName[100], const Clique &clique,GraphLoader rawgraph){
	std::ofstream outFile;
	outFile.open(fileName);
	if(!outFile){
		cout<<"can not open the edges file "<<fileName<<endl;
		return;
	}
	bool isIncludeInComplex(string nodeA,string nodeB, const Clique &clique);	
	string proteinA;
	string proteinB;	
	for(size_t i=0;i<rawgraph.m_RawGraph.size();i++)
	{	
	
		proteinA=rawgraph.m_RawGraph[i].m_szFrom;
		proteinB=rawgraph.m_RawGraph[i].m_szTo;
		double w=rawgraph.m_RawGraph[i].m_fWeight;
		
		if(isIncludeInComplex(proteinA,proteinB,clique)){
			outFile<<proteinA<<'\t'<<proteinB<<'\t'<<w<<endl;
		}				
	}
	if(outFile)
		outFile.close();
}

bool isIncludeInComplex(string nodeA,string nodeB,const Clique &clique){
	/*判断2个节点是否包含在一个clique中*/
	bool marka=false;
	bool markb=false;
	set<Node*>::iterator iter =clique.m_CliqueNodes.begin();
	set<Node*>::iterator end =clique.m_CliqueNodes.end();
	for(;iter!=end;iter++){
		if(nodeA==(*iter)->gName){
			marka=true;			
		}
		if(nodeB==(*iter)->gName){
			markb=true;			
		}
		if(marka&markb)break;
	}
	return marka&markb;
}

