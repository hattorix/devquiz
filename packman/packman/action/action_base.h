#ifndef PACKMAN_ACTION_ACTION_BASE_H__
#define PACKMAN_ACTION_ACTION_BASE_H__

namespace packman {

// 先行宣言
class moving_object;

namespace action {

class action_base {
public:
	virtual ~action_base() {};
	virtual void doing(moving_object& enemy) = 0;
	virtual void undo(const moving_object& enemy) = 0;
};

} } // namespace packman::action

#endif

