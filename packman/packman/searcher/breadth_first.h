#ifndef PACKMAN_SEARCHER_BREADTH_FIRST_H__
#define PACKMAN_SEARCHER_BREADTH_FIRST_H__

#include <vector>
#include "../moving_object.h"

namespace packman {

// 先行宣言
class game;

namespace searcher {

class breadth_first {
public:
	breadth_first(game& g);
	void run();
	void print_result(const std::vector<packman::History>& results);

private:
	game& game_;
};

} } // namespace packman::searcher

#endif
