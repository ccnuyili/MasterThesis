#include "stdafx.h"
#include<string>
#include<fstream>
#include<iostream>
#include<regex>
using namespace::std;

int main()
{
	double count_0 = 0, count_1 = 0, count_2 = 0, count_3 = 0, count_4 = 0, totalcount = 0;
	const char* pfile="camseResult.txt";
	const char* tofile("data//pvalue_all.txt");
	smatch m;
	regex e("(.*)(E)(.*)");
	ifstream infile(pfile);
	string str;
	double p=0;
	infile >> str;
	while (!infile.eof())
	{
		infile >> str;
		regex_search(str, m, e);
		if (m.size() > 0)
		{
			str = m[3];
			p = atof(str.c_str());
			if (p < -15)
				count_0++;
			else if (p < -10)
				count_1++;
			else if (p <-5)
				count_2++;
			else if (p < -2)
				count_3++;
			else
				count_4++;
		}
		else
		{
			p = atof(str.c_str());
			if (p <= 1e-15)
				count_0++;
			else if (p <= 1e-10)
				count_1++;
			else if (p <= 1e-5)
				count_2++;
			else if (p <= 0.01)
				count_3++;
			else
				count_4++;
			
		}
		totalcount++;
	}
	infile.close();
	ofstream ofile(tofile,ios::app);
	ofile << pfile << endl;
	ofile << count_0 << "(" << 100*count_0 / totalcount << "%)\t" <<count_1 << "(" << 100 * count_1 / totalcount << "%)\t" << count_2 << "(" << 100 * count_2 / totalcount << "%)\t" << count_3 << \
		"(" << 100 * count_3 / totalcount << "%)\t" << count_4 << "(" << 100 * count_4 / totalcount << "%)\t" << endl;
	ofile.close();
    return 0;
}

