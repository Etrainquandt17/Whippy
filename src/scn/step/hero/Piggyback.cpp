#define HEL_MATH_VECTOR3_NO_COPY_CONSTRUCTOR

#include "scn/step/hero/Piggyback.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "metafortress.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CameraTarget.h"
#include "scn/step/hero/Guard.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/PowerCharge.h"
#include "scn/step/hero/Squash.h"
#include "scn/step/hero/StateChecker.h"

namespace scn {
namespace step {
namespace hero {

Piggyback::Piggyback(Hero& hero)
    : mHero(hero)
    , mIsEnableReceive(false)
    , mIsEnableRide(false)
    , mIsPiggybackNow(false)
    , mInterval(0)
    , mIsConstraintSquash(false)
    , _30(0.0f)
    , _34(0.0f)
    , _38(1.0f)
    , _3C(1.0f)
    , mIsParentSquat(isParentSquat())
    , mParentAbilityKind(getParentAbilityKind())
    , _54(false) {}

Piggyback::~Piggyback() {}

void Piggyback::setParent(Piggyback& parent) {
    mParent.set(parent);
}

void Piggyback::setChild(Piggyback& child) {
    if (!isExistChild() && !child.isExistParent()) {
        mChild.set(child);
        mChild->setParent(*this);
    }
}

// TODO: clearParent, clearChild, unlinkParent and unlinkChild call PointerWrapper::unset in the original. Here it
// is expanded.
void Piggyback::clearParent() {
    mParent.unset();
}

void Piggyback::clearChild() {
    mChild.unset();
}

void Piggyback::unlinkParent() {
    if (mParent.wasSet()) {
        mParent->clearChild();
        mParent.unset();
    }
}

void Piggyback::unlinkChild() {
    if (mChild.wasSet()) {
        mChild->clearParent();
        mChild.unset();
    }
}

void Piggyback::unlinkAll() {
    unlinkParent();
    unlinkChild();
}

void Piggyback::setInterval(u32 interval) {
    if (mInterval < interval) {
        mInterval = interval;
        unlinkAll();
    }
}

void Piggyback::setEnableReceive(bool isEnable) {
    mIsEnableReceive = isEnable;
}

void Piggyback::setEnableRide(bool isEnable) {
    mIsEnableRide = isEnable;
}

void Piggyback::setIsPiggybackNow(bool isPiggybackNow) {
    mIsPiggybackNow = isPiggybackNow;
}

bool Piggyback::isPiggybackNow() const {
    return mIsPiggybackNow;
}

void Piggyback::setIsConstraintSquash(bool isConstraintSquash) {
    mIsConstraintSquash = isConstraintSquash;
    if (isExistChild()) {
        mChild->setIsConstraintSquash(isConstraintSquash);
    }
}

void Piggyback::procConstraint() {
    if (!isExistParent() && isExistChild()) {
        mChild->constraintChild();
    }
}

void Piggyback::constraintChild() {
    constraint();
    if (isExistChild()) {
        mChild->constraintChild();
    }
}

void Piggyback::resetConstraintInfo() {
    _18 = getRootPos();
    _24 = getConstraintPos();
    _30 = 0.0f;
    _34 = 0.0f;
    _38 = 1.0f;
    _3C = 1.0f;
    mIsParentSquat = isParentSquat();
    _44 = hel::math::Vector3::ZERO;
    mParentAbilityKind = getParentAbilityKind();
    _54 = false;
}

hel::math::Vector3 Piggyback::getRootPos() const {
    if (isExistParent()) {
        return mParent->getRootPos();
    }
    return mHero.location().pos();
}

// TODO: three instructions short. The result is returned through the copy constructor where the original copies
// it word by word.
hel::math::Vector3 Piggyback::getParentCenter() const {
    if (mParent.wasSet()) {
        hel::math::Vector3 pos = mParent->mHero.location().pos();
        f32 rate = isParentSquat() ? 0.5f : 1.0f;
        hel::math::Vector3 center(mParent->mHero.location().toCenter() * rate);
        if (mIsConstraintSquash) {
            center.x *= mHero.squash().getCurrentScale().x;
            center.y *= mHero.squash().getCurrentScale().y;
        }
        pos += center;
        return pos;
    }
    return mHero.location().centerPos();
}

hel::math::Vector3 Piggyback::getConstraintPos() const {
    hel::math::Vector3 pos;
    if (!mParent.wasSet()) {
        pos = mHero.location().pos();
    } else {
        pos = getParentCenter();
        hel::math::Vector3 offset;
        offset = mParent->getConstraintOffset();
        if (mIsConstraintSquash) {
            offset.x *= mHero.squash().getCurrentScale().x;
            offset.y *= mHero.squash().getCurrentScale().y;
        }
        pos += offset;
    }
    return pos;
}

bool Piggyback::isParentRightDir() const {
    return !mParent.wasSet() ? mHero.target().isRightDir() : mParent->mHero.target().isRightDir();
}

// TODO: the original calls StateChecker::isSquat. Here it is expanded, perhaps until the unit's other functions
// use it too.
bool Piggyback::isParentSquat() const {
    if (!mParent.wasSet()) {
        return false;
    }
    return mParent->mHero.stateChecker().isSquat();
}

hel::math::Vector3 Piggyback::getParentVelocity() const {
    if (isExistParent()) {
        return mParent->mHero.move().velocity();
    }
    return hel::math::Vector3();
}

AbilityKind Piggyback::getParentAbilityKind() const {
    if (isExistParent()) {
        return mParent->mHero.abilityManager().abilityKind();
    }
    return mHero.abilityManager().abilityKind();
}

#define MF_FUNCTION getParentPadChan__Q43scn4step4hero9PiggybackCFv
u32 Piggyback::getParentPadChan() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x5269524B
    after1:
        mflr    r27
        lwz     r26, 0x0(r27)
        stw     r26, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
        opword  0x48F3E380
    after2:
        mflr    r22
        lwz     r18, 0x0(r22)
        stw     r18, start
        lwz     r17, 0x4(r22)
        add     r18, r18, r17
        stw     r18, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 61;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0 && isExistParent()) {
        return mParent->mHero.padChan();
    }
    return mHero.padChan();
}
#undef MF_FUNCTION

hel::math::Vector3 Piggyback::getRootSquashScale() const {
    if (isExistParent()) {
        return mParent->getRootSquashScale();
    }
    return mHero.squash().getCurrentScale();
}

bool Piggyback::isRootGuard() const {
    if (isExistParent()) {
        return mParent->isRootGuard();
    }
    return mHero.guard().isGuard();
}

bool Piggyback::isRootSuperJump() const {
    if (isExistParent()) {
        return mParent->isRootSuperJump();
    }
    return mHero.stateChecker().isSuperJump();
}

void Piggyback::clearChargeAttack() {
    mHero.powerCharge().clear();
    if (isExistChild()) {
        mChild->clearChargeAttack();
    }
}

bool Piggyback::canChargeAttack() const {
    if (!isExistChild()) {
        return false;
    }
    if (isExistParent()) {
        return false;
    }
    return canChargeAttackChild();
}

bool Piggyback::canChargeAttackChild() const {
    if (!mHero.powerCharge().isChargeAttackReady()) {
        return false;
    }
    if (isExistChild()) {
        return mChild->canChargeAttackChild();
    }
    return true;
}

u32 Piggyback::getChargeLv() const {
    if (!isExistChild()) {
        return 0;
    }
    if (isExistParent()) {
        return 0;
    }
    return getChargeLvChild();
}

u32 Piggyback::getChargeLvChild() const {
    if (isExistChild()) {
        return mChild->getChargeLvChild() + 1;
    }
    return 0;
}

f32 Piggyback::getRootParentFrontViewOffsTarget() const {
    if (isExistParent()) {
        return mParent->getRootParentFrontViewOffsTarget();
    }
    return mHero.cameraTarget().getFrontViewOffsTarget();
}

#define MF_FUNCTION setChildHidDisable__Q43scn4step4hero9PiggybackFv
void Piggyback::setChildHidDisable() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 size;
    u32 hash;
    u32 i;
    u32 last;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xB0B67880
        opword  0x90C5F980
        opword  MF_WORD(0x38)
        opword  0x0493FC90
    after1:
        mflr    r19
        lwz     r16, 0xc(r19)
        lwz     r17, 0x0(r19)
        stw     r17, end
        stw     r16, start
    }
    size = end - start;
    last = end;
    mHero.hid().disableInputs();
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    asm {
        bl      after2
        opword  MF_WORD(0xB8)
        opword  0x4AE4DE11
    after2:
        mflr    r25
        lwz     r14, 0x0(r25)
        stw     r14, expected
    }
    hash += hash << 15;
    if (hash - expected != 0 || isExistChild()) {
        mChild->setChildHidDisable();
    }
}
#undef MF_FUNCTION

// TODO: Hero::location() const returns a Location that can be written to in the original.
void Piggyback::constraintMapColl() {
    if (!isRootBackDir()) {
        hel::math::Vector3 pos = mHero.location().pos();
        Hero& hero = mHero;
        const_cast<chara::Location&>(hero.location()).setPos(getRootPos());
        mHero.mapColl().setAfterMoveDetectForce(true);
        mHero.mapColl().setValid(true);
        const_cast<chara::Location&>(mHero.location()).setPos(pos);
        mHero.mapColl().procMapColl();
        mHero.mapColl().setValid(false);
    }
}

}}}  // namespace scn::step::hero
