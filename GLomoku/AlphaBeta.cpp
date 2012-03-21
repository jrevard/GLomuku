#include "AlphaBeta.h"

int AlphaBeta::Search(SearchNode *origin, int depth) {
	Search(origin, depth, INT_MIN, INT_MAX, true);
}
	
int AlphaBeta::Search(SearchNode *origin, int depth, int alpha, int beta, bool maxNode) {
	if (depth == 0 || origin->IsTerminal()) return origin->ValueHeuristic();
	vector<SearchNode> children = origin->Children();
	if (maxNode) {
		for (int i=0; i < children.size(); i++) {
			SearchNode *child = &(children[i]);
			alpha = max(alpha, Search(child, depth-1, alpha, beta, false));
			if (beta <= alpha) break;
		}
		return alpha;
	} else {
		for (int i=0; i < children.size(); i++) {
			SearchNode *child = &(children[i]);
			beta = min(beta, Search(child, depth-1, alpha, beta, true));
			if (beta <= alpha) break;
		}
		return beta;
	}
}