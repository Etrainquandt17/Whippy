#ifndef SCN_GOALGAME_GAMECTRL_H
#define SCN_GOALGAME_GAMECTRL_H

#include "types.h"

namespace scn {
namespace goalgame {

class Component;

class GameCtrl {
public:
    GameCtrl(Component& component);
    ~GameCtrl();

private:
    u32 _0[0x17];
};

}}  // namespace scn::goalgame

#endif
