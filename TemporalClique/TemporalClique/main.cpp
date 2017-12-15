//2
#include "CliqueMaster.h"

int main()
{
	CliqueMaster cm;

	cout << "1. input" << endl;
	cout << "2. read file" << endl;
	cout << "3. input file name" << endl;
	cout << "Choose:";
	int type=1;
	cin >> type;
	if (type == 1)
	{
		int n, m;
		cin >> n >> m;
		cm.init(n, m);
	}
	else if(type==2)
	{
		int datasetNum=5;
		string DatasetList[]={"out.dolphins", "Hospital.dat","high_2012.csv","Infectious.txt","dblp","dblp10","dblp20" };
		for (int i = 0; i < sizeof(DatasetList)/sizeof(DatasetList[0]); i++)
		{
			cout << "[" << i + 1 << "]" << DatasetList[i] << endl;
		}
		cout << "Which one?";
		int no = 0;
		cin >> no;
		cm.init("../../Dataset/"+DatasetList[no-1]);	
	}
	else
	{
		string in_file_add;
		cin>>in_file_add;
		cm.init(in_file_add);
	}

	cout << endl;
	cout << "Please input delta:";
	int delta = 0;
	cin >> delta;
	cm.setDelta(delta);

	cout << endl;
	cout << "0. no pivoting" << endl;
	cout << "1. pivot one" << endl;
	cout << "2. pivot one max" << endl;
	cout << "Please choose pivot:";
	int pl = 0;
	cin >> pl;
	cm.setPivotLvl(pl);

	//bool ct=true;
	//while(ct)
	//{

	//}
	int minsup=0;

	cout << endl;
	cout << "1. Find all temporal clique" << endl;
	cout << "2. Test" << endl;
	
	cout << "Input:";
	cin >> type;
	switch (type)
	{
	case 1:
		cout<<"Min Size:";
		cin>>minsup;
		cm.findTemporalClique(minsup);
		break;
	case 2:
		cm.test();
		delta = 0;
		break;
	}

	cout << cm.getAllCliqueNum() << endl;
	cout << cm.getMaximalCliqueNum() << endl;
	cm.saveResult();
}