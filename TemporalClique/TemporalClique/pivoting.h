#include "Vertex_Interval.h"
#include "DeltaInterval.h"
#include "basic\func.h"

set<Vertex_Interval> pivotingOne(map<Vertex_Interval, vector<Vertex_Interval>> pivot, vector<DeltaInterval> pivotIntervals);
set<Vertex_Interval> pivotingOneMax(map<Vertex_Interval, vector<Vertex_Interval>> pivot, vector<DeltaInterval> pivotIntervals);
//set<Vertex_Interval> pivotingOptimal(map<Vertex_Interval, vector<Vertex_Interval>> pivot, vector<DeltaInterval> pivotIntervals);
