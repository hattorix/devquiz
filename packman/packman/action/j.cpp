#include "j.h"
#include "../around.h"
#include "../moving_object.h"
#include "algorithm/left_turn_priority.h"
#include "algorithm/right_turn_priority.h"

using namespace packman;
using namespace packman::action::algorithm;

namespace packman {
namespace action {

struct j::Pimpl {
	mutable int is_first;
	left_turn_priority left;
	right_turn_priority right;
};

j::j(game& game)
	: abstract_action(game)
	, pimpl_(new Pimpl())
{
}

j::j(const j& r)
	: abstract_action(r.get_game())
	, pimpl_(new Pimpl())
{
}

j::~j()
{
	delete pimpl_;
}

j& j::operator=(const j& r)
{
	pimpl_->is_first = r.pimpl_->is_first;
	return *this;
}

void j::undo(const moving_object& enemy)
{
	around ar(get_game(), enemy.get_x(), enemy.get_y());
	if (ar.is_intersection()) {
		pimpl_->is_first = 1 - pimpl_->is_first;
	}
}

direction j::action_in_intersection(const around& ar, const moving_object& enemy) const
{
	int tmp = pimpl_->is_first;
	pimpl_->is_first = 1 - tmp;
	if (tmp) {
		return pimpl_->right(ar, enemy.get_direction());
	} else {
		return pimpl_->left(ar, enemy.get_direction());
	}
}

} } // namespace packman::action
