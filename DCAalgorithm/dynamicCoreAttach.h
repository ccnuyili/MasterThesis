#pragma once
#include"myheader.h"
#include"graph.h"
#include"proteinExpression.h"
#include"getOS.h"

class DyCoreAttach {
public:
	Graph TotalComplex;
	vector<vector<Clique*> > sliceComplexVec; //0号不用，从1...36
	double alpha;
	double cliqueAveWtv;
	double outTV;


	~DyCoreAttach() {		
		for (size_t i = 0;i < sliceComplexVec.size();i++) {
			for (size_t j = 0;j < sliceComplexVec[i].size();j++)
				delete  sliceComplexVec[i][j];
		}
		sliceComplexVec.clear();
	}

	void out2SliceComplex(const Graph *graph);
	void changeProcess(const string outFile, double matchTV);

	template <class ProteinType> DyCoreAttach(const char *intervalPPI_Arch, string resultFileArch, const ProteinVec<ProteinType> &expressionMatrix):sliceComplexVec(SampleNum+1)
	{
		alpha = 0.6;
		cliqueAveWtv = 0.55;
		outTV = 1.4;
		double matchTV = 0.2;
		char ch_k[3];
		string str_k;
		for (int k = 0;k < SampleNum;k++) {

			string fromFileName(&intervalPPI_Arch[0], &intervalPPI_Arch[strlen(intervalPPI_Arch)]);
			_itoa_s(k + 1, ch_k, 3, 10);
			str_k = ch_k;
			fromFileName += ("Interval_ppi_" + str_k + ".txt");
			string subtofileLOG = resultFileArch + "complex_Interval_" + str_k + "LOG.txt";

			Graph *graph = new Graph(fromFileName.c_str());
			graph->getEdgeECC();
			graph->getNormSuvivalTime(expressionMatrix, k);
			graph->getWeight(k, alpha, 1.0 - alpha);
			graph->getCliques(k, cliqueAveWtv, cliqueAveWtv, outTV, alpha);
			graph->FilterClique_NodeIDs(1.0);
//			graph->outPutAllComplexLog(subtofileLOG);
			out2SliceComplex(graph);

			for (size_t ss = 0;ss < graph->m_CliqueArray.size();ss++) {
				Clique *cli = new Clique(*graph->m_CliqueArray[ss]);
				if (graph->m_CliqueArray[ss]->match == false)
					continue;
				for (size_t ii = 0;ii < graph->m_CliqueArray[ss]->m_CliqueNodeIDs.size();ii++)
				{
					char* protein = graph->m_NodeArray[graph->m_CliqueArray[ss]->m_CliqueNodeIDs[ii]]->m_szName;
					cli->m_CliqueNodeNames.push_back(protein);
				}
				TotalComplex.m_CliqueArray.push_back(cli);
			}
			graph->clearGraph();
		}
		string tofile = resultFileArch + "complex_" + "_alpha=" + to_string(alpha) + \
			"_cliqueAveTV=" + to_string(cliqueAveWtv) + "_outTV=" + to_string(outTV) + ".txt";
		string logfile = tofile + "LOG.txt";
		TotalComplex.FilterClique_NodeNames(1.0);
//		TotalComplex.outPutAllComplex(tofile);
//		TotalComplex.outPutAllComplexLog(logfile);

		/*
		float tp = 0, fp = 0, fn = 0, numKC = 0, numPC = 0, tn = 0, sn = 0, sp = 0, f_measure = 0;
		const char* knownComplexFile = "data//CYC2008.txt";
		const char* PCInformationFile = "data//match_CYC2008//PCinformation.txt";
		const char* KCInformationFile = "data//match_CYC2008//KCinformation.txt";
		const char* F_measureFile = "data//match_CYC2008//ACC.txt";		
		string osPCfile = "data//match_CYC2008//os//Interval_os_PC" + str_k + ".txt";
		string osKCfile = "data//match_CYC2008//os//Interval_os_KC" + str_k + ".txt";
		ComplexSet complexKnown;
		ComplexSet complexPredict;

		readComplexfile(complexKnown, knownComplexFile);
		numKC = complexKnown.cliqueVex.size();
		readComplexfile(complexPredict, tofile.c_str());
		numPC = complexPredict.cliqueVex.size();
		tp = getPredictComplexOS(complexPredict, complexKnown, tofile.c_str(), PCInformationFile, osPCfile.c_str());
		tn = getKnownComplexOS(complexKnown, complexPredict, tofile.c_str(), KCInformationFile, osKCfile.c_str());
		fn = numKC - tn;
		fp = numPC - tp;
		sn = tp / (tp + fn);
		sp = tp / (tp + fp);
		f_measure = ((2 * sn*sp) / (sn + sp));
		
		std::ofstream OutFile;
		OutFile.open(F_measureFile, ios::app);
		if (!OutFile)
		{
			std::cout << "Can't create file !" << std::endl;
		}
		OutFile << tofile << ":  SN:" << sn << "   SP:" << sp << "   F-measure:" << f_measure << endl;
		if (OutFile)
			OutFile.close();
		*/		
		string FinalLogfile = tofile + "_finalLog.txt";
		changeProcess(FinalLogfile, matchTV);
		TotalComplex.clearGraph();
		cout << tofile << "	has done!" << endl << "________________________________" << endl;
	}
};


void DyCoreAttach::out2SliceComplex(const Graph *graph) {
	//把graph中的clique存在sliceComplexVec
	for (size_t i = 0;i < graph->m_CliqueArray.size();i++) {
		Clique *cli = graph->m_CliqueArray[i];
		if (cli->match) {
			Clique *nc = new Clique(*cli);
			for (size_t j = 0;j < cli->m_CliqueNodeIDs.size();j++)
			{
				char* protein = graph->m_NodeArray[cli->m_CliqueNodeIDs[j]]->m_szName;
				nc->m_CliqueNodeNames.push_back(protein);
			}
			sliceComplexVec[cli->sliceID].push_back(nc);
		}
	}
}

void DyCoreAttach::changeProcess(const string outFile,double matchTV){
	//sliceComplexVec
	//TotalComplex	
	std::ofstream OutFile;
	OutFile.open(outFile,ios::out);
	if (!OutFile)
	{
		std::cout << "Can't create file !"<< outFile << std::endl;
		return;
	}
	set<pair<double,int>* > topMatchRateIDVec;
	double AllmatchRate;
	int no = 1;
	for (size_t i = 0;i < TotalComplex.m_CliqueArray.size();i++) {
		AllmatchRate = 0;
		Clique *clique = TotalComplex.m_CliqueArray[i];
		int id = clique->sliceID;  //ID都从1开始
		if (clique->m_AttachNodes.size()<3)
			continue;
		double maxMatchRate;
		for (int nid = 1;nid < 37;nid++){
			maxMatchRate = 0;
			int bestCliNo = 0;
			for (size_t cliNo = 0;cliNo < sliceComplexVec[nid].size();cliNo++) {
				double os = OS(clique,sliceComplexVec[nid][cliNo]);
				if (os>0 && os> maxMatchRate)
				{
					maxMatchRate = os;
					bestCliNo = cliNo;
				}
			}
			if (maxMatchRate >= matchTV)
			{
				sliceComplexVec[nid][bestCliNo]->os = maxMatchRate;
				if (nid == id)
					OutFile << "******";
				OutFile << *sliceComplexVec[nid][bestCliNo];
				AllmatchRate += maxMatchRate;
				
			}
		}
		topMatchRateIDVec.insert(new pair<double,int>(AllmatchRate,no));
		OutFile <<endl<<"----------"<< endl << endl;
		no++;
	}
	OutFile << "top list:" << endl;
	set<pair<double, int>* >::iterator it=topMatchRateIDVec.end();
	it--;
	int top = 100;
	while (it != topMatchRateIDVec.begin() && top-- > 0) {
		OutFile << (*it)->second << "\t" << (*it)->first << endl;
		it--;
	}
	OutFile.close();
}