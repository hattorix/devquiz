#ifndef PACKMAN_MOVING_OBJECT_H__
#define PACKMAN_MOVING_OBJECT_H__

#include <list>
#include <utility>
#include "common.h"

namespace packman {

typedef std::list<direction> History;
typedef std::pair<int, int> position;

class moving_object {
public:
	moving_object(int x, int y);
	virtual ~moving_object() {}
	virtual bool move(direction d);
	virtual position get_latest_position() const;
	virtual bool same_position(const position& other ) const;
	virtual bool same_position(const moving_object& other) const;
	int get_x() const { return x_; }
	int get_y() const { return y_; }
	direction get_direction() const { return direction_; }

protected:
	void set_direction(direction d) { direction_ = d; }

private:
	int x_;
	int y_;
	direction direction_;
};

} // namespace packman

#endif

