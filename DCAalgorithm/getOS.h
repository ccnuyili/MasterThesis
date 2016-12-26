#pragma once

#include"stdafx.h"
#include"clique.h"

void readComplexfile(ComplexSet &complexset, const char* file) {

	std::ifstream inFile;
	inFile.open(file);
	if (!inFile) {
		cout << "can not open the file " << file << endl;
		return;
	}
	const string strDelims = "\t \n";
	vector<string> splitStrs;
	vector<string>::iterator iter;
	char str[10000];
	char c = '\0';
	int i = 0;
	int inode = 0;
	inFile >> noskipws;
	int cliqueId = 0;
	int proteinNum = 0;
	while (!inFile.eof()) {
		while (!inFile.eof() && c != '\n')
		{
			inFile >> c;
			str[i++] = c;
		}
		str[i] = '\0';
		Clique *pClique = new Clique();
		splitStrs.clear();
		int splitString(string &strSrc, const string &strDelims, vector<string>& strDest);
		string s(&str[0], &str[strlen(str)]);
		splitString(s, strDelims, splitStrs);
		for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter) {
			pClique->m_CliqueNodeNames.push_back(*iter);
		}
		complexset.cliqueVex.push_back(pClique);
		i = 0;
		c = '\0';
		inode = 0;
	}
	if (inFile)
		inFile.close();
}

double OS(const Clique *pc, const Clique *kc) {
	//与已知复合物比较 匹配程度
	std::vector<string>::const_iterator iterk;
	std::vector<string>::const_iterator iterp;
	double num = 0;
	double os = 0;
	for (iterk = kc->m_CliqueNodeNames.begin();iterk != kc->m_CliqueNodeNames.end();iterk++) {
		for (iterp = pc->m_CliqueNodeNames.begin();iterp != pc->m_CliqueNodeNames.end();iterp++)
		{
			if ((*iterp) == (*iterk))
				num++;
		}
	}
	os = (double)(num*num) / ((double)pc->m_CliqueNodeNames.size()*(double)kc->m_CliqueNodeNames.size());
	return os;
}

int getPredictComplexOS(ComplexSet &complexPredit, ComplexSet &complexKC, const char* identify, const char* PCinformationFile, const char* osFile) {
	//PC与KC匹配
	double os;
	for (size_t i = 0;i < complexPredit.cliqueVex.size();i++) {
		complexPredit.cliqueVex[i]->os = 0;
	}

	double TP = 0, numPC = 0;
	numPC = complexPredit.cliqueVex.size();
	double avesize = 0;
	size_t maxsize = 0;
	for (size_t i = 0;i<complexPredit.cliqueVex.size();i++) {
		//对于标准复合物测试集中的每个复合物：求得它与预测的蛋白质复合物的最大的匹配值OS
		os = 0;
		for (size_t j = 0;j < complexKC.cliqueVex.size();j++) {
			os = OS(complexPredit.cliqueVex[i], complexKC.cliqueVex[j]);
			if (os > complexPredit.cliqueVex[i]->os)
			{
				complexPredit.cliqueVex[i]->os = os;
			}
		}

		if (complexPredit.cliqueVex[i]->m_CliqueNodeNames.size()>maxsize)
			maxsize = complexPredit.cliqueVex[i]->m_CliqueNodeNames.size();
		avesize += complexPredit.cliqueVex[i]->m_CliqueNodeNames.size();
		if (complexPredit.cliqueVex[i]->os >= 0.2) {
			TP++;
		}
	}

	avesize /= numPC;
	std::ofstream OutFile;
	OutFile.open(PCinformationFile, ios::app);
	if (!OutFile)
	{
		std::cout << "Can't create file !" << std::endl;
	}
	else {
		OutFile << identify << ":    " << "AverageSize: " << avesize << "    MaxSize:" << maxsize << "    TP:" << TP << "    TotalNum: " << complexPredit.cliqueVex.size() << endl;
	}
	return TP;
}

int getKnownComplexOS(ComplexSet &ComplexKC, ComplexSet &ComplexPC, const char* identify, const char* KCinformationFile, const char* osFile) {
	//KC被PC识别
	double os;
	for (size_t i = 0;i < ComplexKC.cliqueVex.size();i++) {
		ComplexKC.cliqueVex[i]->os = 0;
	}

	double numMatchedKC = 0;
	int a_1 = 0, a_2 = 0, a_3 = 0, a_4 = 0, a_5 = 0, a_6 = 0, a_7 = 0, a_8 = 0, a_9 = 0, a_10 = 0;
	for (size_t i = 0;i < ComplexKC.cliqueVex.size();i++) {
		//对于标准复合物测试集中的每个复合物：求得它与预测的蛋白质复合物的最大的匹配值OS
		os = 0;
		for (size_t j = 0;j < ComplexPC.cliqueVex.size();j++) {
			os = OS(ComplexKC.cliqueVex[i], ComplexPC.cliqueVex[j]);
			if (os > ComplexKC.cliqueVex[i]->os)
				ComplexKC.cliqueVex[i]->os = os;
		}

		if (ComplexKC.cliqueVex[i]->os == 1.0) {
			a_10++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.9) {
			a_9++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.8) {
			a_8++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.7) {
			a_7++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.6) {
			a_6++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.5) {
			a_5++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.4) {
			a_4++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.3) {
			a_3++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.2) {
			a_2++;
		}

		if (ComplexKC.cliqueVex[i]->os >= 0.1) {
			a_1++;
		}
	}
	numMatchedKC = a_2;
	std::ofstream OutFile;
	OutFile.open(KCinformationFile, ios::app);
	if (!OutFile)
	{
		std::cout << "Can't create file !" << std::endl;
	}
	else {
		OutFile << identify << ":   " << "numMatchedKC:  " << numMatchedKC << "  0.1---1.0:  " << a_1 << "    " << a_2 << "    " << a_3 << "    " << a_4 << "    " << a_5 << "    " << a_6 << "    " << a_7 << "    " << a_8 << "    " << a_9 << "    " << a_10 << endl;
	}
	return numMatchedKC;
}

int splitString(string &strSrc, const string &strDelims, vector<string> &strDest)
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


