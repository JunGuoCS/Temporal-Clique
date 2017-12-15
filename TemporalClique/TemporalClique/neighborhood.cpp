#include "neighborhood.h"

//void neighborhood::init(int totalStart, int totalEnd, int delta, map<pair<int, int>, set<int>> E)
//{
//	int start, end;
//	for (auto iter = E.begin(); iter != E.end(); iter++)
//	{
//		pair<int, int> u_v = iter->first;
//		set<int> times = iter->second;
//		Interval interval;
//		for (auto i_time = times.begin(); i_time != times.end(); i_time++)
//		{
//			int t = *i_time;
//			if (i_time == times.begin())
//			{
//				start = max(totalStart, t - delta + 1);
//				end = min(totalEnd, t + delta - 1);
//			}
//			else
//			{
//				if (t<start||t>end)
//				{
//					interval.setInterval(start, end);
//					deltaNeighbors[u_v].push_back(interval);
//				}
//				start = min(start,t - delta + 1);
//				end = max(end,t + delta - 1);
//			}
//		}
//		interval.setInterval(start, end);
//		deltaNeighbors[u_v].push_back(interval);
//
//	}
//}


void neighborhood::init(int totalStart, int totalEnd, int delta, map<pair<int, int>, set<int>> E)
{
	this->delta = delta;
	int start, end;
	for (auto iter = E.begin(); iter != E.end(); iter++)
	{
		pair<int, int> u_v = iter->first;
		set<int> times = iter->second;
		Interval interval;

		start = max(totalStart, *times.begin() - delta);
		//end = min(totalEnd, start + 2 * delta);
		end = min(totalEnd, *times.begin() + delta);

		for (auto i_time = times.begin(); i_time != times.end(); i_time++)
		{
			int t = *i_time;

			//if (t > (end + 1))
			if (t > end )
			{
				interval.setInterval(start, end);
				deltaNeighbors[u_v].push_back(interval);
				start = max(totalStart, t - delta);
			}
			end = min(totalEnd, t + delta);

		}
		interval.setInterval(start, end);
		deltaNeighbors[u_v].push_back(interval);
		
	}
}

map<int, vector<Interval>> neighborhood::cut(pair<int, Interval> v_i, map<int, vector<Interval>> P, map<int, set<int>> &V, set<int> &res_Pmax)
{
	int v = v_i.first;
	Interval interval = v_i.second;

	map<int, vector<Interval>> P_new;
	set<int> Pmax;

	//only neighbors
	auto P_begin = P.begin();
	auto P_end = P.end();
	for (auto i_w = P_begin; i_w != P_end; i_w++)
	{
		int w = i_w->first;
		if (V[v].find(w) != V[v].end())
		{
			pair<int, int> v_w = v<w ? make_pair(v, w) : make_pair(w, v);

			bool P_supp;
			vector<Interval> tmp = deltaIntersection(interval.start, interval.end, P[w], deltaNeighbors[v_w],P_supp);
			if (tmp.size()>0)
			{
				P_new[w] = tmp;
			}
			if (P_supp)
			{
				Pmax.insert(w);
			}
		}
		
	}

	res_Pmax.insert(Pmax.begin(), Pmax.end());

	return P_new;
}

vector<Interval> neighborhood::deltaIntersection(int vStart,int vEnd,vector<Interval> list1, vector<Interval> list2, bool &Pmax)
{
	vector<Interval> list_new;

	sort(list1.begin(), list1.end(), cmpI);
	sort(list2.begin(), list2.end(), cmpI);

	int list1_curr = 0;
	int list2_curr = 0;

	while (list1_curr < list1.size() && list2_curr < list2.size())
	{
		Interval interval1 = list1[list1_curr];
		int i1_start = interval1.start;
		int i1_end = interval1.end;
		if (vEnd < (i1_start + delta))
			break;
		if (i1_end < (vStart + delta))
		{
			list1_curr += 1;
			continue;
		}
		else
		{
			while (list2_curr < list2.size())
			{
				Interval interval2 = list2[list2_curr];
				int i2_start = interval2.start;
				int i2_end = interval2.end;

				if (i2_end < (vStart + delta))
				{
					list2_curr += 1;
					continue;
				}
				if (vEnd < (i2_start + delta))
				{
					list2_curr = list2.size();//in order to break outter FOR
					break;
				}
				if (i2_end < (i1_start + delta))
				{
					list2_curr += 1;
					continue;
				}

				if (i2_start<i1_start&&i2_end>i1_start&&i2_end <= i1_end)
				{
					int a = max(i1_start, vStart);
					int b = min(i2_end, vEnd);
					if (b - a >= delta)
					{
						Interval a_b(a, b);
						list_new.push_back(a_b);
					}
					list2_curr += 1;
					continue;
				}

				if (i2_start<i1_start&&i2_end>i1_end)
				{
					int a = max(i1_start, vStart);
					int b = min(i1_end, vEnd);
					if (b - a >= delta)
					{
						Interval a_b(a, b);
						list_new.push_back(a_b);
					}
					list1_curr += 1;
					break;
				}
				
				if (i2_start >= i1_start&&i2_end <= i1_end)
				{
					int a = max(i2_start, vStart);
					int b = min(i2_end, vEnd);
					if (b - a >= delta)
					{
						Interval a_b(a, b);
						list_new.push_back(a_b);
					}
					list2_curr += 1;
					continue;
				}

				if (i2_start >= i1_start&&i2_start<i1_end&&i2_end>i1_end)
				{
					int a = max(i2_start, vStart);
					int b = min(i1_end, vEnd);
					if (b - a >= delta)
					{
						Interval a_b(a, b);
						list_new.push_back(a_b);
					}
					list1_curr += 1;
					break;
				}

				if (i2_start >= i1_end)
				{
					list1_curr += 1;
					break;
				}

			}
		}
	}

	Pmax = false;
	if (list_new.size() == 1 && list_new[0].start == vStart&&list_new[0].end == vEnd)
	//if (list_new[0].start == vStart&&list_new[0].end == vEnd)
		Pmax = true;

	return list_new;
}

void neighborhood::computePivotInformation(map<int, vector<Interval>> P, map<Vertex_Interval, vector<Vertex_Interval>> &pivot, vector<DeltaInterval> &pivotIntervals)
{
	for (auto i_v = P.begin(); i_v != P.end(); i_v++)
	{
		int v = i_v->first;
		for (auto i_I = i_v->second.begin(); i_I != i_v->second.end(); i_I++)
		{
			Interval I = *i_I;
			Vertex_Interval v_I(v, I);
			for (auto i_w = P.begin(); i_w != P.end(); i_w++)
			{
				int w = i_w->first;
				if (w != v)
				{
					vector<Vertex_Interval> tmp=checkIn(w, i_w->second, v_I);
					if (tmp.size() > 0)
					{
						pivot[v_I].insert(pivot[v_I].end(), tmp.begin(), tmp.end());
						//pivotIntervals.push_back(DeltaInterval(v_I, pivot[v_I]));
					}
				}
			}
			if (pivot.find(v_I) != pivot.end())
			{
				pivotIntervals.push_back(DeltaInterval(v_I, pivot[v_I]));
			}
		}
	}
}

vector<Vertex_Interval> neighborhood::checkIn(int w, vector<Interval> list1, Vertex_Interval v_I)
{
	int v = v_I.v;
	Interval interval = v_I.interval;
	int start = interval.start;
	int end = interval.end;

	vector<Vertex_Interval> pivot;

	//only neighbor do
	pair<int, int> v_w=v<w?make_pair(v,w):make_pair(w,v);
	if (deltaNeighbors.find(v_w) != deltaNeighbors.end())
	{
		vector<Interval> list2=deltaNeighbors[v_w];
		sort(list1.begin(), list1.end(), cmpI);
		sort(list2.begin(), list2.end(), cmpI);

		int list1_curr = 0;
		int list2_curr = 0;

		while (list1_curr < list1.size() && list2_curr < list2.size())
		{
			int i1_start = list1[list1_curr].start;
			int i1_end = list1[list1_curr].end;
			if (end<i1_end || start>i1_start)
				break;
			else
			{
				while (list2_curr < list2.size())
				{
					int i2_start = list2[list2_curr].start;
					int i2_end = list2[list2_curr].end;

					if (i1_start >= i2_start&&i1_end <= i2_end)
					{
						pivot.push_back(Vertex_Interval(w, Interval(i1_start, i1_end)));
						list1_curr += 1;
						break;
					}
					if (i1_start<i2_start&&i1_end>i2_end)
					{
						list1_curr += 1;
						list2_curr += 1;
						break;
					}
					if (i1_start<i2_start)
					{
						list1_curr += 1;
						break;
					}
					if (i1_end>i2_end)
					{
						list2_curr += 1;
						continue;
					}
				}
			}
			
		}
	}
	return pivot;
}

map<pair<int, int>, vector<Interval>> neighborhood::getDeltaNeighbors()
{
	return deltaNeighbors;
}
