#include "Func.h"

bool cmp1(const pair<int, int> &a, const pair<int, int> &b)
{
	if (a.first < b.first)
		return true;
	else return false;
}
bool cmp2(const pair<int, int> &a, const pair<int, int> &b)
{
	if (a.second < b.second)
		return true;
	else return false;
}
bool cmpI(const Interval &a, const Interval &b)
{
	if (a.start < b.start)
		return true;
	else return false;
}


//map union
map<int, set<int>> map_union(map<int, set<int>> H1, map<int, set<int>> H2)
{
	map<int, set<int>> H;

	map<int, set<int>>::iterator it1, it2;
	for (it1= H1.begin(), it2 = H2.begin(); it1 != H1.end() && it2 != H2.end();)
	{
		if (it1->first == it2->first)
		{
			H[it1->first] = set_int_union(it1->second, it2->second);
			it1++;
			it2++;
		}
		else if (it1->first<it2->first)
		{
			H[it1->first] = it1->second;
			it1++;
		}
		else if (it1->first>it2->first)
		{
			H[it2->first] = it2->second;
			it2++;
		}
	}

	while (it1 != H1.end())
	{
		H[it1->first] = it1->second;
	}
	while (it2 != H2.end())
	{
		H[it2->first] = it2->second;
	}

	return H;
}

//map<int,int> union
map<int, int> map_union(map<int, int> H1, map<int, int> H2)
{
	map<int, int> H;
	return H;
}


//vector<pair<int,int>>  union
vector<pair<int, int>> vec_pair_union(vector<pair<int, int>> vec1, vector<pair<int, int>> vec2)
{
	vector<pair<int, int>> res;

	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	vector<pair<int, int>> tmp(vec1.size() + vec2.size());
	auto end = set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), tmp.begin());

	res.assign(tmp.begin(), end);

	return res;
}

//vector<int> union
vector<int> vec_int_union(vector<int> vec1, vector<int> vec2)
{
	vector<int> res;

	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	vector<int> tmp(vec1.size() + vec2.size());
	auto end = set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), tmp.begin());

	res.assign(tmp.begin(), end);

	return res;
}

//vector<int> intersection
vector<int> vec_int_intersection(vector<int> vec1, vector<int> vec2)
{
	vector<int> res;

	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	vector<int> tmp(vec1.size() + vec2.size());
	auto end = set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), tmp.begin());

	res.assign(tmp.begin(), end);

	return res;
}


//========================================================================================

//set<int> intersection
set<int> set_int_intersection(set<int> set1, set<int> set2)
{
	set<int> res;

	auto end = set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(res, res.begin()));

	return res;
}

//set<int> union
set<int> set_int_union(set<int> set1, set<int> set2)
{
	set<int> res;

	auto end = set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(res, res.begin()));

	return res;
}

