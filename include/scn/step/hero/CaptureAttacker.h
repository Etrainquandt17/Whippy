#ifndef SCN_STEP_HERO_CAPTUREATTACKER_H
#define SCN_STEP_HERO_CAPTUREATTACKER_H

#include "types.h"
#include "util/ObjRefHandle.h"

namespace hel {
namespace math {
class Vector3;
}}  // namespace hel::math

namespace scn {
namespace step {

namespace enemy {
class Enemy;
}

namespace hero {

// TODO: members and the other functions.
class CaptureAttacker {
public:
    util::ObjRefHandle<enemy::Enemy> chkCaptureEnemy();
    bool isCapture() const;
    void clearCapture();
    void decHp(u32 damage);
    void setConstraintPos(const hel::math::Vector3& pos);
    void setIgnoreMapColl(bool isIgnore);
    void setMapCollValid(bool isValid);
    hel::math::Vector3 getConstraintPos() const;
    u32 getID() const;
    void setVelocity(const hel::math::Vector3& velocity);
};

}}}  // namespace scn::step::hero

#endif
