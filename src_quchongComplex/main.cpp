
#include"datastruct.h"
int main(int args,char* argv[])
{
	if (args != 3) {
		cout << "para error!" << endl;
		return 0;
	}
	istringstream istr(argv[1]);
	string file;
	istr >> file;
	ComplexSet complexes;
	readComplexfile(complexes,file);
	FilterClique(complexes);
	istr.clear();
	istr.str(argv[2]);
	string tofile;
	istr >> tofile;
	outPutComplex(complexes, tofile);
	return 0;
}

