#include "basic\Graph.h"
#include "Clique.h"
#include "neighborhood.h"
#include "pivoting.h"

class CliqueMaster :public Graph
{
	int pivot_lvl;
	int delta;
	neighborhood deltaN;
	vector<Clique> maximalClique;
	vector<Clique> allClique;
	void BK(Clique R, map<int, vector<Interval>> P,set<int> Pmax, map<int, vector<Interval>> X,set<int> Xmax,int minsup);
public:
	CliqueMaster() :pivot_lvl(0){}
	void setPivotLvl(int pl){ pivot_lvl = pl; };
	void setDelta(int d);

	//finding all temporal clique
	void findTemporalClique(int minsup);
	
	//experiment
	int getMaximalCliqueNum();
	int getAllCliqueNum();
	void test();
	void saveResult();
};