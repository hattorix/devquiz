#include <stdexcept>
#include "enemy.h"
#include "action/action_base.h"

namespace packman {

enemy::enemy(object type, int x, int y, action::action_base* act)
	: moving_object(x, y)
	, type_(type)
	, history_()
	, action_(act)
{
	if (!action_)
		throw std::invalid_argument("enemy::enemy");
}

enemy::~enemy()
{
	delete action_;
}

void enemy::doing()
{
	action_->doing(*this);
}

void enemy::undo()
{
	if (history_.empty()) return;

	moving_object::move(double_back(get_direction()));
	moving_object::set_direction(history_.back());
	history_.pop_back();
	action_->undo(*this);
}

bool enemy::move(direction d)
{
	direction his = get_direction();
	bool b = moving_object::move(d);
	if (b) {
		history_.push_back(his);
	}
	return b;
}

} // namespace packman
