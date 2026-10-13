#ifndef SCN_SUBGAME_GUNSHOOT_CHARA_PLAYER_H
#define SCN_SUBGAME_GUNSHOOT_CHARA_PLAYER_H

#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace chara {

class Player {
public:
    ~Player();

    bool isShotable() const;
    void forceShotable();
    void shot(bool charged);
    void damage(bool);
    bool isCharged() const;

private:
    u32 _0[0x9A];
};

}}}}  // namespace scn::subgame::gunshoot::chara

#endif
