#ifndef PACKMAN_COMMON_H__
#define PACKMAN_COMMON_H__

#include <cctype>

namespace packman {

// マップの要素
typedef char object;

// 方向
enum direction {
	// その場に留まる
	HOLD = -1,

	// +1 するごとに、時計回りに回転するように配置
	DOWN = 0,
	LEFT,
	UP,
	RIGHT,

	// 不定値
	NONE
};

// マップの要素
enum {
	WALL = '#',
	DOT = '.',
	SPACE = ' ',
	PLAYER = '@',
	ENEMY_V = 'V',
	ENEMY_H = 'H',
	ENEMY_L = 'L',
	ENEMY_R = 'R',
	ENEMY_J = 'J',

	// 範囲外
	OUTSIDE = -1
};

inline direction double_back(direction d)
{
	if (DOWN <= d && d <= RIGHT)
		return static_cast<direction>((d + 2) % NONE);
	return d;
}

inline bool can_move(object o)
{
	return o == SPACE || o == DOT;
}

inline bool is_moving_object(object o)
{
	return o == PLAYER
		|| o == ENEMY_V
		|| o == ENEMY_H
		|| o == ENEMY_L
		|| o == ENEMY_R
		|| o == ENEMY_J;
}

inline direction char_to_direction(char input)
{
	switch (toupper(input)) {
	case 'K': return UP;
	case 'J': return DOWN;
	case 'H': return LEFT;
	case 'L': return RIGHT;
	case '.': return HOLD;
	default: break;
	}
	return NONE;
}

inline char direction_to_char(direction d)
{
	switch (d) {
	case UP: return 'k';
	case DOWN: return 'j';
	case LEFT: return 'h';
	case RIGHT: return 'l';
	case HOLD: return '.';
	default: break;
	}
	return ' ';
}

} // namespace packman

#endif
