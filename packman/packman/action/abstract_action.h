#ifndef PACKMAN_ACTION_ABSTRACT_ACTION_H__
#define PACKMAN_ACTION_ABSTRACT_ACTION_H__

#include "action_base.h"
#include "../common.h"

namespace packman {

// 先行宣言
class around;
class game;
class moving_object;

namespace action {

class abstract_action : public action_base {
public:
	abstract_action(const game& g);
	void doing(moving_object& enemy);
	void undo(const moving_object& enemy) {}

	const game& get_game() const;

protected:
	direction default_action(const around& ar) const;

private:
	virtual direction action_in_intersection(
		const around& ar,
		const moving_object& enemy
		) const = 0;

	const game& game_;
};

} } // namespace packman::action

#endif
