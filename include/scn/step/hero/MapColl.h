#ifndef SCN_STEP_HERO_MAPCOLL_H
#define SCN_STEP_HERO_MAPCOLL_H

#include "hel/math/Vector2.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/hero/MapCollResult.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: size and the other members.
class MapColl {
public:
    void setAfterMoveDetectForce(bool isForce);
    void setValid(bool isValid);
    void procMapColl();
    void reset();
    MapCollResult result() const { return *reinterpret_cast<const MapCollResult*>(&_48); }

    u32 _0[0x48 / 4];
    chara::MapCollResult _48;
    hel::math::Vector2 _74;
    bool isPassThroughLand() const;
    void setTriggerPassThroughLand();
    MapCollResult precheck(const hel::math::Vector2& offset);
    void resetTriggerPassThroughLand();
    bool is_86() const { return reinterpret_cast<const u8*>(this)[0x86]; }
    void setThroughOneSpace(bool isThrough);
    void setIgnoreFire(bool isIgnore);
    bool is_8E() const { return reinterpret_cast<const u8*>(this)[0x8E]; }
    bool is_8F() const { return reinterpret_cast<const u8*>(this)[0x8F]; }
    void setIgnoreInvisibleRoof(bool isIgnore);
    bool isValid() const;
    void setHitSlopeRoof(bool isHit);
    f32 actorHeight() const;
    void setIgnoreInvisibleWall(bool isIgnore);
    hel::math::Vector2 floorNormal() const { return _74; }
};

}}}  // namespace scn::step::hero

#endif
