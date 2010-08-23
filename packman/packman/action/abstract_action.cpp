#include <stdexcept>
#include "abstract_action.h"
#include "../around.h"
#include "../game.h"
#include "../moving_object.h"
#include "algorithm/clockwise.h"

using namespace packman;
using namespace packman::action::algorithm;

namespace packman {
namespace action {

abstract_action::abstract_action(const game& g)
	: game_(g)
{
}

const game& abstract_action::get_game() const
{
	return game_;
}

void abstract_action::doing(moving_object& enemy)
{
	int d = NONE;
	around ar(game_, enemy.get_x(), enemy.get_y());
	if (enemy.get_direction() == NONE) {
		// 初回の行動
		d = default_action(ar);
	} else if (ar.is_intersection()) {
		// 交差点
		d = action_in_intersection(ar, enemy);
	} else if (ar.is_dead_end()) {
		// 行き止まり
		d = default_action(ar);
	} else if (can_move(ar[enemy.get_direction()])) {
		// 直進
		d = enemy.get_direction();
	} else if (can_move(ar[(enemy.get_direction() + 1) % NONE])) {
		// 左折
		d = (enemy.get_direction() + 1) % NONE;
	} else if (can_move(ar[(enemy.get_direction() + 3) % NONE])) {
		// 右折
		d = (enemy.get_direction() + 3) % NONE;
	} else {
		throw std::logic_error("移動できない＞＜");
	}
	enemy.move(static_cast<direction>(d));
}

direction abstract_action::default_action(const around& ar) const
{
	clockwise c;
	return c(ar);
}

} } // namespace packman::action
