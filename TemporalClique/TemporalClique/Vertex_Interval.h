#pragma once
#include "Interval.h"
class Vertex_Interval
{
public:
	int v;
	Interval interval;
	Vertex_Interval(){}
	Vertex_Interval(int in_v, Interval in_i) :v(in_v), interval(in_i){}
	bool operator < (const Vertex_Interval &vi) const		//how to make compare reasonable
	{
		
		if (v!=vi.v)
			return v < vi.v;
		else
		{
			if (interval.end != vi.interval.end)
				return interval.end < vi.interval.end;
			else
				return interval.start < vi.interval.start;
		}

	}
	//bool operator = (const Vertex_Interval &vi) const
	//{
	//	if (v == vi.v&&interval.start == vi.interval.start&&interval.end == vi.interval.end)
	//		return true;
	//	else
	//		return false;
	//}
};