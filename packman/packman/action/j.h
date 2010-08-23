#ifndef PACKMAN_ACTION_J_H__
#define PACKMAN_ACTION_J_H__

#include "../common.h"
#include "abstract_action.h"

namespace packman {

// 先行宣言
class game;
class moving_object;

namespace action {

class j : public abstract_action {
public:
	j(game& game);
	j(const j& r);
	~j();
	j& operator=(const j& r);

	// inherit abstract_action
	void undo(const moving_object& enemy);

private:
	direction action_in_intersection(const around& ar, const moving_object& enemy) const;

	struct Pimpl;
	Pimpl* pimpl_;
};

} } // namespace packman::action

#endif
