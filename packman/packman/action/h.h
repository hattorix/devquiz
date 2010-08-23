#ifndef PACKMAN_ACTION_H_H__
#define PACKMAN_ACTION_H_H__

#include "../common.h"
#include "abstract_action.h"

namespace packman {

// 先行宣言
class game;
class moving_object;

namespace action {

class h : public abstract_action {
public:
	h(game& game);
	h(const h& r);
	~h();
	h& operator=(const h&);

private:
	direction action_in_intersection(const around& ar, const moving_object& enemy) const;

	struct Pimpl;
	Pimpl* pimpl_;
};

} } // namespace packman::action

#endif
