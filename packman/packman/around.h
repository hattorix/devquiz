#ifndef PACKMAN_AROUND_H__
#define PACKMAN_AROUND_H__

#include "common.h"

namespace packman {

// æséŒ¾
class game;

class around {
public:
	around(const packman::game& game, int x, int y);
	packman::object operator[](int index) const;
	bool is_intersection() const;
	bool is_dead_end() const;

private:
	int branch_count() const;

	const packman::game& game_;
	const int x_;
	const int y_;
};

} // namespace packman

#endif
