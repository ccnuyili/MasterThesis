#include<stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <list>
using namespace std;

#define tvOS 0.2
#define minCliqueSize 2

struct Clique//����;
{
public:
	std::vector<string>	m_CliqueNodes;//�ŵĽڵ�����;
	double os;
	int nodeNum;
	bool mark;
public:
	Clique(){
		os=0;
		nodeNum=0;
	};
};

class ComplexSet{

public:
	vector<Clique> cliqueVex;
	int cliqueNum;
public:
	ComplexSet(){
		cliqueNum=0;
	}
}; 


class CompDcend  //����
{  
 public:  
   bool operator ()(const  Clique& stItem1, const  Clique& stItem2)  
    {  
       return stItem1.m_CliqueNodes.size() > stItem2.m_CliqueNodes.size();  
    }  
 };
