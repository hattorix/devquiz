#include <algorithm>
#include <iterator>
#include <stack>
#include <iostream>
#include <curses.h>
#include "breadth_first.h"
#include "../game.h"
#include "../player.h"
#include "../around.h"
#include "../common.h"

using namespace std;
using namespace packman;

namespace packman {
namespace searcher {

breadth_first::breadth_first(game& g)
	: game_(g)
{
}

void breadth_first::run()
{
	const player& pl = *game_.player_;
	vector<History> results;
	stack<int> searcher;
	searcher.push(DOWN);

	game::status st = game::PLAYING;
	while (!searcher.empty()) {
		around ar(game_, pl.get_x(), pl.get_y());

		for (int& i = searcher.top(); i < NONE; ++i) {
			// 移動
			direction d = static_cast<direction>(i);
			int result = game_.on_action(st, direction_to_char(d));
			if (result == game::ERROR) continue;

			// 各種判定
			st = game_.on_turn_end();
			if (st == game::PLAYING) {
				++i;
				searcher.push(DOWN);
				break;
			} else if (st == game::BEAT_THE_GAME) {
				results.push_back(pl.get_history());
				game_.on_action(st, 'z');
				st = game::PLAYING;
			} else if (st == game::GAME_OVER || st == game::LIMIT_OVER) {
				game_.on_action(st, 'z');
				st = game::PLAYING;
			}
		}
		if (searcher.top() >= NONE) {
			searcher.pop();
			game_.on_action(st, 'z');
		}
	}
	print_result(results);
}

void breadth_first::print_result(const vector<History>& results)
{
	for (vector<History>::const_iterator it = results.begin();
		 it != results.end(); ++it) {
		std::cout << "count[" <<  it->size() << "]\n";
		for (History::const_iterator p = it->begin();
			 p != it->end(); ++p) {
			cout << direction_to_char(*p);
		}
		cout << '\n';
	}
}

} } // namespace packman::searcher
