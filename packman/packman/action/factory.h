#ifndef PACKMAN_ACTION_FACTORY_H__
#define PACKMAN_ACTION_FACTORY_H__

#include "../common.h"
#include "action_base.h"

namespace packman {

// 先行宣言
class game;

namespace action {

action_base* create_action(packman::object o, game& g);

} } // namespace packman::action

#endif
