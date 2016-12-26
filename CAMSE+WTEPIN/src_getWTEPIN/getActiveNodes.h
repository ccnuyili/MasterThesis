void LoadAndSetActive(char  fromFileName[100],ExpressionSet &expSet){
	std::ifstream InFile;
	InFile.open(fromFileName);
	void SetActive1( Expression *p);

	if (!InFile)
	{
		std::cout<<"can not open the file "<<fromFileName<<std::endl;
		return;
	}
	string at;
	while(!InFile.eof())  {
		Expression exp;
		InFile>>at;
		InFile>>exp.protein;
		for(int n_interval=0;n_interval<36;n_interval++){
			InFile>>exp.expValue[n_interval];		
		}	
		if(exp.protein!="Found"&&exp.protein!="non-annotated"&&exp.protein!="--Control")
		{	exp.mark=false;//默认设置为未激活
			SetActive1(&exp);
			expSet.ExpVex.push_back(exp);
		}
	}
	expSet.expNum=expSet.ExpVex.size();
	if(InFile)InFile.close();
}

//u+sigma
void SetActive1( Expression *p){
	//判断蛋白质P的表达值在时刻interval是否超过活性阈值
	int interval;
	double u=0,sigma=0;
	for(int i=0;i<36;i++){
		u+=p->expValue[i];	
	}
	u/=36;

	for(int i=0;i<36;i++){
		sigma+=(p->expValue[i]-u)*(p->expValue[i]-u);
	}
	sigma/=35; //平方
	sigma=sqrt(sigma); //sigma	

	for(interval=1;interval<=n_subPINs;interval++){
			if(p->expValue[interval-1]-u>sigma) { 
				p->mark=true;
				p->isActive[interval-1]=true;
			}
			else 
				p->isActive[interval-1]=false;
	}
}

void outPutActiveNodesToFile(char  fromFileName[100],ExpressionSet expSet){
	//输出活性的蛋白质集合到n_subPINs个文件
	//输出文件名格式：_NodeSet_atInterval_k
	char stt[5];
	char  toFileName[100];
	int num=0;//统计在任何时刻都没被表达的个数
	for(int k=1;k<=n_subPINs;k++){

		strcpy(toFileName,fromFileName);
		strcat(toFileName,"_NodesAtInterval_");
		itoa(k,stt,10);
		strcat(toFileName,stt);
		strcat(toFileName,".txt");
		std::ofstream OutFile;
		OutFile.open(toFileName);
		if(!OutFile)
		{
			std::cout<<"Can't Create Output File_"<<k<<"  "<<std::endl;
			return;
		}
		for(size_t j=0;j<expSet.ExpVex.size();j++)
		{	
			if(expSet.ExpVex[j].isActive[k-1]==true)
				{	
					OutFile<<expSet.ExpVex[j].protein<<std::endl;
			}
		}
		if(OutFile)
			OutFile.close();
	}
	return;
}

