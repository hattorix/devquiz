#ifndef PACKMAN_ACTION_L_H__
#define PACKMAN_ACTION_L_H__

#include "abstract_action.h"
#include "../common.h"
#include "../around.h"
#include "../moving_object.h"

namespace packman {

// 先行宣言
class game;
class around;

namespace action {

template<typename Policy>
class action_policy : public abstract_action {
public:
	action_policy(game& g) : abstract_action(g), impl_() {}

private:
	direction action_in_intersection(const around& ar, const moving_object& enemy) const {
		return impl_(ar, enemy.get_direction());
	}

	Policy impl_;
};

} } // namespace packman::action

#endif
