#ifndef SCN_STEP_CHARA_MAPCOLLRESULT_H
#define SCN_STEP_CHARA_MAPCOLLRESULT_H

#include "hel/math/Vector2.h"
#include "mcoll/detail/MoveGridGroupId.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: the flags keep their offset names because about 120 statements read them directly. _2 is the wall in
// front, _3 the wall behind, _4 and _5 graze left and right, _6 spine, _7 fire, _8 ice, _9 dead. _1c is the
// group of the floor, _20 that of the wall in front, and _28 is a mcoll::detail::LandAttribute.
class MapCollResult {
public:
    MapCollResult();

    void clear();
    void setHitWallBack();
    bool isHitFloor() const { return mIsHitFloor; }
    bool isHitRoof() const { return mIsHitRoof; }
    bool isHitWallFront() const { return _2; }
    bool isHitWallBack() const { return _3; }
    bool isHitWall() const { return _2 || _3; }
    // TODO: the name is a guess. No symbol of it survives, only its expansions.
    bool isHit() const { return mIsHitFloor || mIsHitRoof || _2 || _3; }
    bool isGrazeLeft() const { return _4; }
    bool isGrazeRight() const { return _5; }
    bool isOnFire() const { return _7; }
    bool isDead() const { return _9; }
    void setHitRoof() { mIsHitRoof = true; }
    void setHitWallFront() { _2 = true; }
    void setGrazeLeft() { _4 = true; }
    void setGrazeRight() { _5 = true; }
    void setOnSpine() { _6 = true; }
    void setOnFire() { _7 = true; }
    void setOnIce() { _8 = true; }

    bool mIsHitFloor;
    bool mIsHitRoof;
    bool _2;
    bool _3;
    bool _4;
    bool _5;
    bool _6;
    bool _7;
    bool _8;
    bool _9;
    hel::math::Vector2 _c;
    hel::math::Vector2 _14;
    ::mcoll::detail::MoveGridGroupId _1c;
    ::mcoll::detail::MoveGridGroupId _20;
    ::mcoll::detail::MoveGridGroupId _24;
    bool _28;
    ::mcoll::detail::MoveGridGroupId groupFloor() const;
};

}}}  // namespace scn::step::chara

#endif
