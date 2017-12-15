#include "basic\Func.h"

class Clique
{
public:
	set<int> nodes;
	int start;
	int end;

	Clique() :start(0), end(INT_MAX){};
	int CliqueSize();
	Clique aa();
friend	Clique addClique(Clique R, int v, int vStart, int vEnd);
};

