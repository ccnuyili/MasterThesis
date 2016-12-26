#include "stdafx.h"

#include "dataStruct.h"
#include "getTheComplexCloselyToMyComplex.h"

void main(int args,char *argv[] )
{
	int count=0;
	int start=1;
	int end=8;
	int tagTimePoint=0;
	string str_complex="YOR224C YPR110C YOR341W YOR116C YNR003C YKL144C YJR063W YJL011C YBR154C YPR190C YPR187W YPR010C YOR207C YNL248C YNL113W YBR245C YGR005C YIL021W YGL070C YDR404C YOR151C";
	//string str_complex="YOR224C  YPR110C  YOR116C  YNR003C  YKL144C  YJR063W  YJL011C  YBR154C  YPR187W  YPR010C  YOR207C  YNL113W";
	//string str_complex="YCR057C YPR144C YPR137W YPL217C YPL126W YPL094C YOR310C YOR078W YNR054C YNL132W YNL075W YNL064C YMR300C YMR128W YMR093W YML130C YLR409C YLR222C YLR197W YLR186W YLR175W YLR129W YLL011W YKR060W YKL099C YJR002W YJL109C YJL069C YJL033W YHR196W YHR169W YHR148W YGR210C YGR145W YGR128C YGR090W YGL171W YGL120C YER082C YDR502C YDR449C YDR382W YDR365C YDR324C YDR299W YDR034C YDL213C YDL148C YDL014W YCL059C YBR247C YBL004W YNL061W YPL043W YNL207W YLR180W YDL208W YPL012W YHR089C YDR060W YOL010W";
	//string str_complex="YPR110C YPR187W YPR010C YOR332W YOR224C YOR210W YOR207C YOR116C YNR003C YNL308C YNL248C YNL229C YNL151C YNL113W YMR285C YLR086W YKR025W YKL144C YJR063W YJL011C YDL150W YBR154C";
	//string str_complex="YOR116C YPR190C YPR187W YPR110C YOR224C YOR207C YNR003C YNL151C YNL113W YMR116C YKR025W YKL144C YKL060C YJL011C YGL070C YFR037C YDR045C YDL150W YBR154C YOR341W YBR245C YMR091C YCR052W";
	//string str_complex="YJR063W YPR187W YPR110C YPR010C YOR341W YOR340C YOR224C YOR210W YNL113W YDR156W YBR228W YBR220C YBR187W YBR154C YOR116C YKL144C YOR207C YNR003C YNL248C YBR245C";
	//string str_complex="YDR377W  YBL099W  YJR121W  YKL016C  YML081C-A  YPL078C  YDL004W  ";
	Clique	mycomplex;//
	Clique *nextClique;
	Clique *getTheComplexCloselyToMyComplex(Clique &complexPredit,ComplexSet &complexPC,char outFile[],int timepoint,int &count);
	int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest);
	const string strDelims="\t \n";
	vector<string> splitStrs;
	vector<string>::iterator iter; 
	splitStrs.clear();
	splitString(str_complex,strDelims,splitStrs);
	for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter) {  
		mycomplex.m_CliqueNodes.push_back(*iter);
	}
	//int interval=0;
	for (int interval = start;interval <=end;interval+=1)
	{		
	//	if( interval==tagTimePoint)continue;
	//	char PCfile[100]="data//Complexes_";
		char PCfile[100]="timePointsComplex//_timePoint_";
		char str2[30];		  
		itoa(interval,str2,10);
		strcat(str2,".txt");
		strcat(PCfile,str2);
	//	char PCfile[100]="E://_dataTest//sourceData//complexMIPS.txt";
		char dynamicComplexFile[100]="dynamicComplex.txt";
		ComplexSet complexPredict;	
		readComplexfile(complexPredict,PCfile);	
		nextClique=getTheComplexCloselyToMyComplex(mycomplex,complexPredict,dynamicComplexFile,interval,count);
	//	if(nextClique==NULL)
	//		continue;
	//	mycomplex.m_CliqueNodes.clear();
	//	for(int my=0;my<nextClique->m_CliqueNodes.size();my++){
	//		mycomplex.m_CliqueNodes.push_back(nextClique->m_CliqueNodes[my]);		
	//}
	}
}
