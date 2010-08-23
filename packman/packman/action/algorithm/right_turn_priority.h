#ifndef PACKMAN_ACTION_ALGORITHM_RIGHT_TURN_PRIORITY_H__
#define PACKMAN_ACTION_ALGORITHM_RIGHT_TURN_PRIORITY_H__

#include <stdexcept>
#include "../../common.h"

namespace packman {
namespace action {
namespace algorithm {

struct right_turn_priority {
	template<typename Elem>
	packman::direction operator()(const Elem e, packman::direction d) const {
		// 進行方向の右を向く
		d = static_cast<direction>(d + 1);

		// 反時計回りに試す
		for (int i = 0; i < NONE; ++i) {
			int tryd = (NONE + d - i) % NONE;
			if (packman::can_move(e[tryd]))
				return static_cast<packman::direction>(tryd);
		}
		throw std::logic_error("right_turn_priority");
	}
};

} } } // namespace packman::action::algorithm

#endif
