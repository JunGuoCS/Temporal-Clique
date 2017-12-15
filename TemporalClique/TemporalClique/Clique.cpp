#include "Clique.h"

Clique addClique(Clique R,int v, int vStart, int vEnd)
{
	Clique empty;
	
	R.nodes.insert(v);
	if (vStart <= vEnd)
	{
		R.start = vStart;
		R.end = vEnd;
	}
	
	return R;

}

int Clique::CliqueSize()
{
	return nodes.size(); 
}
