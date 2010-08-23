#ifndef PACKMAN_ACTION_ALGORITHM_CLOCKWISE_H__
#define PACKMAN_ACTION_ALGORITHM_CLOCKWISE_H__

#include "../../common.h"

namespace packman {
namespace action {
namespace algorithm {

struct clockwise {
	// m[direction] で、その方向のマップ要素を表す
	template<typename Elem>
	packman::direction operator()(const Elem e) const {
		for (int i = DOWN; i < NONE; ++i) {
			const packman::direction d = static_cast<packman::direction>(i);
			if (packman::can_move(e[d])) return d;
		}
		return NONE;
	}
};

} } } // namespace packman::action::algorithm

#endif
