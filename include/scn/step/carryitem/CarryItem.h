#ifndef SCN_STEP_CARRYITEM_CARRYITEM_H
#define SCN_STEP_CARRYITEM_CARRYITEM_H

#include "hel/common/PointerWrapper.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mem/ExplicitScopedPtr.h"
#include "mem/HeapExpArrayUser.h"
#include "scn/step/carryitem/Param.h"
#include "scn/step/carryitem/ReleaseType.h"
#include "scn/step/map/BinCarryItemKind.h"
#include "types.h"
#include "util/ObjRefHandle.h"
#include "util/StateChanger.h"

namespace gobj {
class FootState;
class Location;
class Move;
class Target;
}

namespace scn {
namespace step {

class Component;

namespace chara {
class Effect;
class GroundChecker;
class LandConstraint;
class Lifetime;
class Model;
class ObjCollLite;
class Shadow;
class SoundSE;
class Water;
class WorldCage;
}
namespace ogen {
class Generator;
}
namespace sfx {
class DarknessLight;
}

namespace carryitem {

class CarryItem;
class Desc;
class Flash;
class IState;
class MapColl;
class ObjStop;
class ScriptCallback;
class StateCallback;
class User;
class VacuumReceiver;

}}}  // namespace scn::step::carryitem

namespace util {

// TODO: Owner is a member of the ObjRefHandle template and belongs in util/ObjRefHandle.h.
// This specialization only exists to declare it for CarryItem until it is there.
template <>
class ObjRefHandle<scn::step::carryitem::CarryItem>
    : public ObjListNode<scn::step::carryitem::CarryItem, ObjListDummyType> {
public:
    class Owner {
    public:
        ~Owner();

        void unset();

    private:
        scn::step::carryitem::CarryItem* mObj;
        u8 _4[0x10];
    };

    scn::step::carryitem::CarryItem* operator->() const { return mObj; }
    // TODO: stands for whatever the original tests a handle with, which is expanded where Switch uses it.
    scn::step::carryitem::CarryItem* ptr() const { return mObj; }
};

}

namespace scn {
namespace step {
namespace carryitem {

class CarryItem {
public:
    CarryItem(Component& component, mem::HeapExpArray& heap, const Desc& desc);
    ~CarryItem();

    map::BinCarryItemKind kind() const;
    f32 getThrowPowerRate() const;
    void setNextStateDefault();
    void put(const Desc& desc);
    void reset();
    void deadProcReleaseEffect();
    bool isDisableReputItem() const;

    void dead();
    void deadWithEffect();
    void vanishObjGenerator();
    void clearUser();
    hel::common::PointerWrapper<User> getUser();
    void setCollideInterval(u32 interval);
    void clearCheckRadiusPrevOwner();
    bool isEnableCarry() const;
    void setIsEnableCarry(bool isEnableCarry);
    void setNextStateDefaultExt();
    void setNextStateSpaceJump();
    void reput();
    void setReputStart(bool isReputStart);
    void incUseCount();
    void setUseCount(u32 useCount);
    void resetUseCount();
    bool canGather() const;
    void setCanGather(bool canGather);
    void setGatherOwnerUid(u64 uid);
    u64 getGatherOwnerUid() const;
    void setCanOpenDoor(bool canOpenDoor);
    void setIsGathered(bool isGathered);
    bool isStageItem() const;
    bool isFastReputItem() const;
    void onStepOver();
    void onSpaceJumpEnd();
    u32 subKind() const;
    hel::math::Vector3 centerPos() const;
    bool isCatched() const;
    bool canShowDarknessLight() const;
    u32 getThrowPower() const;
    void setThrowPower(u32 throwPower);
    bool isDead() const;
    bool isGathering() const;
    void setIsGathering(bool isGathering);
    bool isReputed() const;
    u32 useCount() const;
    ReleaseType getReleaseType() const;
    void setReleaseType(ReleaseType type);
    void resetReleaseType();

    Component& comp();
    const Param& param() const;
    gobj::Target& target();
    gobj::FootState& footState();
    gobj::Location& location();
    gobj::Move& move();
    chara::Model& model();
    chara::Effect& effect();
    chara::Effect& effectBack();
    chara::Effect& effectWarp();
    chara::SoundSE& soundSE();
    ObjStop& objStop();
    chara::LandConstraint& landConstraint();
    chara::Lifetime& lifetime();
    MapColl& mapColl();
    chara::ObjCollLite& objColl();
    VacuumReceiver& vacuumReceiver();
    chara::Water& water();
    Flash& flash();
    chara::Shadow& shadow();
    chara::WorldCage& worldCage();
    chara::GroundChecker& groundChecker();
    sfx::DarknessLight& darknessLight();
    util::StateChanger<IState, 256>& stateChanger();

private:
    // TODO: name. Only seen inlined.
    bool hasObjGenerator() const { return mObjGenerator != 0; }

    Component& mComponent;
    mem::HeapExpArrayUser mHeapUser;
    hel::math::Vector2 _C;
    map::BinCarryItemKind mKind;
    u32 _18;
    bool _1C;
    bool mIsDead;
    bool _1E;
    bool _1F;
    bool _20;
    u64 _28;
    bool _30;
    u32 _34;
    bool _38;
    u32 _3C;
    u32 mThrowPower;
    u32 mUseCount;
    u64 _48;
    f32 _50;
    u32 _54;
    bool _58;
    bool mIsReputed;
    hel::common::PointerWrapper<User> mUser;
    Param mParam;
    ogen::Generator* mObjGenerator;
    mem::ExplicitScopedPtr<gobj::Target> mTarget;
    mem::ExplicitScopedPtr<gobj::FootState> mFootState;
    mem::ExplicitScopedPtr<gobj::Location> mLocation;
    mem::ExplicitScopedPtr<gobj::Move> mMove;
    mem::ExplicitScopedPtr<chara::Model> mModel;
    mem::ExplicitScopedPtr<ScriptCallback> mScriptCallback;
    mem::ExplicitScopedPtr<chara::Effect> mEffect;
    mem::ExplicitScopedPtr<chara::Effect> mEffectBack;
    mem::ExplicitScopedPtr<chara::Effect> mEffectWarp;
    mem::ExplicitScopedPtr<chara::SoundSE> mSoundSE;
    mem::ExplicitScopedPtr<chara::Lifetime> mLifetime;
    mem::ExplicitScopedPtr<ObjStop> mObjStop;
    mem::ExplicitScopedPtr<chara::LandConstraint> mLandConstraint;
    mem::ExplicitScopedPtr<MapColl> mMapColl;
    mem::ExplicitScopedPtr<chara::ObjCollLite> mObjColl;
    mem::ExplicitScopedPtr<VacuumReceiver> mVacuumReceiver;
    mem::ExplicitScopedPtr<chara::Water> mWater;
    mem::ExplicitScopedPtr<chara::WorldCage> mWorldCage;
    mem::ExplicitScopedPtr<chara::GroundChecker> mGroundChecker;
    mem::ExplicitScopedPtr<Flash> mFlash;
    mem::ExplicitScopedPtr<chara::Shadow> mShadow;
    mem::ExplicitScopedPtr<sfx::DarknessLight> mDarknessLight;
    mem::ExplicitScopedPtr<StateCallback> mStateCallback;
    mem::ExplicitScopedPtr<util::StateChanger<IState, 256> > mStateChanger;
    util::ObjRefHandle<CarryItem>::Owner mHandleOwner;
};

}}}  // namespace scn::step::carryitem

#endif
