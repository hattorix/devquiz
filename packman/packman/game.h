#ifndef PACKMAN_GAME_H__
#define PACKMAN_GAME_H__

#include <vector>
#include <iosfwd>
#include "common.h"

namespace packman {

// 先行宣言
class player;
class moving_object;
class enemy;
namespace searcher {
class breadth_first;
}

class game {
public:
	friend class searcher::breadth_first;

	enum status {
		PLAYING,
		GAME_OVER,
		LIMIT_OVER,
		BEAT_THE_GAME,
	};

	enum action_result {
		QUIT,
		CONTINUE,
		SUCCESS,
		ERROR,
	};

	game();
	~game();
	void load(std::istream& ifs);
	void start();

	const moving_object* get_player() const;
	std::vector<enemy*>& get_enemies() { return enemies_; }
	object get_object(int x, int y) const;
	int get_width() const { return width_; }
	int get_height() const { return height_; }

protected:
	void on_paint(status st) const;
	int on_action(status st, int input);
	status on_turn_end();

private:
	void load_header(std::istream& ifs);
	void load_field(std::istream& ifs);
	void init_objects();
	bool in_range(int x, int y) const;
	bool can_move(int x, int y) const;

	typedef std::vector<object> Field;
	typedef std::vector<char> GetdotHistory;
	typedef std::vector<enemy*> Enemies;

	bool init_;
	int width_;
	int height_;
	int limit_;
	Field field_;
	GetdotHistory getdot_; // DOT の回収履歴
	player* player_;
	Enemies enemies_;

	// コピー禁止
	game(const game&);
	void operator=(const game&);
};

} // namespace packman

#endif
