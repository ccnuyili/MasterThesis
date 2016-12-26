#include "stdafx.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#define n_subPINs 36
using namespace std;  

#include "datastruct.h"
#include "graph.h"
#include "getActiveNodes.h"
#include"getIntervalPPI.h"
#include"getW.h"

int main(int argc, char* argv[])
{
	ExpressionSet expSet;	
	char  geneExpFile[100] = "Express.txt";	
	char  NodesAtIntervalFile1[100] = "NodesAtInterval//";

	LoadAndSetActive(geneExpFile,expSet);
	outPutActiveNodesToFile(NodesAtIntervalFile1,expSet);

	//get dynamic PPI
	char nodesFile[n_subPINs][100];
	char str[5];
	for(int k=1;k<=n_subPINs;k++){		
		strcpy(nodesFile[k-1],NodesAtIntervalFile1);
		strcat(nodesFile[k-1],"_NodesAtInterval_");
		itoa(k,str,10);
		strcat(nodesFile[k-1],str);
		strcat(nodesFile[k-1],".txt");
	}
	std::vector<Nodeset> ns;
	readIntervalNodeSetFile(nodesFile,ns);

	char scppi[100]="ppi.txt";
	char szppi[n_subPINs][100];
	char szwpin[n_subPINs][100];
	for(int k=1;k<=n_subPINs;k++){
		char ppi[100]="ppi//ppi_";		
		strcpy(szppi[k-1],ppi);
		itoa(k,str,10);
		strcat(szppi[k-1],str);
		strcat(szppi[k-1],".txt");
		char intervalWPINfile[100]="wpin//wpin_"; 
		strcpy(szwpin[k-1],intervalWPINfile);
		itoa(k,str,10);
		strcat(szwpin[k-1],str);
		strcat(szwpin[k-1],".txt");
	}
	 buildIntervalPPI(scppi ,ns,szppi);

	 //Weight
	NodeMatrix complex;
	char pctfile[100]="complexMIPS.txt";
	char stt[5];
	Graph graph;
	readPCTfile(complex, pctfile);
	for(int k=1;k<=n_subPINs;k++)
		{		
		GraphLoader rawgraph(szppi[k-1]);
		LoadGraphFromRawGraph(graph,rawgraph);	
		rebuildWeight(expSet,szwpin[k-1],complex,rawgraph,graph);
		rawgraph.m_RawGraph.clear();
		graph.m_NodeArray.clear();
	}

//	char ppi[100]="ppi.txt";		
//	char w[100]="wpin.txt";	
//	GraphLoader rawgraph(ppi);
//	LoadGraphFromRawGraph(graph,rawgraph);	
//	rebuildWeight(expSet,w,complex,rawgraph,graph);

}

