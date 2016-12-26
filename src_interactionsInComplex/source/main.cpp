
#include <vector>
#include <algorithm>
#include <iterator>
#include<stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;  
#include "clique.h"
#include "graph.h"
#include"getedges.h"
int main(int args, char* argv[])
{
	Clique clique;
	char complexfile[100];
	char ppi[100];
	char edgesfile[100];
	if(args==4)
		{		
		stringstream ss(argv[1]);
		ss>>complexfile;
		ss.clear();
		ss.str(argv[2]);
		ss>>edgesfile;
		ss.clear();
		ss.str(argv[3]);
		ss>>ppi;
		ss.clear();
		GraphLoader rawgraph(ppi);
		readComplexfile(clique, complexfile);
		getEdges(edgesfile,clique,rawgraph);
		cout<<argv[1]<<"...ok!"<<endl;
	}
}

