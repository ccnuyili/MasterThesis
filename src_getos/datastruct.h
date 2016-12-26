#pragma once
#include<stdlib.h>
#include <string>
#include<cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
#define minCliqueSize 2
double tvOS=0.2;

struct Clique//团类;
{
public:
	std::vector<string>	m_CliqueNodes;//团的节点向量;
	double os;
	bool mark;
	double m_matchIndex;//与之匹配的复合物编号,0表示么有匹配
	int m_Index;//从1开始
public:
	Clique() {
		os = 0;
		m_matchIndex = 0;
	}
};

class ComplexSet {
public:
	vector<Clique> cliqueVex;
public:
	ComplexSet() {
	}
};


class CompDcend  //降序
{
public:
	bool operator ()(const  Clique& stItem1, const  Clique& stItem2)
	{
		return stItem1.m_CliqueNodes.size() > stItem2.m_CliqueNodes.size();
	}
};

void readComplexfile(ComplexSet &complexset, const string file) {
	std::ifstream inFile;
	inFile.open(file.c_str());
	if (!inFile) {
		cout << "can not open the file " << file << endl;
		return;
	}
	int splitString(string &strSrc, const string &strDelims, vector<string>& strDest);
	const string strDelims = "\t, \n";
	vector<string> splitStrs;
	vector<string>::iterator iter;
	string str;
	int cliqueId = 0;
	while (!inFile.eof()) {
		getline(inFile, str, '\n');
		Clique pClique;
		splitStrs.clear();
		splitString(str, strDelims, splitStrs);
		for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter) {
			pClique.m_CliqueNodes.push_back(*iter);
		}
		pClique.m_Index = ++cliqueId;
		complexset.cliqueVex.push_back(pClique);
	}
	if (inFile)
		inFile.close();
}

double OS(Clique pc, Clique kc) {
	//与已知复合物比较 匹配程度
	std::vector<string>::iterator iterk;
	std::vector<string>::iterator iterp;
	double num = 0;
	double os = 0;
	for (iterk = kc.m_CliqueNodes.begin();iterk != kc.m_CliqueNodes.end();iterk++) {
		for (iterp = pc.m_CliqueNodes.begin();iterp != pc.m_CliqueNodes.end();iterp++)
		{
			if ((*iterp) == (*iterk))
			{
				num++;
				continue;
			}
		}
	}
	os = (double)(num*num) / ((double)pc.m_CliqueNodes.size()*(double)kc.m_CliqueNodes.size());
	return os;
}

int getPredictComplexOS(ComplexSet &complexPredit, ComplexSet &complexKC, const string identify, char PCinformationFile[], char osFile[]) {
	//PC与KC匹配
	double os;
	for (size_t i = 0;i < complexPredit.cliqueVex.size();i++) {
		complexPredit.cliqueVex[i].os = 0;
	}
	size_t TP = 0, numPC = 0;
	numPC = complexPredit.cliqueVex.size();
	double avesize = 0;
	size_t maxsize = 0;
	for (size_t i = 0;i<complexPredit.cliqueVex.size();i++) {
		//对于标准复合物测试集中的每个复合物：求得它与预测的蛋白质复合物的最大的匹配值OS
		os = 0;
		for (size_t j = 0;j < complexKC.cliqueVex.size();j++) {
			os = OS(complexPredit.cliqueVex[i], complexKC.cliqueVex[j]);
			if (os > complexPredit.cliqueVex[i].os)
			{
				complexPredit.cliqueVex[i].os = os;
				complexPredit.cliqueVex[i].m_matchIndex = complexKC.cliqueVex[j].m_Index;
			}
		}

		if (complexPredit.cliqueVex[i].m_CliqueNodes.size()>maxsize)
			maxsize = complexPredit.cliqueVex[i].m_CliqueNodes.size();
		avesize += complexPredit.cliqueVex[i].m_CliqueNodes.size();
		if (complexPredit.cliqueVex[i].os >= tvOS) {
			TP++;
		}
	}
	if(tvOS>0.2)
		return TP;
	avesize /= complexPredit.cliqueVex.size();
	std::ofstream OutFile;
	OutFile.open(osFile);
	if (!OutFile)
	{
		std::cout << "Can't create file !" << std::endl;
	}
	for (size_t i = 0;i < complexPredit.cliqueVex.size();i++)
	{
		OutFile << complexPredit.cliqueVex[i].os << "\t" << complexPredit.cliqueVex[i].m_matchIndex << endl;
	}
	if (OutFile)
		OutFile.close();
	bool exist = true;
	ifstream ifile(PCinformationFile);
	if (!ifile)
		exist = false;
	else
		ifile.close();

	OutFile.open(PCinformationFile, ios::app);
	if (!OutFile)
	{
		std::cout << "Can't create file !" << std::endl;
	}
	else {
		if (!exist)
		{
			OutFile << "ComplexSet\tAverageSize\tMaxSize:\tTP\tTotalNum\n";
			OutFile << identify << "\t" << avesize << "\t" << maxsize << "\t" << TP << "\t" << complexPredit.cliqueVex.size() << endl;
		}
		else
			OutFile << identify << "\t" << avesize << "\t" << maxsize << "\t" << TP << "\t" << complexPredit.cliqueVex.size() << endl;
		OutFile.close();
	}
	return TP;
}
int getKnownComplexOS(ComplexSet &ComplexKC, ComplexSet &ComplexPC, const string identify, char KCinformationFile[], char osFile[]) {
	//KC被PC识别
	double os;
	for (size_t i = 0;i < ComplexKC.cliqueVex.size();i++) {
		ComplexKC.cliqueVex[i].os = 0;
	}
	size_t numMatchedKC = 0;
	int a_1 = 0, a_2 = 0, a_3 = 0, a_4 = 0, a_5 = 0, a_6 = 0, a_7 = 0, a_8 = 0, a_9 = 0, a_10 = 0;
	for (size_t i = 0;i < ComplexKC.cliqueVex.size();i++) {
		//对于标准复合物测试集中的每个复合物：求得它与预测的蛋白质复合物的最大的匹配值OS
		os = 0;
		for (size_t j = 0;j < ComplexPC.cliqueVex.size();j++) {
			os = OS(ComplexKC.cliqueVex[i], ComplexPC.cliqueVex[j]);
			if (os > ComplexKC.cliqueVex[i].os) {
				ComplexKC.cliqueVex[i].os = os;
				ComplexKC.cliqueVex[i].m_matchIndex = ComplexPC.cliqueVex[j].m_Index;
			}
		}

		if (ComplexKC.cliqueVex[i].os == 1.0) {
			a_10++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.9) {
			a_9++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.8) {
			a_8++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.7) {
			a_7++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.6) {
			a_6++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.5) {
			a_5++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.4) {
			a_4++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.3) {
			a_3++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.2) {
			a_2++;
		}

		if (ComplexKC.cliqueVex[i].os >= 0.1) {
			a_1++;
		}
		
		if(ComplexKC.cliqueVex[i].os>=tvOS)
			numMatchedKC++;
		
	}
	if(tvOS>0.2)
		return numMatchedKC;
	//numMatchedKC = a_2;
	std::ofstream OutFile;
	OutFile.open(osFile);
	if (!OutFile)
	{
		std::cout << "Can't create file !" << std::endl;
	}
	for (size_t i = 0;i < ComplexKC.cliqueVex.size();i++)
	{
		OutFile << ComplexKC.cliqueVex[i].os << "\t" << ComplexKC.cliqueVex[i].m_matchIndex << endl;
	}
	if (OutFile)
		OutFile.close();
	bool exist = true;
	ifstream ifile(KCinformationFile);
	if (!ifile)
		exist = false;
	else
		ifile.close();
	OutFile.open(KCinformationFile, ios::app);
	if (!OutFile)
	{
		std::cout << "Can't create file !" << std::endl;
	}
	else {
		if (!exist)
		{
			OutFile << "complexSet\tnumMatchedKC\t0.1\t0.2\t0.3\t0.4\t0.5\t0.6\t0.7\t0.8\t0.9\t1.0\n";
			OutFile << identify << "\t" << numMatchedKC << "\t" << a_1 << "\t" << a_2 << "\t" << a_3 << "\t" << a_4 << "\t" << a_5 << "\t" << a_6 << "\t" << a_7 << "\t" << a_8 << "\t" << a_9 << "\t" << a_10 << endl;
		}
		else
			OutFile << identify << "\t" << numMatchedKC << "\t" << a_1 << "\t" << a_2 << "\t" << a_3 << "\t" << a_4 << "\t" << a_5 << "\t" << a_6 << "\t" << a_7 << "\t" << a_8 << "\t" << a_9 << "\t" << a_10 << endl;
		OutFile.close();
	}

	return numMatchedKC;
}
int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)
{	//分割字符串strSrc,分隔符为strDelims中的各个字符，分割出来的各个分量存在strDest
	typedef string::size_type ST;
	string delims = strDelims;
	std::string STR;
	if (delims.empty())
		delims = "| ";
	ST pos = 0, LEN = strSrc.size();
	while (pos < LEN) {
		STR = "";
		while ((pos < LEN) && (delims.find(strSrc[pos]) != std::string::npos))
			++pos;
		if (pos == LEN)
			return strDest.size();
		while ((pos < LEN) && (delims.find(strSrc[pos]) == std::string::npos))
			STR += strSrc[pos++];
		if (!STR.empty())
			strDest.push_back(STR);
	}
	return strDest.size();
}
