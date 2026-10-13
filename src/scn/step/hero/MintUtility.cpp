#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/hero/MintUtility.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "hel/mint/AddOnMathDirection3.h"
#include "hel/mint/AddOnMathVector3.h"
#include "mcoll/detail/MoveGridGroupId.h"
#include "metafortress.h"
#include "ocoll/Attack.h"
#include "ocoll/NodeDesc.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/MintEffect.h"
#include "scn/step/hero/BossDemoCtrl.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/IndiviUtil.h"
#include "scn/step/hero/InvisibleControl.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/MintGear.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/Pinch.h"
#include "scn/step/hero/ShakeCharge.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Water.h"
#include "util/ObjList.h"

// TODO: a stand-in: with it AddAttackGearNode8 calls unlink and GetNodeFromPointer as the original does.
template class util::ObjListNode<g3d::Model, util::ObjListDummyType>;

// TODO: scn::step::hero::MintGear::Obj returns the gear itself in the original: no temporary is made for the
// call that follows. scn/step/hero/MintGear.h has it return a handle.
extern "C" scn::step::hero::Gear& Obj__Q43scn4step4hero8MintGearFv();

namespace scn {
namespace step {
namespace hero {

namespace MintUtility {

namespace {

// TODO: the node of an ocoll::NodeDesc is a g3d::NodeAccessor, assigned member by member; ocoll/NodeDesc.h holds
// its two parts.
struct NodeParts {
    util::ObjRefHandle<g3d::Model> mModel;
    u32 _10;
};

}

bool IsMainPlayer() {
    return MintHero::Obj().isMainPlayer();
}

bool IsKirby() {
    return IndiviUtil::IsKirby(MintHero::Obj().kind());
}

bool IsMeta() {
    return IndiviUtil::IsMeta(MintHero::Obj().kind());
}

bool IsDedede() {
    return IndiviUtil::IsDedede(MintHero::Obj().kind());
}

bool IsDee() {
    return IndiviUtil::IsDee(MintHero::Obj().kind());
}

bool IsMainPlayerRight() {
    f32 x = MintHero::Obj().location().pos().x;
    return MintHero::Obj().comp().heroManager().getMainPlayerPos().x < x;
}

void SetIsDirRight(bool value) {
    MintHero::Obj().model().setIsRightDir(value);
}

#define MF_FUNCTION IsDirRight__Q43scn4step4hero11MintUtilityFv
bool IsDirRight() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 addend;
    u32 size;
    u32 i;
    u32 hash;
    u32 tail;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  MF_WORD(0x24)
        opword  0xF73A170B
    after1:
        mflr    r21
        lwz     r14, 0x0(r21)
        lwz     r30, 0x4(r21)
        stw     r30, end
        stw     r14, start
    }
    hash = 0xC5;
    tail = end;
    size = tail - start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(tail - 1 - i);
    }
    hash ^= hash >> 10;
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0x9450E61D
    after2:
        mflr    r14
        lwz     r21, 0x0(r14)
        stw     r21, expected
    }
    hash ^= hash << 20;
    if (hash != expected) {
        asm {
            bl      after3
            opword  0xA859E900
            opword  0xD0707191
            opword  MF_WORD(0xC4)
        after3:
            mflr    r27
            lwz     r20, 0x8(r27)
            stw     r20, -0x4(r1)
            stw     r27, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r27, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0xE8)
            opword  0xBA99440A
            opword  0x54E79A80
            opword  MF_WORD(0xF4)
        after4:
            mflr    r29
            lwz     r26, 0x0(r29)
            stw     r29, mfBase
            lwz     r30, 0xc(r29)
            stw     r26, offset
            stw     r30, addend
        }
        response = offset + addend;
        response = response + mfBase;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    } else {
        return MintHero::Obj().model().isRightDir();
    }
}
#undef MF_FUNCTION

void LoadPos() {
    hel::mint::AddOnMathVector3::Set(MintHero::Obj().location().pos());
}

void LoadDir() {
    hel::mint::AddOnMathDirection3::Set(MintHero::Obj().target().getDirection3());
}

void LoadModelDir() {
    hel::math::Direction3 dir;
    dir.mFront = hel::math::Vector3::BASIS_X;
    dir.mFront *= MintHero::Obj().model().isRightDir() ? 1.0f : -1.0f;
    dir.restructFrontUp();
    hel::mint::AddOnMathDirection3::Set(dir);
}

void LoadDirFollowFloor() {
    hel::math::Direction3 dir = MintHero::Obj().target().getDirection3();
    hel::math::Vector2 normal = MintHero::Obj().mapColl()._74;
    dir.mUp = normal.toVector3();
    dir.restructUpLeft();
    hel::mint::AddOnMathDirection3::Set(dir);
}

bool IsPinch() {
    return MintHero::Obj().pinch().isPinch();
}

bool IsInWater() {
    return MintHero::Obj().water().isInWater();
}

int ShakeChargePower() {
    return MintHero::Obj().shakeCharge().power();
}

bool IsInvisible() {
    return MintHero::Obj().invisibleControl().isInvisible();
}

bool IsOnIce() {
    chara::MapCollResult result = MintHero::Obj().mapColl().result();
    return result._8;
}

bool IsExistPiggybackChild() {
    return MintHero::Obj().piggyback().isExistChild();
}

bool IsExistCarryItem() {
    return MintHero::Obj().carryItemUser().isItemExist();
}

bool IsHidDisable() {
    return !MintHero::Obj().hid().isEnableInputs();
}

bool IsBossDemoSilent() {
    return MintHero::Obj().comp().heroManager().bossDemoCtrl().isSilent();
}

bool IsSeparateProcessMyTurn() {
    return Utility::IsSeparateProcessMyTurn(MintHero::Obj());
}

bool IsHaveCandle() {
    carryitem::User& user = MintHero::Obj().carryItemUser();
    if (user.isItemExist() && user.targetItemKind() == 3 && user.targetItemUseCount() == 0) {
        return true;
    }
    return false;
}

int PlayerCount() {
    return MintHero::Obj().comp().heroManager().getPlayerCount();
}

void ReqLandingStar() {
    Utility::ReqLandingStar(MintHero::Obj());
}

#define MF_FUNCTION ReqNakigoe__Q43scn4step4hero11MintUtilityFv
void ReqNakigoe() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 subtrahend;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 mfBase;
    u32 i;
    u32 base;
    u32 hash;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x48BD6A98
    after1:
        mflr    r22
        lwz     r14, 0x0(r22)
        stw     r14, expected
        bl      after2
        opword  MF_WORD(0x38)
        opword  0x10ABC980
        opword  0x08117C0A
        opword  MF_WORD(0x44)
        opword  0x14A34B81
    after2:
        mflr    r21
        lwz     r18, 0xc(r21)
        lwz     r29, 0x0(r21)
        add     r29, r29, r21
        stw     r29, start
        add     r18, r18, r29
        stw     r18, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    hash = 0x811C9DDB;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash -= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0x58E7C193
            opword  0xF9454E03
            opword  MF_WORD(0xD8)
        after3:
            mflr    r16
            lwz     r29, 0x8(r16)
            stw     r29, -0x4(r1)
            stw     r16, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r16, -0x8(r1)
            mtlr    r29
            bl      after4
            opword  MF_WORD(0xFC)
            opword  MF_WORD(0x100)
        after4:
            mflr    r29
            lwz     r30, 0x4(r29)
            stw     r30, subtrahend
            lwz     r30, 0x0(r29)
            stw     r29, mfBase
            stw     r30, offset
        }
        offset = offset ^ 0xA0;
        response = offset - subtrahend;
        response = response + mfBase;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    } else {
        Utility::ReqNakigoe(MintHero::Obj());
    }
}
#undef MF_FUNCTION

void ReqKakegoe() {
    Utility::ReqKakegoe(MintHero::Obj());
}

bool IsPressHDirKey() {
    return Utility::IsPressHDirKey(MintHero::Obj());
}

void AddAttackGearNode3(u32 arg0, u32 arg1, f32 arg2) {
    AddAttackGearNode8(arg0, arg1, arg2, 0.0f, 0.0f, 0.0f, 0.0f, false);
}

void AddAttackGearNode5(u32 arg0, u32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    AddAttackGearNode7(arg0, arg1, arg2, arg3, arg4, arg3, arg4);
}

void AddAttackGearNode7(u32 arg0, u32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    AddAttackGearNode8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, false);
}

void AddAttackGearNode8(u32 arg0, u32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, bool arg7) {
    ::ocoll::NodeDesc desc;
    reinterpret_cast<NodeParts&>(desc) =
        reinterpret_cast<const NodeParts&>(static_cast<const g3d::NodeAccessor&>(Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1)));
    desc._14 = arg2;
    desc._18 = hel::math::Vector2(arg3, arg4);
    desc._20 = hel::math::Vector2(arg5, arg6);
    desc._28 = arg7;
    // TODO: the chara::ObjColl at 0x8 of hero::ObjColl, whose header has no members yet.
    reinterpret_cast<chara::ObjColl*>(reinterpret_cast<u8*>(&MintHero::Obj().objColl()) + 8)->attack().addNode(arg0, desc);
}

#define MF_FUNCTION RequestEffectGearNodeN__Q43scn4step4hero11MintUtilityFQ43scn4step6effect4KindUl
void RequestEffectGearNodeN(effect::Kind arg0, u32 arg1) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 mfBase;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x8597D5C2
    after1:
        mflr    r25
        lwz     r22, 0x0(r25)
        stw     r22, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x44)
        opword  0x0FBFA60B
        opword  MF_WORD(0x4C)
        opword  0x28909080
    after2:
        mflr    r23
        lwz     r15, 0x0(r23)
        lwz     r14, 0x8(r23)
        stw     r14, start
        stw     r15, end
    }
    limit = end - start + 1;
    base = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 61;
        hash += *(u16*)(base + i - 1);
    }
    if ((hash ^ expected) != 0) {
        asm {
            bl      after3
            opword  0x06FB060B
            opword  0x9C728291
            opword  0x1AFC5705
            opword  MF_WORD(0xC0)
        after3:
            mflr    r28
            lwz     r30, 0xc(r28)
            stw     r30, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r30, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r30
            bl      after4
            opword  MF_WORD(0xE4)
            opword  MF_WORD(0xE8)
        after4:
            mflr    r20
            lwz     r26, 0x0(r20)
            lwz     r29, 0x4(r20)
            stw     r29, key
            stw     r26, offset
            stw     r20, mfBase
        }
        key = 0;
        response = offset;
        response = response + mfBase;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    } else {
        g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
        chara::MintEffect::Obj().requestN(arg0, node);
    }
}
#undef MF_FUNCTION

void RequestEffectGearNodeNS(effect::Kind arg0, u32 arg1, f32 arg2) {
    g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
    chara::MintEffect::Obj().requestN(arg0, node, arg2);
}

void RequestEffectGearNodeNO(effect::Kind arg0, u32 arg1) {
    g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
    chara::MintEffect::Obj().requestN(arg0, node, hel::mint::AddOnMathVector3::Get());
}

void RequestEffectGearNodeNOS(effect::Kind arg0, u32 arg1, f32 arg2) {
    g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
    chara::MintEffect::Obj().requestN(arg0, node, hel::mint::AddOnMathVector3::Get(), arg2);
}

void RequestEffectGearNodeND(effect::Kind arg0, u32 arg1) {
    g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
    chara::MintEffect::Obj().requestND(arg0, node, hel::mint::AddOnMathDirection3::Get());
}

void RequestEffectGearNodeNDS(effect::Kind arg0, u32 arg1, f32 arg2) {
    g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
    chara::MintEffect::Obj().requestND(arg0, node, hel::mint::AddOnMathDirection3::Get(), arg2);
}

void RequestEffectGearNodeNDO(effect::Kind arg0, u32 arg1) {
    g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
    chara::MintEffect::Obj().requestND(arg0, node, hel::mint::AddOnMathDirection3::Get(), hel::mint::AddOnMathVector3::Get());
}

void RequestEffectGearNodeNDOS(effect::Kind arg0, u32 arg1, f32 arg2) {
    g3d::NodeAccessor node = Obj__Q43scn4step4hero8MintGearFv().model().nodes().at(arg1);
    chara::MintEffect::Obj().requestND(arg0, node, hel::mint::AddOnMathDirection3::Get(), hel::mint::AddOnMathVector3::Get(), arg2);
}

}
}
}
}
