#include <stdexcept>
#include "around.h"
#include "game.h"

namespace packman {

around::around(const packman::game& game, int x, int y)
	: game_(game)
	, x_(x)
	, y_(y)
{
}

packman::object around::operator[](int index) const
{
	switch (index) {
	case UP   : return game_.get_object(x_, y_ - 1);
	case DOWN : return game_.get_object(x_, y_ + 1);
	case LEFT : return game_.get_object(x_ - 1, y_);
	case RIGHT: return game_.get_object(x_ + 1, y_);
	default: break;
	}
	throw std::out_of_range("around::operator[]");
}

bool around::is_intersection() const
{
	return branch_count() > 2;
}

bool around::is_dead_end() const
{
	return branch_count() == 1;
}

int around::branch_count() const
{
	int count = 0;
	for (int i = DOWN; i < NONE; ++i) {
		if (can_move((*this)[i]))
			++count;
	}
	return count;
}

} // namespace packman
