#ifndef PACKMAN_ACTION_ALGORITHM_RELATIVITY_H__
#define PACKMAN_ACTION_ALGORITHM_RELATIVITY_H__

#include "../../common.h"

namespace packman {
namespace action {
namespace algorithm {

template<int PLUS, int MINUS>
struct relativity {
	template<typename Elem>
	packman::direction operator()(const Elem e, int dy) const {
		if (dy < 0) {
			if (packman::can_move(e[MINUS])) {
				return static_cast<packman::direction>(MINUS);
			}
		} else if (dy > 0) {
			if (packman::can_move(e[PLUS])) {
				return static_cast<packman::direction>(PLUS);
			}
		}
		return NONE;
	}
};

} } } // namespace packman::action::algorithm

#endif
