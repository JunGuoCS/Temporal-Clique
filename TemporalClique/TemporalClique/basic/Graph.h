/*
	Graph definition
	Write by:Jason
	Date:2016-9-20
*/
#include "Func.h"

class Graph
{
protected:
	//variable
	int edge_num;			
	int node_num;
	int totalStart;
	int totalEnd;
	int lifetime;
	string fileAddress;
	string fileName;
	map<int, set<int>> V;	
	map<pair<int,int>, set<int>> E;				//<<u,v>,set(t)>

public:
	//Graph(int n, int m);
	//Graph(string filename);
	void init(string fileAddress);
	void init(int n, int m);

};

