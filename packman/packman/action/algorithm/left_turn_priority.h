#ifndef PACKMAN_ACTION_ALGORITHM_LEFT_TURN_PRIORITY_H__
#define PACKMAN_ACTION_ALGORITHM_LEFT_TURN_PRIORITY_H__

#include <stdexcept>
#include "../../common.h"

namespace packman {
namespace action {
namespace algorithm {

struct left_turn_priority {
	template<typename Elem>
	packman::direction operator()(const Elem e, packman::direction d) const {
		// 進行方向の左を向く
		d = static_cast<direction>(d - 1);

		// 時計回りに試す
		for (int i = 0; i < NONE; ++i) {
			int tryd = (NONE + d + i) % NONE;
			if (packman::can_move(e[tryd]))
				return static_cast<packman::direction>(tryd);
		}
		throw std::logic_error("left_turn_priority");
	}
};

} } } // namespace packman::action::algorithm

#endif
