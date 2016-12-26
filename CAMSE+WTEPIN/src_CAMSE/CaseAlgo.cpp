#include "stdafx.h"
#include<stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#define tvOverlap 0.8
#define n_subPINs 36
using namespace std;
#include "DataStruct.h"
#include "myFunction.h"
#include "CASEonGraph.h"
#include <string>
#include <string.h>
#include <time.h>

int main(int args,char **argv)
{
	double inf;
	double outf;	
	Graph graph;
	bool mark;
	for (inf = 0.7;inf <=0.7;inf+=0.05)
	{	
		for (outf =0.6;outf <= 0.6;outf+=0.1)	
		{	
			char str2[10] = "_IN_";
			char s2[4];		  
			gcvt(inf,4,s2); //把double型的inf保留4位转换为字符串给s
			strcat(str2,s2);
			strcat(str2,"_OUT_");
			gcvt(outf,2,s2);
			strcat(str2,s2);
			strcat(str2,".txt");		  
			for(int interval=1;interval<=n_subPINs;interval+=1)   
			{
				char wpin[100]="data//krogan_extended_interval_ppi_uPlus3sigma//Interval_ppi_";
				char inter[2];
				itoa(interval,inter,10);
				strcat(wpin,inter);
				strcat(wpin,".txt");
				char  Infilename[100];
				strcpy(Infilename,wpin);
				char    SCComplexesfilename[100] ;
				strcpy(SCComplexesfilename,Infilename);
				SCComplexesfilename[strlen(SCComplexesfilename)-4] = '\0';	  
				char str[50] = "_Complexes_IN_";
				char s[4];		  
				gcvt(inf,4,s); //把double型的inf保留4位转换为字符串给s
				strcat(str,s);
				strcat(str,"_OUT_");
				gcvt(outf,2,s);
				strcat(str,s);
				strcat(str,".txt");		  
				strcat(SCComplexesfilename,str);
				char allcomFileName[100]="data//krogan_CAMSE_DPIN3SIG.txt";
				strcat(allcomFileName,str);
				std::cout<<SCComplexesfilename<<std::endl;	
				if(interval==n_subPINs)   
					mark=true; //mark标志为true表示要将合并的复合物过滤、输出到文件
				else 
					mark=false;
				graph.loadGraph(Infilename,SCComplexesfilename,allcomFileName,inf,outf,mark);	
				graph.m_ComplexArray.clear();
				graph.m_nNumEdges=0;
				graph.m_NodeArray.clear();
			}
		}		
	}
	return 0;
}
