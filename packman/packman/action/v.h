#ifndef PACKMAN_ACTION_V_H__
#define PACKMAN_ACTION_V_H__

#include "../common.h"
#include "abstract_action.h"

namespace packman {

// 先行宣言
class game;
class moving_object;

namespace action {

class v : public abstract_action {
public:
	v(game& game);
	v(const v& r);
	~v();
	v& operator=(const v&);

private:
	direction action_in_intersection(const around& ar, const moving_object& enemy) const;

	struct Pimpl;
	Pimpl* pimpl_;
};

} } // namespace packman::action

#endif
