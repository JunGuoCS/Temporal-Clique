#include "pivoting.h"

set<Vertex_Interval> pivotingOne(map<Vertex_Interval, vector<Vertex_Interval>> pivot, vector<DeltaInterval> pivotIntervals)
{
	set<Vertex_Interval> dismissElements;
	
	dismissElements.insert(pivot.begin()->second.begin(), pivot.begin()->second.end());
	//cout << "#dismissed elements:" << dismissElements.size() << endl;

	return dismissElements;
}

set<Vertex_Interval> pivotingOneMax(map<Vertex_Interval, vector<Vertex_Interval>> pivot, vector<DeltaInterval> pivotIntervals)
{
	set<Vertex_Interval> dismissElements;

	map<Vertex_Interval, vector<Vertex_Interval>>::iterator maxVI = pivot.begin();
	for (auto it = pivot.begin(); it != pivot.end(); it++)
	{
		if (it->second.size() > maxVI->second.size())
		{
			maxVI = it;
		}
	}
	dismissElements.insert(maxVI->second.begin(), maxVI->second.end());
	return dismissElements;
}
