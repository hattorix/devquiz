#include "moving_object.h"

namespace packman {

moving_object::moving_object(int x, int y)
	: x_(x)
	, y_(y)
	, direction_(NONE)
{
}

bool moving_object::move(direction d)
{
	switch (d) {
	case UP   : --y_; break;
	case DOWN : ++y_; break;
	case LEFT : --x_; break;
	case RIGHT: ++x_; break;
	case HOLD : break;
	default: return false;
	}
	direction_ = d;
	return true;
}

position moving_object::get_latest_position() const
{
	moving_object tmp(*this);
	tmp.move(double_back(direction_));
	return std::make_pair(tmp.x_, tmp.y_);
}

bool moving_object::same_position(const position& other) const
{
	return this->get_x() == other.first
		&& this->get_y() == other.second;
}

bool moving_object::same_position(const moving_object& other) const
{
	return same_position(std::make_pair(other.x_, other.y_));
}

} // namespace packman
