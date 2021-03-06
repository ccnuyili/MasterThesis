/*	Author: Li Yi
*	Email:	yili@mails.ccnu.edu.cn
*	Date:	2016.12.23
*/

#include"myheader.h"
#include "proteinExpression.h"
#include"sliceNetworksConstruction.h"
#include"dynamicCoreAttach.h"

int main()
{
	ProteinVec<Protein_uPlus3sigma> expressionMatrix_uPlus3sigma("data//Express.txt");
//	expressionMatrix_uPlus3sigma.output("data//intervalActiveProteins_uPlus3sigma//");
	
	//	u+3sigma*(1-f) krogan
//	sliceSet sliceNetwork("data//krogan_extended2006.txt", expressionMatrix_uPlus3sigma);
//	sliceNetwork.output("data//krogan_extended_interval_ppi_uPlus3sigma//");
//	DyCoreAttach algo("data//krogan_extended_interval_ppi_uPlus3sigma//", \
		"data//krogan_extended_res_uPlus3sigma//", expressionMatrix_uPlus3sigma);


	//	u+3sigma*(1-f) DIP
//	sliceSet sliceNetwork2("data//DIP.txt", expressionMatrix_uPlus3sigma);
//	sliceNetwork2.output("data//DIP_interval_ppi_uPlus3sigma//");

	DyCoreAttach algo2("data//DIP_interval_ppi_uPlus3sigma//", \
		"data//DIP_res_uPlus3sigma//", expressionMatrix_uPlus3sigma);

	return 0;
}

