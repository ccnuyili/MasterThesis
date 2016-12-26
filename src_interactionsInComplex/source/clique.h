#include <set>
#include<cstring>
using namespace::std;
class Node
{
public:
	string	gName;//节点名称;
	bool	m_bMarked;//节点标志;
	int		m_iNode;//节点编号;
public:
	Node()
	{	m_iNode=0;
		gName="";		
	}	
	Node(int iNode,string szName)
	{
		gName=szName;
		m_iNode=iNode;
		m_bMarked=false;
	}

	void setNodeName(string s)
	{
		gName=s;		
	}
};

class Clique//团类;
{
public:
	std::set<Node*>	m_CliqueNodes;//团的节点向量;
	bool	mark ;
	string	m_CliqueNodesID;  //团编号
	int		NumEdges;
public:
	Clique(){
		NumEdges=0;
	}
	Clique(string CliqueNodesID)
	{
		m_CliqueNodesID = CliqueNodesID;
		NumEdges=0;
		mark = false;
	}
};

void readComplexfile(Clique &clique,const char complexfile[100]){
	std::ifstream inFile;
	inFile.open(complexfile);
	if(!inFile){
		cout<<"can not open the complexes file "<<complexfile<<endl;
		return;
	}
	const string strDelims="\t \n|";
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
		while(iter != splitStrs.end()) {  
			s=(*iter);
			Node *node=new Node();
			node->setNodeName(s);
			clique.m_CliqueNodes.insert(node);
			++iter;
		}
		i=0;
		c='\0';
	}
	if(inFile)
		inFile.close();
}

int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)  
{	/*分割字符串strSrc,分隔符为strDelims中的各个字符，分割出来的各个分量存在strDest*/
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