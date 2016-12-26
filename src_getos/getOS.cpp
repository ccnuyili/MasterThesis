//#include "stdafx.h"
#include "datastruct.h"
int main(int args, char *argv[])
{
	if (args != 3)
	{
		cout << "pls input KC file and PC file!" << endl;
		return 0;
	}
	float sn = 0, sp = 0, f_measure = 0;
	int tp = 0, fp = 0, fn = 0, numKC = 0, numPC = 0, tn = 0;
	string PCfile;
	string knownComplexFile;
	istringstream istr(argv[1]);
	istr >> knownComplexFile;
	istr.clear();
	istr.str(argv[2]);
	istr >> PCfile;
	istr.clear();
	char PCInformationFile[100] = "PC_info.txt";
	char KCInformationFile[100] = "KC_info.txt";
	char osPCfile[100];
	strcpy(osPCfile, PCfile.c_str());
	osPCfile[strlen(osPCfile) - 4] = '\0';
	strcat(osPCfile, "_PC_OS.txt");
	char osKCfile[100];
	strcpy(osKCfile, PCfile.c_str());
	osKCfile[strlen(osKCfile) - 4] = '\0';
	strcat(osKCfile, "_KC_OS.txt");
	ComplexSet complexPredict;
	readComplexfile(complexPredict, PCfile);
	numPC = complexPredict.cliqueVex.size();
	ComplexSet complexKnown;
	readComplexfile(complexKnown, knownComplexFile);
	numKC = complexKnown.cliqueVex.size();	
	cout<<"osTV\tSN\tSP\tF-Measure\n";
	for(tvOS=0.2;tvOS<=1.0;tvOS+=0.1){
		tp = getPredictComplexOS(complexPredict, complexKnown, PCfile, PCInformationFile, osPCfile);
		tn = getKnownComplexOS(complexKnown, complexPredict, PCfile, KCInformationFile, osKCfile);
		fn = numKC - tn;
		fp = numPC - tp;
		sn = (float)tp / (float)(tp + fn);
		sp = (float)tp / (float)(tp + fp);
		f_measure = ((2 * sn*sp) / (sn + sp));
		cout << tvOS << "\t" << sn << "\t" << sp << "\t" << f_measure << endl;
	}	
	return 0;
}

