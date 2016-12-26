
void readComplexfile( ComplexSet &complexset,char file[]){
	std::ifstream inFile;
	inFile.open(file);
	if(!inFile){
		cout<<"can not open the file "<<file<<endl;
		return;
	}
	const string strDelims="\t \n";
	vector<string> splitStrs;
	vector<string>::iterator iter; 
	char str[10000];
	char c='\0';
	int i=0;
	int inode=0;
	inFile>>noskipws;  
	int cliqueId=0;
	int proteinNum=0;
	char enter;
	while(!inFile.eof())  {		
		while(!inFile.eof() && c!='\n')
		{
			inFile>>c;
			str[i++]=c;
		}
		str[i]='\0';
		Clique pClique;	
		splitStrs.clear();
		int splitString(string &strSrc, const string &strDelims, vector<string>& strDest);
		string s(&str[0],&str[strlen(str)]);  
		splitString(s,strDelims,splitStrs);
		for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter) {  
			pClique.m_CliqueNodes.push_back(*iter);
		}
		pClique.nodeNum=pClique.m_CliqueNodes.size();
		complexset.cliqueVex.push_back(pClique);
		i=0;
		c='\0';
		inode=0;
	}
	if(inFile)
		inFile.close();
	complexset.cliqueNum=complexset.cliqueVex.size();
}

double OS(Clique pc,Clique kc){
	//与已知复合物比较 匹配程度
	std::vector<string>::iterator iterk;
	std::vector<string>::iterator iterp;
	double num=0;
	double os=0;
	for(iterk=kc.m_CliqueNodes.begin();iterk!=kc.m_CliqueNodes.end();iterk++){
		for(iterp=pc.m_CliqueNodes.begin();iterp!=pc.m_CliqueNodes.end();iterp++)
		{
			if((*iterp)==(*iterk))
				num++;	
		}
	}
	os=(double)(num*num)/((double)pc.m_CliqueNodes.size()*(double)kc.m_CliqueNodes.size());
	return os;
}

int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)  
{	//分割字符串strSrc,分隔符为strDelims中的各个字符，分割出来的各个分量存在strDest
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

Clique *getTheComplexCloselyToMyComplex(Clique &complexPredit,ComplexSet &complexPC,char outFile[],int timepoint,int &count){
	double os=0;
	int record=0;
	complexPredit.os=0;
	for(int j=0;j<complexPC.cliqueVex.size();j++){
		os=OS(complexPredit,complexPC.cliqueVex[j]);
		if(os>complexPredit.os)
		{
		complexPredit.os=os;
		record=j;
		}	
	}	
	if(complexPredit.os>=0.2){	
		count++;	
		Clique commonProteins;
		std::vector<string>::iterator iterk;
		std::vector<string>::iterator iterp;
		for(iterk=complexPredit.m_CliqueNodes.begin();iterk!=complexPredit.m_CliqueNodes.end();iterk++){
			for(iterp=complexPC.cliqueVex[record].m_CliqueNodes.begin();iterp!=complexPC.cliqueVex[record].m_CliqueNodes.end();iterp++)
			{
				if((*iterp)==(*iterk))
					commonProteins.m_CliqueNodes.push_back(*iterp);
			}
		}	
		std::ofstream OutFile;
		OutFile.open(outFile,ios::app);
		if (!OutFile)
		{
			std::cout<<"Can't create file !"<<std::endl;
		}
		if(count==1)
		{	
			OutFile<<endl<<endl<<endl;
			OutFile<< "　 The original complex is: ****************************************************"<<endl;
			for(iterk=complexPredit.m_CliqueNodes.begin();iterk!=complexPredit.m_CliqueNodes.end();iterk++){
			OutFile<<*iterk<<"  ";
			}
		}
		OutFile<<endl<< "**********  TimePoint:  **********"<<timepoint<<endl;
		OutFile<<"Its match complex is:"<<endl;
		for(int k=0;k<complexPC.cliqueVex[record].m_CliqueNodes.size();k++){
			OutFile<<complexPC.cliqueVex[record].m_CliqueNodes[k]<<"  ";
		}
		OutFile<<endl<<" Their common proteins are:"<<endl;
		for(iterk=commonProteins.m_CliqueNodes.begin();iterk!=commonProteins.m_CliqueNodes.end();iterk++){
			OutFile<<*iterk<<"  ";		
		}
		OutFile<<endl<<"OS:  "<<complexPredit.os<<endl<<endl;	
		if(OutFile)
			OutFile.close();
		return &complexPC.cliqueVex[record];
		}
	else 
		return NULL;	
}