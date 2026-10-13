#ifndef SCN_STEP_CARRYITEM_USER_H
#define SCN_STEP_CARRYITEM_USER_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace ocoll {
class Owner;
}

namespace scn {
namespace step {

class Component;

namespace carryitem {

class CarryItem;

class User {
public:
    User(Component& component, ::ocoll::Owner& owner);

    bool chkCollide(const hel::math::Vector2& pos);
    void clearTargetItem();
    bool isItemExist() const;
    int targetItemKind() const;
    int targetItemUseCount() const;
    void setIsValid(bool isValid);
    void setIsBackDir(bool isBackDir);
    void useItem(CarryItem& item);
    const ::ocoll::Owner& owner() const { return *reinterpret_cast<const ::ocoll::Owner* const*>(this)[1]; }
    // TODO: names; the u32 at 0x48 is what a throw state counts while the button is held.
    void set_48(u32 value) { reinterpret_cast<u32*>(this)[0x48 / 4] = value; }
    void set_4C(u32 value) { reinterpret_cast<u32*>(this)[0x4C / 4] = value; }
    void set_41(bool flag) { reinterpret_cast<bool*>(this)[0x41] = flag; }
    void setIsWalk(bool isWalk) { reinterpret_cast<bool*>(this)[0x42] = isWalk; }
    void setIsRun(bool isRun) { reinterpret_cast<bool*>(this)[0x43] = isRun; }

    bool isRightDir() const { return mIsRightDir; }
    hel::math::Vector3 getOwnerPos() const { return mOwnerPos; }
    ::ocoll::Owner& getOCOwner() { return mOwner; }
    bool isBackDir() const { return mIsBackDir; }
    // TODO: the names of these three are guesses; only their expansions were seen.
    hel::math::Vector3 getConstraintPos() const { return mConstraintPos; }
    bool isNoUseSE() const { return mIsNoUseSE; }
    void clearNoUseSE() { mIsNoUseSE = false; }
    void resetStepShoeInfo();
    // TODO: the name is a guess; only its expansion was seen.
    hel::math::Vector3 getStepShoeScale() const { return _58; }

private:
    u32 _0;
    ::ocoll::Owner& mOwner;
    u32 _8[5];
    hel::math::Vector3 mConstraintPos;
    hel::math::Vector3 mOwnerPos;
    u32 _34[3];
    bool mIsRightDir;
    bool mIsBackDir;
    bool mIsWalk;
    bool mIsRun;
    u32 _44;
    u32 _48;
    u32 _4C;
    bool mIsNoUseSE;

public:
    // TODO: what the stomper boot's states read of its user: which script to play, and the model's scale.
    bool _51;
    bool _52;
    bool _53;
    bool _54;
    bool _55;
    hel::math::Vector3 _58;
};

}}}  // namespace scn::step::carryitem

#endif
