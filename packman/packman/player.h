#ifndef PACKMAN_PLAYER_H__
#define PACKMAN_PLAYER_H__

#include "moving_object.h"

namespace packman {

class player : public moving_object {
public:
	player(int x, int y);
	void undo();

	// inherit moving_object
	bool move(direction d);
	const History& get_history() const { return history_; }

private:
	bool moving(direction d);

	History history_;
};

} // namespace packman

#endif
