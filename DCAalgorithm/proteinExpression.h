#pragma once
#include"myheader.h"

class  Protein {
public:
	string name;
	double expValue[SampleNum];
	bool isActive[SampleNum];
	vector<int> activeInterval;
	int activeTimePointNum;
	bool everActive;//����ͳ�����κ�ʱ�̶�û���ĸ���
	Protein() {
		for (size_t i = 0; i < SampleNum; i++)
		{
			isActive[i] = false;
		}
		activeTimePointNum = 0;
		everActive = false;
	}
	virtual void setActive() {}
	bool equalto(Protein other) {
		if (name == other.name)
			return true;
		else
			return false;
	}
	Protein* operator=(const Protein* other) {
		name = other->name;
		for (size_t i = 0; i < SampleNum; i++)
		{
			expValue[i] = other->expValue[i];
			isActive[i] = other->isActive[i];
		}
		activeInterval = other->activeInterval;
		activeTimePointNum = other->activeTimePointNum;
		everActive = other->everActive;
		return this;
	}
	int consecutiveActiveTimePointNums(int interval)const {
		//����һ��ʱ���interval,����������slice�����Ļ���ʱ������
		int numInterval = 0;//��ǰʱ�̿϶�Ϊ����
		if (isActive[interval])
			numInterval++;
		else
			return 0;
		for (int leftInterval = interval - 1;leftInterval >= 0;leftInterval--) {
			if (isActive[leftInterval])
				numInterval++;
			else
				break;
		}
		for (int rightInterval = interval + 1;rightInterval < SampleNum;rightInterval++) {
			if (isActive[rightInterval])
				numInterval++;
			else
				break;
		}
		return numInterval;
	}
};

class Protein_uPlus3sigma : public Protein {
public:
	void setActive();
};

template <class ProteinType>
class ProteinVec {
public:
	std::vector<Protein*>	ProteinVex;
	int geneNum;
public:
	ProteinVec() {
		geneNum = 0;
	}

	~ProteinVec() {
		for (size_t i = 0; i < ProteinVex.size(); ++i) {
			if (ProteinVex[i] != NULL)
				delete ProteinVex[i];
		}
		ProteinVex.clear();
		geneNum = 0;
	}

	//���������ת����SampleNum��ʱ���Ļ��Ե����ʼ���
	ProteinVec(const char* fromFileName) {
		//		cout <<"load expression file!..."<<endl;
				//��ȡexpress�����û���
		std::ifstream InFile;
		InFile.open(fromFileName);
		if (!InFile)
		{
			std::cout << "can not open the file " << fromFileName << std::endl;
			return;
		}
		string at;
		while (!InFile.eof()) {
			ProteinType exp;
			InFile >> at;
			InFile >> exp.name;
			for (int n_interval = 0;n_interval < SampleNum;n_interval++) {
				InFile >> exp.expValue[n_interval];
			}
			exp.everActive = false;//Ĭ������Ϊδ����
			exp.setActive();
			Protein *p = new Protein(exp);
			ProteinVex.push_back(p);
		}
		geneNum = ProteinVex.size();
		if (InFile)
			InFile.close();
	}



	void output(const char*  toFileArch) {
		//���36�����Ե����ʼ��ϸ�ʽ��IntervalActiveNodes_k
		char ch_k[3];
		string str_k;
		int proteinNum = 0;
		for (int k = 1;k <= SampleNum;k++) {
			string toFileName(&toFileArch[0], &toFileArch[strlen(toFileArch)]);
			_itoa_s(k, ch_k, 3, 10);
			str_k = ch_k;
			toFileName += ("IntervalActiveNodes_" + str_k + ".txt");
			std::ofstream OutFile;
			OutFile.open(toFileName);
			if (!OutFile)
			{
				std::cout << "Can't Create Output File_" << k << "  " << std::endl;
				return;
			}
			for (size_t j = 0;j < ProteinVex.size();j++)
			{
				if (ProteinVex[j]->isActive[k - 1] == true)
				{
					proteinNum++;
					OutFile << ProteinVex[j]->name << std::endl;
				}
			}
			if (OutFile)
				OutFile.close();
		}
		//		cout << "ƽ��ÿ��interval�Ļ��Խڵ�����" << proteinNum / SampleNum << endl;

				//�����еĽڵ�ƽ������ʱ�����
		double ave = 0;
		for (int k = 1;k <= SampleNum;k++) {
			for (size_t j = 0;j < ProteinVex.size();j++)
			{
				if (ProteinVex[j]->isActive[k - 1] == true)
				{
					ave++;
				}
			}
		}
		ave /= ProteinVex.size();
		//		cout << "�����еĽڵ�ƽ������ʱ�����Ϊ��" << ave << endl;

				//���������δ���ĵ�����
		std::ofstream OutFile;
		string file = toFileArch;
		file += "unexpress_Proteins.txt";
		OutFile.open(file);
		for (size_t j = 0;j < ProteinVex.size();j++)
		{
			if (ProteinVex[j]->everActive == false)
			{
				OutFile << ProteinVex[j]->name << endl;
			}
		}
		OutFile.close();

		//������Ե����ʵĻ���ʱ���
		string file2 = toFileArch;
		file2 += "ActiveIntervals.txt";
		OutFile.open(file2);
		for (size_t j = 0;j < ProteinVex.size();j++)
		{
			OutFile << ProteinVex[j]->name << "\t";
			for (vector<int>::iterator iter = ProteinVex[j]->activeInterval.begin();iter != ProteinVex[j]->activeInterval.end();iter++)
				OutFile << (*iter) << "\t";
			OutFile << endl;
		}
		OutFile.close();
		return;

	}
	Protein* search(string name)const {
		for (size_t i = 0;i < ProteinVex.size();i++) {
			if (ProteinVex[i]->name == name)
			{
				return ProteinVex[i];
				break;
			}
		}
		return NULL;
	}
};

