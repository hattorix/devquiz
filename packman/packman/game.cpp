#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <curses.h>
#include "enemy.h"
#include "game.h"
#include "moving_object.h"
#include "player.h"
#include "action/action_base.h"
#include "action/factory.h"

using namespace std;
using namespace packman::action;

namespace packman {

namespace {

bool is_dot(object o)
{
	return o == DOT;
}

} // unnamed namespace

game::game()
	: init_(false)
	, width_(0)
	, height_(0)
	, limit_(0)
	, field_(0)
	, getdot_(0)
	, player_(0)
	, enemies_(0)
{
}

game::~game()
{
	if (player_)
		delete player_;

	for (Enemies::iterator it = enemies_.begin(); it != enemies_.end(); ++it) {
		delete *it;
	}
}

// マップファイルの読み込み
void game::load(istream& ifs)
{
	load_header(ifs);
	load_field(ifs);
	init_objects();

	init_ = true;
}

// ヘッダー部の読み込み
void game::load_header(istream& ifs)
{
	ifs >> limit_;
	if (ifs.fail()) throw invalid_argument("フィールドファイルの[制限時間]が不正です。");
	ifs >> width_ >> height_;
	if (ifs.fail()) throw invalid_argument("フィールドファイルの[行、列]が不正です。");
}

// フィールド部の読み込み
void game::load_field(istream& ifs)
{
	// サイズ設定
	field_.resize(width_ * height_);

	// field_ にコピー
	int y = 0;
	string line;
	while (getline(ifs, line)) {
		if (line.empty()) continue;
		if (static_cast<int>(line.size()) != width_)
			throw runtime_error("フィールドファイルの[列数]が不正です。");

		copy(line.begin(), line.end(), &field_[y++ * width_]);
	}
	if (y != height_) {
		throw runtime_error("フィールドファイルの[行数]が不正です。");
	}
}

// プレイヤーと敵の生成
void game::init_objects()
{
	for (Field::iterator it = field_.begin(); it != field_.end(); ++it) {
		if (!is_moving_object(*it)) continue;

		int index = it - field_.begin();
		int x = index % width_;
		int y = index / width_;

		if (*it == PLAYER) {
			// プレイヤー生成
			if (!player_) {
				player_ = new player(x, y);
			}
		} else {
			// 敵を生成
			action_base* act = create_action(*it, *this);
			enemies_.push_back(new enemy(*it, x, y, act));
		}
		*it = SPACE;
	}
	if (!player_)
		throw runtime_error("プレイヤーが見つかりません。");
}

void game::start()
{
	if (!init_) return;

	initscr();
	cbreak();

	status st = PLAYING;
	while (true) {
		// 画面表示
		on_paint(st);

		// キーボード入力
		int input = getch();

		// 移動
		int result = on_action(st, input);
		if (result == QUIT) break;
		else if (result == ERROR) continue;
		else if (result == CONTINUE) { st = PLAYING; continue; }

		// 各種判定
		st = on_turn_end();
	}

	endwin();
}

void game::on_paint(status st) const
{
	erase();

	// フィールドを出力
	move(0, 0);
	for (int y = 0; y < height_; ++y) {
		int pos = y * width_;
		printw("%.*s\n", width_, &field_[pos]);
	}

	// プレイヤーを出力
	if (player_) {
		move(player_->get_y(), player_->get_x());
		printw("%c", PLAYER);
	}
	// 敵を出力
	for (Enemies::const_iterator it = enemies_.begin(); it != enemies_.end(); ++it) {
		move((*it)->get_y(), (*it)->get_x());
		printw("%c", (*it)->get_type());
	}

	// ステータスの表示
	move(height_, 0);
	printw("[%s]\n", st == PLAYING ? "PLAYING"
		   : st == GAME_OVER ? "GAME OVER"
		   : st == LIMIT_OVER ? "LIMIT OVER"
		   : st == BEAT_THE_GAME ? "BEAT THE GAME"
		   : "UNKNOWN");

	// 移動履歴
	printw("History.size[%d]\n", player_->get_history().size());
	for (History::const_iterator it = player_->get_history().begin();
		 it != player_->get_history().end(); ++it) {
		printw("%c", direction_to_char(*it));
	}
	printw("%c\n", direction_to_char(player_->get_direction()));

	// DOT の取得履歴
	printw("dot.size[%d]\n", getdot_.size());
	for (GetdotHistory::const_iterator it = getdot_.begin();
		 it != getdot_.end(); ++it) {
		printw("%c", *it ? '.' : ' ');
	}

	refresh();
}

int game::on_action(status st, int input)
{
	switch (input) {
	case 'q':
		return QUIT;

	case 'z': {
		// DOT をマスに返す
		if (!getdot_.empty()) {
			if (getdot_.back()) {
				field_[player_->get_x() + player_->get_y() * width_] = DOT;
			}
			getdot_.pop_back();
		}
		// undo
		player_->undo();
		for (Enemies::const_iterator it = enemies_.begin(); it != enemies_.end(); ++it) {
			(*it)->undo();
		}
		return CONTINUE;
	}

	case 'k':
	case 'j':
	case 'h':
	case 'l':
	case '.': {
		if (st != PLAYING) {
			return ERROR;
		}

		// 移動可能か確認
		moving_object tmp(player_->get_x(), player_->get_y());
		tmp.move(char_to_direction(input));
		if (!can_move(tmp.get_x(), tmp.get_y())) {
			return ERROR;
		}

		// 敵の移動
		for (Enemies::const_iterator it = enemies_.begin(); it != enemies_.end(); ++it) {
			(*it)->doing();
		}

		// プレイヤーの移動
		player_->move(char_to_direction(input));
		break;
	}
	default:
		return ERROR;
	}
	return SUCCESS;
}

game::status game::on_turn_end()
{
	// ドットの回収
	int pos = player_->get_x() + player_->get_y() * width_;
	if (field_[pos] == DOT) {
		field_[pos] = SPACE;
		getdot_.push_back(true);
	} else {
		getdot_.push_back(false);
	}

	// LIMIT OVER 判定
	if (static_cast<int>(getdot_.size()) > limit_) {
		return LIMIT_OVER;
	}

	// GAME OVER 判定
	position old_player = player_->get_latest_position();
	for (Enemies::const_iterator it = enemies_.begin(); it != enemies_.end(); ++it) {
		// 同一マス
		if (player_->same_position(**it)) {
			return GAME_OVER;
		}

		// 入れ替わり
		position old_enemy = (*it)->get_latest_position();
		if (player_->same_position(old_enemy) && (*it)->same_position(old_player)) {
			return GAME_OVER;
		}
	}

	// クリア判定
	if (field_.end() == find_if(field_.begin(), field_.end(), is_dot)) {
		return BEAT_THE_GAME;
	}

	return PLAYING;
}

const moving_object* game::get_player() const
{
	return player_;
}

bool game::in_range(int x, int y) const
{
	return 0 <= x && x < width_ && 0 <= y && y < height_;
}

bool game::can_move(int x, int y) const
{
	if (!in_range(x, y)) return false;
	return packman::can_move(field_[x + y * width_]);
}

packman::object game::get_object(int x, int y) const
{
	if (!in_range(x, y)) return OUTSIDE;
	return field_[x + y * width_];
}

} // namespace packman
