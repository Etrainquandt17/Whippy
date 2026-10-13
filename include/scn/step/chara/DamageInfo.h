#ifndef SCN_STEP_CHARA_DAMAGEINFO_H
#define SCN_STEP_CHARA_DAMAGEINFO_H

#include "hel/math/Vector2.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/ocoll/Element.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: the name of the data's type is a guess, and its members are named as the enemies' damage states read
// them. The smash type is a signed enum that has no header yet.
class DamageInfo {
public:
    struct Data {
        hel::math::Vector2 _0;
        u32 _8;
        hel::math::Vector2 _c;
        hel::math::Vector2 mAttackPos;
        ocoll::AttackType mAttackType;
        s32 mSmashType;
        u32 mDamage;
        u32 _28;
        ocoll::Element mElement;
        u32 _30;
        f32 mAngle;
        f32 mWidth;
        f32 mSpeed;
        f32 _40;
        u32 _44;
        bool _48;
        bool _49;
        u32 _4c;
        u32 _50;
        u64 _58;
        u64 _60;
    };

    bool isValid() const;
    const Data& data() const;
    hel::math::Vector2 attackPos() const { return data().mAttackPos; }
    ocoll::AttackType attackType() const { return data().mAttackType; }
    int smashType() const { return data().mSmashType; }
    ocoll::Element element() const { return data().mElement; }
    ocoll::Element attackElement() const;

private:
    bool mIsValid;
    Data mData;
};

}
}
}

#endif
