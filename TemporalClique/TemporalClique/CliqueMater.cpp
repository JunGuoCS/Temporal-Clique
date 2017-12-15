#include "CliqueMaster.h"
	
clock_t findTCTime = 0;

void CliqueMaster::findTemporalClique(int minsup)
{
	Clique R;
	map<int, vector<Interval>> P,X;
	set<int> Pmax, Xmax;
	deltaN.init(totalStart,totalEnd,delta,E);

	Interval i(totalStart,totalEnd);
	for (auto it = V.begin(); it != V.end(); it++)
	{
		P[it->first].push_back(i);
		Pmax.insert(it->first);
	}
	
	//clock_t findTCTime = 0;
	findTCTime -= clock();
	BK(R, P,Pmax, X,Xmax,minsup);
	findTCTime += clock();
	cout << "Find temporal clique cost: " << (double)findTCTime / CLOCKS_PER_SEC << endl;
}


void CliqueMaster::BK(Clique R, map<int, vector<Interval>> P,set<int> Pmax, map<int, vector<Interval>> X,set<int> Xmax,int minsup)
{
	//report maximal clique
	//if (P.size() == 0 && X.size() == 0 && R.CliqueSize() >= minsup)
	if (Pmax.size() == 0 && Xmax.size() == 0 && R.CliqueSize() >= minsup)
	{
		/*cout << "Clique: ";
		for (auto it = R.nodes.begin(); it != R.nodes.end(); it++)
		{
			cout << *it << " ";
		}
		cout <<"Interval:"<<R.start<<"-"<<R.end<< endl;*/
		allClique.push_back(R);
	}
	if (P.size() == 0 && X.size() == 0 && R.CliqueSize() >= minsup)
	{
		maximalClique.push_back(R);
	}

	//pivot strategy
	set<Vertex_Interval> dismiss;
	if (pivot_lvl > 0)
	{
		map<Vertex_Interval, vector<Vertex_Interval>> pivots;
		vector<DeltaInterval> pivotIntervals;
		deltaN.computePivotInformation(P,pivots, pivotIntervals);
		if (pivots.size() > 1)
		{
			switch (pivot_lvl)
			{
			case 1:
				dismiss = pivotingOne(pivots, pivotIntervals);
				break;
			case 2:
				dismiss = pivotingOneMax(pivots, pivotIntervals);
				break;
			}
		}
		else if (pivots.size() == 1)
		{
			dismiss.insert(pivots.begin()->second.begin(), pivots.begin()->second.end());
		}
	}

	map<int, vector<Interval>> P_supp(P.begin(),P.end());//copy one for iteration
	while (P_supp.size()>0)
	{
		map<int, vector<Interval>>::iterator iter = P_supp.begin();
		int v = iter->first;
		vector<Interval> vInterval = iter->second;
	
		int VTSize = vInterval.size();
		int P_v_end=VTSize-1;

		for (int i = VTSize-1; i >= 0; i--)
		{
			//remove N_delta(v)
			Interval interval = vInterval[i];
			if (dismiss.find(Vertex_Interval(v, interval)) == dismiss.end())
			{
				//expand new Clique
				Clique R_new = addClique(R, v, interval.start, interval.end);

				//cut N(v) and P,N(v) and X
				set<int> Pmax_new, Xmax_new;
				map<int, vector<Interval>> P_new = deltaN.cut(make_pair(v, interval), P, V, Pmax_new);
				map<int, vector<Interval>> X_new = deltaN.cut(make_pair(v, interval), X, V, Xmax_new);
				BK(R_new, P_new, Pmax_new, X_new, Xmax_new,minsup);

				//exchange the end
				P[v][i] = P[v][P_v_end];
				P[v].pop_back();
				P_v_end--;

				X[v].push_back(interval);
			}
			P_supp[v].pop_back();
		}
		P_supp.erase(iter);

		if (P_v_end < 0)
		{
			P.erase(v);
		}
	}
}

void CliqueMaster::setDelta(int d)
{ 
	delta = d;
	//bound just before the first edge or beyond the last edge
	totalStart -= delta;
	totalEnd += delta;
}

int CliqueMaster::getMaximalCliqueNum()
{
	return maximalClique.size();
}
int CliqueMaster::getAllCliqueNum()
{
	return allClique.size();
}

void CliqueMaster::test()
{
	deltaN.init(totalStart,totalEnd,delta,E);

	ofstream out("Result/edgeIntervals");

	auto edgeIntervals = deltaN.getDeltaNeighbors();
	for (auto ei : edgeIntervals)
	{
		out << "{" << ei.first.first << "," << ei.first.second << "} ";
		for (auto i : ei.second)
		{
			out << "(" << i.start << "," << i.end << ") ";
		}
		out << endl;
	}
	out.close();
}

void CliqueMaster::saveResult()
{
	ofstream out1("Result/allClique_"+fileName+"_"+to_string(delta));

	int maxC = 0;
	for (auto it = allClique.begin(); it != allClique.end(); it++)
	{
		maxC = max((int)it->nodes.size(), maxC);
	}

	for (auto it = allClique.begin(); it != allClique.end(); it++)
	{
		out1 << "{";
		for (auto it2 = it->nodes.begin(); it2 != it->nodes.end(); it2++)
		{
			if (it2 == it->nodes.begin())
			{
				out1 << *it2;
			}
			else
			{
				out1 << "," << *it2;
			}
		}
		out1 << "} ("<<it->start<<","<<it->end<<")"<<endl;
	}
	out1.close();

	ofstream out2("Result/maximalClique_"+fileName+"_" + to_string(delta));

	for (auto it = maximalClique.begin(); it != maximalClique.end(); it++)
	{
		out2 << "{";
		for (auto it2 = it->nodes.begin(); it2 != it->nodes.end(); it2++)
		{
			if (it2 == it->nodes.begin())
			{
				out2 << *it2;
			}
			else
			{
				out2 << "," << *it2;
			}
		}
		out2 << "} (" << it->start << "," << it->end << ")" << endl;
	}
	out2.close();

	ofstream out3("Result/statistics_"+to_string(delta));
	//clock_t findTCTime = 0;
	out3 << "Find Temporal Clique Time: " << (double)findTCTime / CLOCKS_PER_SEC << " s" << endl;
	out3 << "Clique Number: " << allClique.size() << endl;
	out3 << "Maximum Clique: " << maxC << endl;
	out3 << "Delta: " << delta << endl;
	out3.close();
}
