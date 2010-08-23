#include "common.h"
#include "player.h"

namespace packman {

player::player(int x, int y)
	: moving_object(x, y)
	, history_()
{
}

bool player::move(direction d)
{
	direction his = get_direction();
	bool b = moving_object::move(d);
	if (b) {
		history_.push_back(his);
	}
	return b;
}

void player::undo()
{
	if (history_.empty()) return;

	moving_object::move(double_back(get_direction()));
	moving_object::set_direction(history_.back());
	history_.pop_back();
}

} // namespace packman
