#ifndef SCN_SUBGAME_GUNSHOOT_CHARA_BULLET_H
#define SCN_SUBGAME_GUNSHOOT_CHARA_BULLET_H

#include "hel/math/Vector3.h"
#include "nw4r/math/math_geometry.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace chara {

class Bullet {
public:
    ~Bullet();

    void updateMain();
    void reset();
    bool isSet() const;
    bool isCharged() const;
    void set(hel::math::Vector3 pos, nw4r::math::SEGMENT3 segment, bool charged);

private:
    u32 _0[0x59];
};

}}}}  // namespace scn::subgame::gunshoot::chara

#endif
