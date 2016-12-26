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
		{	exp.mark=false;//Ĭ������Ϊδ����
			SetActive1(&exp);
			expSet.ExpVex.push_back(exp);
		}
	}
	expSet.expNum=expSet.ExpVex.size();
	if(InFile)InFile.close();
}

//u+sigma
void SetActive1( Expression *p){
	//�жϵ�����P�ı��ֵ��ʱ��interval�Ƿ񳬹�������ֵ
	int interval;
	double u=0,sigma=0;
	for(int i=0;i<36;i++){
		u+=p->expValue[i];	
	}
	u/=36;

	for(int i=0;i<36;i++){
		sigma+=(p->expValue[i]-u)*(p->expValue[i]-u);
	}
	sigma/=35; //ƽ��
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
	//������Եĵ����ʼ��ϵ�n_subPINs���ļ�
	//����ļ�����ʽ��_NodeSet_atInterval_k
	char stt[5];
	char  toFileName[100];
	int num=0;//ͳ�����κ�ʱ�̶�û�����ĸ���
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

