#pragma once
#include"myheader.h"
#include"proteinExpression.h"


class PPI {
public:
	Protein proteinA;
	Protein proteinB;
	PPI() {}
	PPI(Protein  a, Protein  b) {
		proteinA = a;
		proteinB = b;
	}
	PPI(string  a, string  b) {
		proteinA.name = a;
		proteinB.name = b;
	}
	inline bool operator==(const PPI &p) const {
		if ((proteinA.name == p.proteinA.name  &&proteinB.name == p.proteinB.name) || \
			proteinB.name == p.proteinA.name  &&proteinA.name == p.proteinB.name)
			return true;
		else return false;
	}
};


class PPISet {
public:
	std::vector<PPI*>	ppiVec;
public:
	PPISet() {};
	~PPISet() {
		for (size_t i = 0; i < ppiVec.size(); ++i) {
			if (ppiVec[i] != NULL)
				delete ppiVec[i];
		}
		ppiVec.clear();
	}
};


class sliceSet {
public:
	std::vector<PPISet*>  sliceVec;
	sliceSet() {
	}

	~sliceSet() {
		for (size_t i = 0; i < sliceVec.size(); ++i) {
			if (sliceVec[i] != NULL)
				delete sliceVec[i];
		}
		sliceVec.clear();
	}

	void init() {
		for (size_t i = 0;i < SampleNum;i++) {
			PPISet *aSlice = new PPISet();
			sliceVec.push_back(aSlice);
		}
	}
	template<class ProteinType>	sliceSet(const char *originalPPIfile, const ProteinVec<ProteinType> &expressionMatrix) {
		init();
		std::ifstream inFile;
		inFile.open(originalPPIfile);
		if (!inFile) {
			cout << "can not open the file " << originalPPIfile << endl;
			return;
		}
		string sA;
		string sB;
		Protein *proteinA;
		Protein *proteinB;
		while (!inFile.eof()) {
			inFile >> sA;
			inFile >> sB;
			if (sA == sB)
				continue;
			proteinA = expressionMatrix.search(sA);
			proteinB = expressionMatrix.search(sB);
			if (proteinA == NULL || proteinB == NULL)
				continue;
			for (int i = 0;i < SampleNum;i++) {
				if (proteinA->isActive[i] && proteinB->isActive[i]) {
					PPI *ppi = new PPI(*proteinA, *proteinB);
					sliceVec[i]->ppiVec.push_back(ppi);
				}
			}
		}
		if (inFile)
			inFile.close();
	}


	void output(const char *intervalPPI_Arch) const {
		char ch_k[3];
		string str_k;
		int avePpi_num = 0;
		for (int k = 0;k < SampleNum;k++) {
			string toFileName(&intervalPPI_Arch[0], &intervalPPI_Arch[strlen(intervalPPI_Arch)]);
			_itoa_s(k + 1, ch_k, 3, 10);
			str_k = ch_k;
			toFileName += ("Interval_ppi_" + str_k + ".txt");
			std::ofstream OutFile;
			OutFile.open(toFileName);
			if (!OutFile)
			{
				std::cout << "Can't Create Output File_" << k << "  " << std::endl;
				return;
			}
			std::vector<PPI*>::iterator ppiIter = sliceVec[k]->ppiVec.begin();
			while (ppiIter != sliceVec[k]->ppiVec.end())
			{
				OutFile << (*ppiIter)->proteinA.name << "\t" << (*ppiIter)->proteinB.name << endl;
				ppiIter++;
			}

			if (OutFile)
				OutFile.close();
			avePpi_num += sliceVec[k]->ppiVec.size();
		}
		cout << "平均每个slice的ppi数量：" << (double)avePpi_num / 36 << endl;
	}


	template<class ProteinType>	sliceSet(const char *originalPPIfile, const char *resultPPIfile, const ProteinVec<ProteinType> &expressionMatrix) {
		//过滤PPI,输出到文件
		std::ifstream inFile;
		inFile.open(originalPPIfile);
		if (!inFile) {
			cout << "can not open the file " << originalPPIfile << endl;
			return;
		}
		std::ofstream oFile;
		oFile.open(resultPPIfile);
		if (!oFile) {
			cout << "can not open the file " << resultPPIfile << endl;
			return;
		}

		string sA;
		string sB;
		Protein *proteinA;
		Protein *proteinB;
		std::vector<PPI>	ppiVec;

		while (!inFile.eof()) {
			inFile >> sA;
			inFile >> sB;
			if (sA == sB)
				continue;
			proteinA = expressionMatrix.search(sA);
			proteinB = expressionMatrix.search(sB);
			if (proteinA == NULL || proteinB == NULL)
				continue;
			PPI *ppi = new PPI(sA, sB);
			if (find(ppiVec.begin(), ppiVec.end(), *ppi) == ppiVec.end()) {
				ppiVec.push_back(*ppi);
				oFile << sA << "\t" << sB << endl;
			}
		}

		if (oFile)
			oFile.close();
		if (inFile)
			inFile.close();
	}
};