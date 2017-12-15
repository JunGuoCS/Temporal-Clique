#pragma once
#include<vector>
#include"Vertex_Interval.h"
class DeltaInterval
{
public:
	int v;
	int start;
	int end;
	std::vector<Vertex_Interval> dismissElements;
	DeltaInterval(Vertex_Interval v_I, std::vector<Vertex_Interval> d) :v(v_I.v), start(v_I.interval.start), end(v_I.interval.end){}
};