#ifndef SCN_STEP_HERO_PIGGYBACK_H
#define SCN_STEP_HERO_PIGGYBACK_H

#include "hel/common/PointerWrapper.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/AbilityKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

class Piggyback {
public:
    explicit Piggyback(Hero& hero);
    ~Piggyback();

    void setChild(Piggyback& child);
    void setParent(Piggyback& parent);
    void clearParent();
    void clearChild();
    void unlinkParent();
    void unlinkChild();
    void unlinkAll();
    void setInterval(u32 interval);
    void setIsConstraintSquash(bool isConstraintSquash);
    void procConstraint();
    void constraintChild();
    void constraint();
    void resetConstraintInfo();
    hel::math::Vector3 getRootPos() const;
    hel::math::Vector3 getParentCenter() const;
    hel::math::Vector3 getConstraintOffset();
    hel::math::Vector3 getConstraintPos() const;
    bool isParentRightDir() const;
    bool isParentSquat() const;
    hel::math::Vector3 getParentVelocity() const;
    AbilityKind getParentAbilityKind() const;
    u32 getParentPadChan() const;
    hel::math::Vector3 getRootSquashScale() const;
    bool isRootGuard() const;
    bool isRootBackDir() const;
    bool isRootSuperJump() const;
    void clearChargeAttack();
    bool canChargeAttack() const;
    bool canChargeAttackChild() const;
    u32 getChargeLv() const;
    u32 getChargeLvChild() const;
    f32 getRootParentFrontViewOffsTarget() const;
    void setChildHidDisable();
    void constraintMapColl();
    void setEnableReceive(bool isEnable);
    void setEnableRide(bool isEnable);
    void setIsPiggybackNow(bool isPiggybackNow);
    bool isPiggybackNow() const;

    bool isExistParent() const { return mParent.wasSet(); }
    bool isExistChild() const { return mChild.wasSet(); }

private:
    Hero& mHero;
    hel::common::PointerWrapper<Piggyback> mParent;
    hel::common::PointerWrapper<Piggyback> mChild;
    bool mIsEnableReceive;
    bool mIsEnableRide;
    bool mIsPiggybackNow;
    u32 mInterval;
    bool mIsConstraintSquash;
    hel::math::Vector3 _18;
    hel::math::Vector3 _24;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3C;
    bool mIsParentSquat;
    hel::math::Vector3 _44;
    AbilityKind mParentAbilityKind;
    bool _54;
};

}}}  // namespace scn::step::hero

#endif
