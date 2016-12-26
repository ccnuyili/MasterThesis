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

#define tvOS 0.2
#define minCliqueSize 2

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

void  FilterClique(ComplexSet &complexset)
{ //已经按复合物大小降序排列，后者与前者相比，考虑后者要不要删
	sort(complexset.cliqueVex.begin(), complexset.cliqueVex.end(), CompDcend());
	int findNum;
	int mi;
	int mj;
	std::vector<string>::iterator iter;
	double overlap;
	for (int i = 0;i < complexset.cliqueVex.size();i++) {
		complexset.cliqueVex[i].mark = true;
	}
	for (int i = 0;i < complexset.cliqueVex.size() - 1;i++) {
		if (complexset.cliqueVex[i].mark == false)continue;
		for (int j = i + 1;j < complexset.cliqueVex.size();j++) {
			if (complexset.cliqueVex[j].mark == false)continue;
			findNum = 0;
			mi = complexset.cliqueVex[i].m_CliqueNodes.size();
			mj = complexset.cliqueVex[j].m_CliqueNodes.size();
			for (int jd = 0;jd < mj;jd++)
			{
				for (iter = complexset.cliqueVex[i].m_CliqueNodes.begin();iter != complexset.cliqueVex[i].m_CliqueNodes.end();iter++)
				{	//若找到
					if ((*iter) == complexset.cliqueVex[j].m_CliqueNodes[jd])
					{
						findNum++;
						break;
					}
				}
			}
			if ((mi != 0) && (mj != 0))
			{
				overlap = (double)(findNum*findNum) / (mi*mj);
			}
			if (overlap - 1 == 0) {//去重
				complexset.cliqueVex[j].mark = false;
			}
			if(findNum==mj)
				complexset.cliqueVex[j].mark = false;
		}
	}
}


void outPutComplex(ComplexSet toComplexset, const string scFileName)
{
	std::ofstream OutFile;
	OutFile.open(scFileName.c_str());
	if (!OutFile)
	{
		std::cout << "Can't create OutPut file COMPLEX!" << std::endl;
	}
	for (int i = 0;i < toComplexset.cliqueVex.size();i++)
	{
		if (toComplexset.cliqueVex[i].mark == false)continue;
		if (toComplexset.cliqueVex[i].m_CliqueNodes.size()>= minCliqueSize) {
			int j;
			for (j = 0;j < toComplexset.cliqueVex[i].m_CliqueNodes.size()-1;j++)
			{
				OutFile << toComplexset.cliqueVex[i].m_CliqueNodes[j] << '\t';
			}
			OutFile << toComplexset.cliqueVex[i].m_CliqueNodes[j];
			OutFile << std::endl;
		}
	}
	if (OutFile)	OutFile.close();

}

int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)
{	//分割字符串strSrc,分隔符为strDelims中的各个字符，分割出来的各个分量存在strDest
	typedef string::size_type ST;
	string delims = strDelims;
	std::string STR;
	if (delims.empty())
		delims = "|";
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
