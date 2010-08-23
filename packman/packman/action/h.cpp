#include "h.h"
#include "../around.h"
#include "../game.h"
#include "../moving_object.h"
#include "algorithm/relativity.h"

using namespace packman;
using namespace packman::action::algorithm;

namespace packman {
namespace action {

struct h::Pimpl {
	relativity<RIGHT, LEFT> hori;
	relativity<DOWN, UP> vert;
};

h::h(game& game)
	: abstract_action(game)
	, pimpl_(new Pimpl())
{
}

h::h(const h& r)
	: abstract_action(r.get_game())
	, pimpl_(new Pimpl())
{
}

h::~h()
{
	delete pimpl_;
}

h& h::operator=(const h&)
{
	return *this;
}

direction h::action_in_intersection(const around& ar, const moving_object& enemy) const
{
	const moving_object* p = get_game().get_player();

	int dx = p->get_x() - enemy.get_x();
	direction d = pimpl_->hori(ar, dx);
	if (d != NONE) {
		return d;
	}

	int dy = p->get_y() - enemy.get_y();
	d = pimpl_->vert(ar, dy);
	if (d != NONE) {
		return d;
	}

	return abstract_action::default_action(ar);
}

} } // namespace packman::action
