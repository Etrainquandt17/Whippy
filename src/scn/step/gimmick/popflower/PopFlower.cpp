#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS
#define UTIL_OBJLISTNODE_CONSTRUCTOR_LINK_REFERENCE
#define UTIL_OBJREFHANDLE_ASSIGNMENT_END_ITERATOR

#include "scn/step/gimmick/popflower/PopFlower.h"

#include "app/Random.h"
#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "g3d/StdModel.h"
#include "hel/common/FixedString.h"
#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/MaproPos.h"
#include "scn/step/bg/Manager.h"
#include "scn/step/gimmick/Util.h"
#include "scn/step/gimmick/popflower/ItemGen.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/map/BinGmkGeneralEntry.h"
#include "scn/step/map/MemManager.h"
#include "scn/step/spstop/Manager.h"
#include "std/tr1/reference_wrapper.h"
#include "util/ObjRefHandleInline.h"

using app::Random;
using g3d::NodeAccessor;
using g3d::Root;
using hel::common::FixedString;
using hel::common::FixedStringIN;
using hel::common::MutableArray;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace {

// TODO: what g3d::NodeAccessor holds; g3d/NodeAccessor.h has it opaque.
struct NodeAccessorMembers {
    ObjRefHandle<g3d::Model> model;
    u32 index;
};

}

namespace {

FixedString<40> getConnectString(const char* a, const char* b) {
    return FixedStringIN<char, 40>::FromFormat("%s%s", a, b);
}

#define MF_FUNCTION getConnectString__27_unnamed_PopFlower_prt_cpp_FPCcPCcPCc
FixedString<40> getConnectString(const char* a, const char* b, const char* c) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 t;
    u32 last;
    u32 word;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x7504BE4E
    after1:
        mflr    r14
        lwz     r23, 0x0(r14)
        stw     r23, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0xF734B20B
        opword  0xAD669705
        opword  MF_WORD(0x58)
    after2:
        mflr    r14
        lwz     r23, 0xc(r14)
        lwz     r27, 0x0(r14)
        stw     r27, start
        stw     r23, end
    }
    word = start;
    last = end;
    word -= 2;
    last -= 2;
    while (word != last) {
        word += 2;
        hash *= 37;
        t = *(u16*)word;
        hash += t;
    }
    last = hash >> 10;
    hash ^= last;
    last = hash << 20;
    hash ^= last;
    last = expected;
    last = hash & ~last;
    t = expected;
    t = t & ~hash;
    t = last | t;
    hash = __cntlzw(t);
    t = hash >> 5;
    hash = t << 11;
    hash = t | hash;
    if (hash == 0) {
        volatile u32 addend;
        volatile u32 anchor;
        volatile u32 offset;
        volatile u32 response;

        asm {
            stw     r23, -0x4(r1)
            bl      after3
            opword  MF_WORD(0xE0)
            opword  0x56B3F70B
            opword  0x604BA692
            opword  0xE4703100
        after3:
            mflr    r23
            lwz     r20, 0x0(r23)
            stw     r20, 0x0(r1)
            stw     r23, 0x4(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x108)
            opword  0x2C9B0D91
            opword  0x1002B092
            opword  MF_WORD(0x114)
        after4:
            mflr    r29
            lwz     r19, 0x0(r29)
            lwz     r23, 0xc(r29)
            stw     r23, addend
            stw     r19, offset
            stw     r29, anchor
        }
        offset = offset - 0x8A;
        response = offset + addend;
        response = response + anchor;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    } else {
        return FixedStringIN<char, 40>::FromFormat("%s%s%s", a, b, c);
    }
}
#undef MF_FUNCTION

}

namespace scn {
namespace step {
namespace gimmick {
namespace popflower {

#define MF_FUNCTION __ct__Q53scn4step7gimmick9popflower9PopFlowerFRCQ43scn4step3map18BinGmkGeneralEntryRQ33scn4step9ComponentRQ53scn4step7gimmick9popflower7ItemGenRQ43scn4step7gimmick50ParamAccessor_Q53scn4step7gimmick9popflower5Param_
PopFlower::PopFlower(const map::BinGmkGeneralEntry& entry, Component& component, ItemGen& itemGen, ParamAccessor<Param>& param)
    : mParam(param)
    , mComponent(component)
    , mItemGen(itemGen)
    , mName(Random::Rand(4) == 0 ? "A" : "B")
    , mPos(entry._4.toMaproPos().toWorldPos())
    , mModel(component, mfGetResFileName(), getConnectString(mName, "TopL"), true, true)
    , mOwner(component.objCollManager(), 2, component.mapMemManager().allocator())
    , mHit(component.objCollManager(), mOwner)
    , mSearchAttack(component.objCollManager(), mOwner)
    , mHeroKind(hero::KIND_KIRBY_0)
    , mEffect(component)
    , mSE()
    , mStop(component)
    , mState(STATE_WAIT)
    , mFrameRate(1.0f)
    , _C6C(0)
    , mVacuumReceiver(component.mapMemManager().allocator())
    , mHeroBodyAttacks()
    , _CC0(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    u32 random = Random::Rand(100);
    u32 size = 0;
    u32 sum = 0;
    for (u32 i = 0; i < 4; i++) {
        sum += mParam.obj()._1C[i];
        if (random < sum) {
            size = i;
            break;
        }
    }
    bool isExtraMode = mComponent.context()._524.isExtraMode();
    asm {
        bl      after1
        opword  MF_WORD(0x1FC)
    after1:
        mflr    r25
        lwz     r16, 0x0(r25)
        add     r16, r16, r25
        stw     r16, start
        bl      after2
        opword  MF_WORD(0x214)
    after2:
        mflr    r25
        lwz     r14, 0x0(r25)
        add     r16, r16, r14
        stw     r16, end
    }
    f32 scale;
    if (isExtraMode) {
        scale = mParam.obj()._3C[size];
    } else {
        scale = mParam.obj()._2C[size];
    }
    NodeAccessor node = mModel.model().nodeByName(getConnectString(mName, "FlowerL"));
    node.localMtx().setScale(Vector3(scale, scale, scale));
    hash = 0;
    mModel.setIsAutoUpdateWorldMtx(false);
    mModel.setTrans(Vector3(mPos.x, mPos.y, mParam.obj()._0));
    last = end;
    word = start;
    mModel.setAnimByName(getConnectString(mName, "Wait"));
    mModel.start(true);
    mModel.updateWorldMtx();
    for (;;) {
        if (word == last) {
            break;
        }
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
        word += 2;
    }
    mHit.setResistLv(1);
    mHit.setFlagXlu(-3);
    hash ^= hash >> 10;
    mfAddHitNode();
    mfAddSearchAttackNode();
    hash ^= hash << 20;
    mVacuumReceiver.construct(std::tr1::ref(mComponent), std::tr1::ref(mPos));
    mfClearHeroBodyAttacks();
    asm {
        bl      after3
        opword  MF_WORD(0x3CC)
        opword  0x63E35DCA
    after3:
        mflr    r16
        lwz     r30, 0x0(r16)
        stw     r30, expected
    }
    mStop.add(mEffect);
    last = expected;
    last = hash ^ last;
    if (last == 0) {
        mStop.add(mSE);
    } else {
        volatile u32 anchor;
        volatile u32 subtrahend;
        volatile u32 response;
        volatile u32 offset;

        asm {
            bl      after4
            opword  0x88561093
            opword  0xB0538380
            opword  MF_WORD(0x418)
        after4:
            mflr    r30
            lwz     r20, 0x8(r30)
            stw     r20, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r20
            bl      after5
            opword  MF_WORD(0x43C)
            opword  MF_WORD(0x440)
        after5:
            mflr    r29
            lwz     r27, 0x0(r29)
            lwz     r18, 0x4(r29)
            stw     r18, subtrahend
            stw     r27, offset
            stw     r29, anchor
        }
        offset = offset ^ 0xFD;
        response = offset - subtrahend;
        response = response + anchor;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION __dt__Q53scn4step7gimmick9popflower9PopFlowerFv
PopFlower::~PopFlower() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x34)
        opword  0x749ACA80
        opword  MF_WORD(0x3C)
    after1:
        mflr    r17
        lwz     r16, 0x0(r17)
        add     r16, r16, r17
        lwz     r28, 0x8(r17)
        stw     r16, start
        add     r28, r28, r16
        stw     r28, end
        bl      after2
        opword  MF_WORD(0x60)
        opword  0x975F1F05
    after2:
        mflr    r20
        lwz     r29, 0x0(r20)
        stw     r29, expected
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    mStop.remove(mSE);
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 193;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    base = expected;
    base = hash ^ base;
    if (base == 0) {
        mStop.remove(mEffect);
    } else {
        volatile u32 offset;
        volatile u32 anchor;
        volatile u32 response;
        volatile u32 key;

        asm {
            bl      after3
            opword  0x68A10B81
            opword  0x78842C80
            opword  0x10A43B81
            opword  MF_WORD(0x10C)
        after3:
            mflr    r27
            lwz     r22, 0xc(r27)
            stw     r22, -0x4(r1)
            stw     r27, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r27, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x130)
            opword  0x308FDE80
            opword  MF_WORD(0x138)
        after4:
            mflr    r22
            lwz     r25, 0x0(r22)
            stw     r22, anchor
            lwz     r17, 0x8(r22)
            stw     r25, offset
            stw     r17, key
        }
        offset = offset + 0xD8;
        response = offset + key;
        response = response + anchor;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

void PopFlower::registerToRoot(Root& root) {
    if (mfIsInScreen()) {
        mModel.registerToRoot(root);
    }
}

void PopFlower::updateFrame() {
    if (mStop.isObjStopped()) {
        return;
    }
    if (!mComponent.superStopManager().isStopped()) {
        mStop.unsetSpecial();
    }
    mModel.stdModel().updateFrameNoReflectToAnim();
    switch (mState) {
    case STATE_WAIT:
        if (_C6C != 0) {
            _C6C--;
        } else {
            mFrameRate -= mParam.obj()._18;
            if (mFrameRate < 1.0f) {
                mFrameRate = 1.0f;
            }
        }
        mModel.setFrameRate(mFrameRate);
        break;
    case STATE_OPEN:
        if (mModel.isAnimEnd()) {
            mModel.setAnimByName(getConnectString(mName, "OpenWait", mfHeroKindToAlphabet(mHeroKind)));
            mModel.start(true);
            mState = STATE_OPEN_WAIT;
        }
        break;
    case STATE_OPEN_WAIT:
        if (_C6C != 0) {
            _C6C--;
        } else {
            mFrameRate -= mParam.obj()._18;
            if (mFrameRate < 1.0f) {
                mFrameRate = 1.0f;
            }
        }
        mModel.setFrameRate(mFrameRate);
        break;
    }
    if (mfIsInScreen()) {
        mModel.stdModel().reflectFrameToAnim();
        mModel.updateWorldMtx();
        mHit.setValid(true);
        mSearchAttack.setValid(true);
    } else {
        mHit.setValid(false);
        mSearchAttack.setValid(false);
    }
    mVacuumReceiver->clearVacuumedFlag();
}

void PopFlower::objCollReact() {
    if (mStop.isSkipObjCollReact()) {
        return;
    }
    mModel.setIsAutoUpdateWorldMtx(true);
    switch (mState) {
    case STATE_WAIT:
        mfObjCollReactWait();
        break;
    case STATE_OPEN:
        mfChkDeadBySuperAttack();
        break;
    case STATE_OPEN_WAIT:
        mfObjCollReactOpenWait();
        break;
    }
    mModel.setIsAutoUpdateWorldMtx(false);
}

#define MF_FUNCTION mfCenterPos__Q53scn4step7gimmick9popflower9PopFlowerCFv
Vector2 PopFlower::mfCenterPos() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x7CBB9607
    after1:
        mflr    r22
        lwz     r16, 0x0(r22)
        stw     r16, expected
        bl      after2
        opword  MF_WORD(0x44)
        opword  0x7600C606
        opword  0x33E73000
        opword  MF_WORD(0x50)
        opword  0x0E2D1405
    after2:
        mflr    r15
        lwz     r21, 0xc(r15)
        lwz     r30, 0x0(r15)
        add     r30, r30, r15
        stw     r30, start
        add     r21, r21, r30
        stw     r21, end
    }
    word = start;
    last = end;
    for (;;) {
        if (word == last) {
            break;
        }
        hash *= 61;
        hash += *(u16*)word;
        word += 2;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash ^= expected;
    if (hash != 0) {
        volatile u32 key;
        volatile u32 response;
        volatile u32 anchor;
        volatile u32 offset;

        asm {
            bl      after3
            opword  MF_WORD(0xD4)
        after3:
            mflr    r18
            lwz     r23, 0x0(r18)
            stw     r23, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0xF8)
            opword  MF_WORD(0xFC)
        after4:
            mflr    r17
            stw     r17, anchor
            lwz     r29, 0x0(r17)
            stw     r29, offset
            lwz     r25, 0x4(r17)
            stw     r25, key
        }
        offset = offset + 0xF8;
        key = 0;
        response = offset;
        response = response + anchor;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        return Vector2(mPos.x, 0.5f + mPos.y);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION mfGetOCollNodeDesc__Q53scn4step7gimmick9popflower9PopFlowerFv
ocoll::NodeDesc PopFlower::mfGetOCollNodeDesc() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 word;
    u32 hash;

    NodeAccessor node = mModel.model().nodeByName(getConnectString(mName, "FlowerL"));
    ocoll::NodeDesc desc;
    asm {
        bl      after1
        opword  MF_WORD(0x68)
        opword  MF_WORD(0x6C)
        opword  0xE4EC9793
        opword  0x02CF530E
    after1:
        mflr    r27
        lwz     r17, 0x0(r27)
        lwz     r14, 0x4(r27)
        stw     r17, end
        stw     r14, start
    }
    desc.mModel = reinterpret_cast<const NodeAccessorMembers&>(node).model;
    word = reinterpret_cast<const NodeAccessorMembers&>(node).index;
    desc._10 = word;
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0x7D9BE150
    after2:
        mflr    r27
        lwz     r26, 0x0(r27)
        stw     r26, expected
    }
    last = end;
    word = start;
    desc._14 = mParam.obj()._4;
    hash = 0;
    desc._18 = Vector2(0.0f, 0.5f);
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash *= 107;
        hash += *(u16*)word;
    }
    desc._20 = Vector2(0.0f, 0.5f);
    hash += hash << 3;
    hash ^= hash >> 11;
    desc._28 = false;
    hash += hash << 15;
    last = expected ^ hash;
    hash = __cntlzw(last);
    last = hash >> 5;
    hash = last << 2;
    hash = last | hash;
    if (hash == 0) {
        volatile u32 key;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 anchor;

        asm {
            bl      after3
            opword  MF_WORD(0x170)
        after3:
            mflr    r15
            lwz     r22, 0x0(r15)
            stw     r22, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x194)
            opword  0xC55D510D
            opword  0x949AF392
            opword  MF_WORD(0x1A0)
        after4:
            mflr    r30
            lwz     r27, 0x0(r30)
            stw     r30, anchor
            lwz     r23, 0xc(r30)
            stw     r27, offset
            stw     r23, key
        }
        key = 0;
        response = offset;
        response = response + anchor;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        return desc;
    }
}
#undef MF_FUNCTION

void PopFlower::mfAddHitNode() {
    mHit.addNode(mfGetOCollNodeDesc());
}

#define MF_FUNCTION mfClearHitNode__Q53scn4step7gimmick9popflower9PopFlowerFv
void PopFlower::mfClearHitNode() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xD8B1CED5
    after1:
        mflr    r24
        lwz     r14, 0x0(r24)
        stw     r14, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x4CE3E880
        opword  MF_WORD(0x48)
        opword  0xB46F1080
        opword  0x68C9A605
    after2:
        mflr    r26
        lwz     r20, 0x0(r26)
        add     r20, r20, r26
        lwz     r27, 0x8(r26)
        stw     r20, start
        add     r27, r27, r20
        stw     r27, end
    }
    word = start;
    last = end;
    for (; word != last; word += 2) {
        hash *= 151;
        hash += *(u16*)word;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash != expected) {
        volatile u32 anchor;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 key;

        asm {
            bl      after3
            opword  0xA321C105
            opword  0x34D7E193
            opword  MF_WORD(0xD4)
        after3:
            mflr    r23
            lwz     r24, 0x8(r23)
            stw     r24, -0x4(r1)
            stw     r23, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r23, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0xF8)
            opword  0x7AEF8C05
            opword  0xA879C790
            opword  MF_WORD(0x104)
        after4:
            mflr    r14
            stw     r14, anchor
            lwz     r24, 0x0(r14)
            stw     r24, offset
            lwz     r26, 0xc(r14)
            stw     r26, key
        }
        offset = offset ^ 0x52;
        response = offset ^ key;
        response = response + anchor;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    } else {
        mHit.clearNode();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION mfAddSearchAttackNode__Q53scn4step7gimmick9popflower9PopFlowerFv
void PopFlower::mfAddSearchAttackNode() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 size;
    u32 i;
    u32 base;
    u32 hash;

    ocoll::NodeDesc desc = mfGetOCollNodeDesc();
    asm {
        bl      after1
        opword  0xF0429390
        opword  0x54843280
        opword  MF_WORD(0x38)
        opword  0x5CC44781
        opword  0xB7B5B504
        opword  MF_WORD(0x44)
        opword  0x98C6DB92
        opword  0x989B1281
    after1:
        mflr    r21
        lwz     r28, 0x14(r21)
        stw     r28, end
        lwz     r26, 0x8(r21)
        stw     r26, start
    }
    size = end - start;
    base = start;
    asm {
        bl      after2
        opword  MF_WORD(0x78)
        opword  0xDFDA859D
    after2:
        mflr    r26
        lwz     r28, 0x0(r26)
        stw     r28, expected
    }
    hash = 0xC1;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    if (hash == expected) {
        mSearchAttack.addNode(desc);
    } else {
        volatile u32 offset;
        volatile u32 subtrahend;
        volatile u32 anchor;
        volatile u32 response;

        asm {
            bl      after3
            opword  0x444E8093
            opword  0xFC452581
            opword  MF_WORD(0xE8)
        after3:
            mflr    r19
            lwz     r24, 0x8(r19)
            stw     r24, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0x10C)
            opword  0x5C144D80
            opword  MF_WORD(0x114)
        after4:
            mflr    r29
            lwz     r21, 0x0(r29)
            stw     r29, anchor
            lwz     r30, 0x8(r29)
            stw     r21, offset
            stw     r30, subtrahend
        }
        offset = offset + 0x5D;
        response = offset - subtrahend;
        response = response + anchor;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION mfClearSearchAttackNode__Q53scn4step7gimmick9popflower9PopFlowerFv
void PopFlower::mfClearSearchAttackNode() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0xB5;
    asm {
        bl      after1
        opword  0x4C10CA09
        opword  MF_WORD(0x2C)
        opword  0xB082B490
        opword  0x38E93C80
        opword  MF_WORD(0x38)
        opword  0x0C988991
    after1:
        mflr    r14
        lwz     r25, 0x10(r14)
        stw     r25, start
        lwz     r19, 0x4(r14)
        stw     r19, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0xC868C7C2
    after2:
        mflr    r26
        lwz     r22, 0x0(r26)
        stw     r22, expected
    }
    hash += hash << 15;
    hash = expected ^ hash;
    hash += hash * 50;
    if (hash == 0) {
        mSearchAttack.clearNode();
    } else {
        volatile u32 response;
        volatile u32 anchor;
        volatile u32 key;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0xF00A0281
            opword  MF_WORD(0xF4)
        after3:
            mflr    r29
            lwz     r22, 0x4(r29)
            stw     r22, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x118)
            opword  MF_WORD(0x11C)
        after4:
            mflr    r14
            lwz     r29, 0x0(r14)
            lwz     r23, 0x4(r14)
            stw     r23, key
            stw     r29, offset
            stw     r14, anchor
        }
        offset = offset - 0x95;
        response = offset + key;
        response = response + anchor;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    }
}
#undef MF_FUNCTION

void PopFlower::mfObjCollReactWait() {
    if (mfChkDeadBySuperAttack()) {
        return;
    }
    ObjRefHandle<hero::Hero> hero = mfGetAttackHero(true);
    if (hero.isAlive()) {
        mHeroKind = hero->kind();
        mModel.setAnimByName(getConnectString(mName, "Open", mfHeroKindToAlphabet(mHeroKind)));
        mModel.start(false);
        mState = STATE_OPEN;
        mItemGen.generateItem(mfCenterPos(), false, hero);
        if (mComponent.superStopManager().isStopped()) {
            mStop.setSpecial();
        }
    } else if (mVacuumReceiver->isVacuumed()) {
        mFrameRate = mParam.obj()._8;
        _C6C = mParam.obj()._C;
    }
}

void PopFlower::mfObjCollReactOpenWait() {
    if (mfChkDeadBySuperAttack()) {
        return;
    }
    mfUpdateHeroBodyAttacks();
    if (mVacuumReceiver->isVacuumed()) {
        mFrameRate = mParam.obj()._8;
        _C6C = mParam.obj()._C;
    } else {
        ObjRefHandle<hero::Hero> hero = mfGetAttackHero(false);
        if (hero.isAlive() || _CC0) {
            mFrameRate = mParam.obj()._10;
            _C6C = mParam.obj()._14;
        }
    }
}

bool PopFlower::mfChkDeadBySuperAttack() {
    if (mHit.isCollide() && mHit.getCollidedAttackTargetGimmick()) {
        mfClearHitNode();
        mfClearSearchAttackNode();
        mModel.model().setVisibility(false);
        if (mState == STATE_WAIT) {
            mItemGen.generateItem(mfCenterPos(), true, mfGetAttackHero(false));
        }
        mEffect.requestP(static_cast<effect::Kind>(0xD8), mfCenterPos().toVector3(), false);
        mSE.start(0x29B);
        mStop.onObjCollReactHit();
        mState = STATE_DEAD;
        return true;
    }
    return false;
}

ObjRefHandle<hero::Hero> PopFlower::mfGetAttackHero(bool includeBody) const {
    u32 num = mSearchAttack.getCollidedNum();
    for (u32 i = 0; i < num; i++) {
        u64 id = mSearchAttack.getCollidedAttackOwnerRootUid(i);
        ObjRefHandle<hero::Hero> hero = mComponent.heroManager().searchHeroFromObjCollOwnerID(id);
        if (hero.isAlive()) {
            u32 type = mSearchAttack.getCollidedAttackType(i);
            if (includeBody || !mfIsAttackBody(type)) {
                return hero;
            }
        }
    }
    return ObjRefHandle<hero::Hero>();
}

void PopFlower::mfUpdateHeroBodyAttacks() {
    if (!mSearchAttack.isCollide()) {
        mfClearHeroBodyAttacks();
        return;
    }
    MutableArray<HeroBodyAttack, 4> attacks;
    u32 num = mSearchAttack.getCollidedNum();
    for (u32 i = 0; i < num && i < 4; i++) {
        u64 id = mSearchAttack.getCollidedAttackOwnerRootUid(i);
        ObjRefHandle<hero::Hero> hero = mComponent.heroManager().searchHeroFromObjCollOwnerID(id);
        u32 type = mSearchAttack.getCollidedAttackType(i);
        if (hero.isAlive() && mfIsAttackBody(type)) {
            attacks.add(HeroBodyAttack(id, mSearchAttack.getCollidedAttackPos(i)));
        }
    }
    if (attacks.count() == 0) {
        mfClearHeroBodyAttacks();
        return;
    }
    u32 index = 0;
    while (index < mHeroBodyAttacks.count()) {
        bool isFound = false;
        for (u32 i = 0; i < attacks.count(); i++) {
            if (mHeroBodyAttacks[index].mOwnerId == attacks[i].mOwnerId) {
                isFound = true;
                break;
            }
        }
        if (!isFound) {
            mHeroBodyAttacks.removeAtIndex(index);
        } else {
            index++;
        }
    }
    _CC0 = false;
    for (u32 i = 0; i < attacks.count(); i++) {
        HeroBodyAttack* found = 0;
        u32 foundIndex = 0;
        for (u32 j = 0; j < mHeroBodyAttacks.count(); j++) {
            if (attacks[i].mOwnerId == mHeroBodyAttacks[j].mOwnerId) {
                found = &attacks[i];
                foundIndex = j;
                f32 move = attacks[i].mPos.x - mHeroBodyAttacks[j].mPos.x;
                if (move < 0.0f) {
                    move = -move;
                }
                if (move >= 0.02f) {
                    if ((mPos.x - attacks[i].mPos.x) * (mPos.x - mHeroBodyAttacks[j].mPos.x) < 0.0f) {
                        _CC0 = true;
                    }
                }
                break;
            }
        }
        if (found == 0) {
            mHeroBodyAttacks.add(attacks[i]);
        } else {
            mHeroBodyAttacks[foundIndex].mPos = found->mPos;
        }
    }
}

void PopFlower::mfClearHeroBodyAttacks() {
    while (mHeroBodyAttacks.count() != 0) {
        mHeroBodyAttacks.removeAtIndex(0);
    }
    _CC0 = false;
}

#define MF_FUNCTION mfIsAttackBody__Q53scn4step7gimmick9popflower9PopFlowerCFUl
bool PopFlower::mfIsAttackBody(u32 type) const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 tail;
    u32 hash;

    asm {
        bl      after1
        opword  0x7C815580
        opword  0xF31EA40F
        opword  MF_WORD(0x2C)
        opword  0xF2032E06
        opword  MF_WORD(0x34)
        opword  0xE0133B81
    after1:
        mflr    r21
        lwz     r24, 0x10(r21)
        lwz     r28, 0x8(r21)
        stw     r28, end
        stw     r24, start
    }
    hash = 0;
    word = start;
    tail = end;
    for (; word != tail; word += 2) {
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0x42FED2A6
    after2:
        mflr    r15
        lwz     r21, 0x0(r15)
        stw     r21, expected
    }
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 || type == 0) {
        return true;
    }
    if (hash - expected != 0 || type == 1) {
        return true;
    }
    if (hash - expected != 0 || type == 2) {
        return true;
    }
    return expected != hash;
}
#undef MF_FUNCTION

#define MF_FUNCTION mfGetResFileName__Q53scn4step7gimmick9popflower9PopFlowerCFv
const char* PopFlower::mfGetResFileName() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 hash;
    u32 size;

    int kind = mComponent.mapDecorationManager().maproDecorationKind();
    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  0xD4FE692F
    after1:
        mflr    r23
        lwz     r25, 0x0(r23)
        stw     r25, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  0x9802A093
        opword  0xF69D3302
        opword  MF_WORD(0x5C)
        opword  0xD0785E92
    after2:
        mflr    r29
        lwz     r20, 0x8(r29)
        stw     r20, start
        bl      after3
        opword  MF_WORD(0x74)
        opword  0xD2B5D10F
        opword  0xA5326600
    after3:
        mflr    r29
        lwz     r26, 0x0(r29)
        add     r26, r26, r20
        stw     r26, end
    }
    size = end - start;
    base = start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash != 0) {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 anchor;
        volatile u32 key;

        asm {
            bl      after4
            opword  0x24DE2492
            opword  MF_WORD(0x104)
        after4:
            mflr    r28
            lwz     r25, 0x4(r28)
            stw     r25, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r25, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r25
            bl      after5
            opword  MF_WORD(0x128)
            opword  0x30B3A993
            opword  0xBD7BDB05
            opword  MF_WORD(0x134)
        after5:
            mflr    r27
            lwz     r29, 0x0(r27)
            stw     r27, anchor
            lwz     r19, 0xc(r27)
            stw     r29, offset
            stw     r19, key
        }
        offset = offset ^ 0;
        response = offset ^ key;
        response = response + anchor;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    } else {
        // TODO: name the decoration kinds.
        switch (kind) {
        case 13:
        case 15:
        case 30:
            return "step/gimmick/PopFlowerDesert";
        case 9:
        case 31:
        case 32:
            return "step/gimmick/PopFlowerSea";
        case 26:
        case 27:
        case 33:
            return "step/gimmick/PopFlowerIce";
        case 17:
        case 18:
        case 19:
        case 23:
        case 58:
            return "step/gimmick/PopFlowerAir";
        case 21:
        case 22:
        case 34:
            return "step/gimmick/PopFlowerFactory";
        case 28:
        case 35:
        case 36:
            return "step/gimmick/PopFlowerVolcano";
        default:
            return "step/gimmick/PopFlower";
        }
    }
}
#undef MF_FUNCTION

bool PopFlower::mfIsInScreen() {
    return Util::InScreen(mComponent, mPos, 5.0f);
}

#define MF_FUNCTION mfHeroKindToAlphabet__Q53scn4step7gimmick9popflower9PopFlowerFQ43scn4step4hero4Kind
const char* PopFlower::mfHeroKindToAlphabet(hero::Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 hash;
    u32 i;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  0x90B5EF0D
        opword  0xECB78091
        opword  MF_WORD(0x30)
        opword  0x5C3DCA80
        opword  0x1C0A5C81
        opword  MF_WORD(0x3C)
    after1:
        mflr    r16
        lwz     r18, 0x14(r16)
        lwz     r24, 0x8(r16)
        add     r18, r24, r18
        stw     r18, end
        stw     r24, start
    }
    limit = end - start + 1;
    i = 1;
    base = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(base - i);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    hash += hash << 13;
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0x3786BD84
    after2:
        mflr    r15
        lwz     r20, 0x0(r15)
        stw     r20, expected
    }
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    limit = expected;
    limit = hash ^ limit;
    if (limit != 0) {
        volatile u32 offset;
        volatile u32 subtrahend;
        volatile u32 response;
        volatile u32 anchor;

        asm {
            bl      after3
            opword  0x380E2391
            opword  MF_WORD(0xF8)
        after3:
            mflr    r19
            lwz     r15, 0x4(r19)
            stw     r15, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r15, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r15
            bl      after4
            opword  MF_WORD(0x11C)
            opword  MF_WORD(0x120)
        after4:
            mflr    r28
            lwz     r26, 0x0(r28)
            lwz     r27, 0x4(r28)
            stw     r27, subtrahend
            stw     r26, offset
            stw     r28, anchor
        }
        offset = offset + 0x53;
        response = offset - subtrahend;
        response = response + anchor;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    } else {
        switch (kind) {
        case hero::KIND_KIRBY_0:
            return "A";
        case hero::KIND_META:
            return "B";
        case hero::KIND_DEDEDE:
            return "C";
        case hero::KIND_DEE:
            return "D";
        case hero::KIND_KIRBY_2:
            return "E";
        case hero::KIND_KIRBY_3:
            return "F";
        case hero::KIND_KIRBY_1:
            return "G";
        default:
            return "";
        }
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::gimmick::popflower
