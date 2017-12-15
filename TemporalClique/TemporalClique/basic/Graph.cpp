/*
	Graph Implement
	Write by:Jason
	Date:2016-9-20
*/
#include "Graph.h"
#include <sstream>

//Graph::Graph(int n, int m)
void Graph::init(int n, int m)
{
	edge_num = m;
	node_num = n;
	totalStart = INT_MAX;
	totalEnd = INT_MIN;

	int t,u, v;
	for (int edge_i = 0; edge_i < edge_num; edge_i++)
	{
		cin >>t>> u >> v;
		V[u].insert(v);
		V[v].insert(u);
		E[make_pair(u, v)].insert(t);//time
		totalStart = min(t, totalStart);
		totalEnd = max(t, totalEnd);
	}
}

void Graph::init(string fileAddress)
{
	edge_num = 0;
	node_num = 0;
	totalStart = INT_MAX;
	totalEnd = INT_MIN;

	int t,u, v;//node
	string line;

	ifstream in(fileAddress);
	
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	cout << "Loading Data..." << endl;
	while (!in.eof())
	{
		getline(in,line,'\n');
		istringstream is(line);
		is >>t>> u >> v;

		//put edge
		if (u < v)
		{
			E[make_pair(u, v)].insert(t);
		}
		else if (u>v)
		{
			E[make_pair(v, u)].insert(t);
		}

		//put node
		if (u != v)
		{
			V[u].insert(v);
			V[v].insert(u);
		}
		totalStart = min(t, totalStart);
		totalEnd = max(t, totalEnd);
	}

	node_num = V.size();
	edge_num = E.size();

	in.close();
	cout << "Finish Loading!" << endl;
	this->fileAddress=fileAddress;
	fileName = fileAddress.substr(fileAddress.find_last_of('/') + 1);
	//out.close();
}

























