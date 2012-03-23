#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class SearchNode
{
	public:
	virtual bool IsTerminal() = 0;
	virtual float ValueHeuristic() = 0;
	virtual vector<SearchNode*> Children() = 0;
};

class AlphaBeta
{
	public:
	int Search(SearchNode *origin, int depth);
	
	private:
	int Search(SearchNode *origin, int depth, int alpha, int beta, bool maxNode);
};

#endif