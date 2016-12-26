#include "stdafx.h"
#include"proteinExpression.h"

void Protein_uPlus3sigma::setActive() {
	//判断蛋白质P的表达值在时刻interval是否超过活性阈值
	int interval;
	double u = 0, sigma = 0;
	for (int i = 0;i < 36;i++) {
		u += expValue[i];
	}
	u /= 36;

	for (int i = 0;i < SampleNum;i++) {
		sigma += (expValue[i] - u)*(expValue[i] - u);
	}
	sigma /= 35; //平方
	double f = 1 / (1 + sigma); //sigma平方
	sigma = sqrt(sigma); //sigma	
	double active_th = u + (3 * sigma)*(1.0 - f);
	for (interval = 0;interval < SampleNum;interval++) {
		if (expValue[interval] > active_th) {
			everActive = true;
			isActive[interval] = true;
			activeInterval.push_back(interval);
		}
	}
	activeTimePointNum = activeInterval.size();
}

