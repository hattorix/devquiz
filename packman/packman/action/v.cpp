#include "v.h"
#include "../around.h"
#include "../moving_object.h"
#include "../game.h"
#include "algorithm/relativity.h"

using namespace packman;
using namespace packman::action::algorithm;

namespace packman {
namespace action {

struct v::Pimpl {
	relativity<RIGHT, LEFT> hori;
	relativity<DOWN, UP> vert;
};

v::v(game& game)
	: abstract_action(game)
	, pimpl_(new Pimpl())
{
}

v::v(const v& r)
	: abstract_action(r.get_game())
	, pimpl_(new Pimpl())
{
}

v::~v()
{
	delete pimpl_;
}

v& v::operator=(const v&)
{
	return *this;
}

direction v::action_in_intersection(const around& ar, const moving_object& enemy) const
{
	const moving_object* p = get_game().get_player();

	int dy = p->get_y() - enemy.get_y();
	direction d = pimpl_->vert(ar, dy);
	if (d != NONE) {
		return d;
	}

	int dx = p->get_x() - enemy.get_x();
	d = pimpl_->hori(ar, dx);
	if (d != NONE) {
		return d;
	}

	return abstract_action::default_action(ar);
}

} } // namespace packman::action
