#include<vector>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<algorithm>
#include<queue>
#include<set>
#include<hash_set>
#include<hash_map>
#include <iterator>
#include <fstream> 
#include<iostream>
#include<time.h>
#include<string>

#include"../Interval.h"

using namespace std;

//using namespace boost;


bool cmp1(const pair<int, int> &a, const pair<int, int> &b);//compare first element
bool cmp2(const pair<int, int> &a, const pair<int, int> &b);//compare second element
bool cmpI(const Interval &a, const Interval &b);

//=====================================map==================================================

//map<int, vector<int>> map_union(map<int, vector<int>> H1, map<int, vector<int>> H2);//map<int,vector<int>> union
map<int, set<int>> map_union(map<int, set<int>> H1, map<int, set<int>> H2);//map<int,set<int>> union
map<int, int> map_union(map<int, int> H1, map<int, int> H2);//map<int,int> union

//=====================================vector==================================================

vector<pair<int, int>> vec_pair_union(vector<pair<int, int>> vec1, vector<pair<int, int>> vec2);//vector<pair<int,int>>  union

vector<int> vec_int_union(vector<int> vec1, vector<int> vec2);//vector<int> union

vector<int> vec_int_intersection(vector<int> vec1, vector<int> vec2);//vector<int> intersection

//======================================set==================================================
set<int> set_int_intersection(set<int> set1, set<int> set2);//set<int> intersection

set<int> set_int_union(set<int> set1, set<int> set2);



