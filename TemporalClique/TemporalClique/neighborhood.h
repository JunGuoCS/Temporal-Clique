#include "basic\Func.h"
//#include "Interval.h"
#include "DeltaInterval.h"
#include "Vertex_Interval.h"

class neighborhood
{
	int delta;
	map<pair<int,int>, vector<Interval>> deltaNeighbors;
public:
	void init(int totalStart, int totalEnd, int delta, map<pair<int, int>, set<int>> E);
	map<int, vector<Interval>> cut(pair<int, Interval> v_i, map<int, vector<Interval>> P, map<int, set<int>> &V,set<int> &Pmax);
	vector<Interval> deltaIntersection(int vStart,int vEnd,vector<Interval> list1, vector<Interval> list2, bool &Pmax);
	void computePivotInformation(map<int, vector<Interval>> P, map<Vertex_Interval, vector<Vertex_Interval>> &pivot, vector<DeltaInterval> &pivotIntervals);//operator for key
	vector<Vertex_Interval> checkIn(int w,vector<Interval> list1,Vertex_Interval v_I);

	map<pair<int, int>, vector<Interval>> getDeltaNeighbors();
};