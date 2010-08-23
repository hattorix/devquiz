#ifndef PACKMAN_ENEMY_H__
#define PACKMAN_ENEMY_H__

#include "common.h"
#include "moving_object.h"

namespace packman {
namespace action {

// 先行宣言
class action_base;

}

class enemy : public moving_object {
public:
	enemy(object type, int x, int y, action::action_base* act);
	~enemy();
	void doing();
	void undo();
	object get_type() const { return type_; }

	// inherit moving_object
	bool move(direction d);

private:
	object type_;
	History history_;
	action::action_base* action_;

	enemy(const enemy&);
	void operator=(const enemy&);
};

} // namespace packman

#endif
