#include <stdexcept>
#include "action_policy.h"
#include "factory.h"
#include "h.h"
#include "j.h"
#include "v.h"
#include "../game.h"
#include "algorithm/left_turn_priority.h"
#include "algorithm/right_turn_priority.h"

namespace packman {
namespace action {

action_base* create_action(packman::object o, game& g)
{
	switch (o) {
	case ENEMY_V:
		return new v(g);
	case ENEMY_H:
		return new h(g);
	case ENEMY_L:
		return new action_policy<algorithm::left_turn_priority>(g);
	case ENEMY_R:
		return new action_policy<algorithm::right_turn_priority>(g);
	case ENEMY_J:
		return new j(g);
	default:
		break;
	}
	throw std::invalid_argument("packman::action::create_action()");
}

} } // namespace packman::action
