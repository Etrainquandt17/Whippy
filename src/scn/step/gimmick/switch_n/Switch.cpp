#include "scn/step/gimmick/switch_n/Switch.h"

#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "hel/common/FixedString.h"
#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "mintglue/VectorInline.h"
#include "nw4r/math/math_arithmetic.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Manager.h"
#include "scn/step/chara/Location.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/gimmick/SwitchReceiverManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/map/BinGmkGeneralEntry.h"
#include "scn/step/map/MemManager.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace {

// TODO: what g3d::NodeAccessor holds; g3d/NodeAccessor.h has it opaque.
struct NodeAccessorMembers {
    util::ObjRefHandle<g3d::Model> model;
    u32 index;
};

}

namespace {

inline f32 t_distance(const Vector2& a, const Vector2& b) {
    f32 dx = a.x - b.x;
    f32 dy = a.y - b.y;
    f32 distance = dx * dx + dy * dy;
    return nw4r::math::FSqrt(distance);
}

#define MF_FUNCTION getConnectString__24_unnamed_Switch_prt_cpp_FPCcPCc
hel::common::FixedString<40> getConnectString(const char* a, const char* b) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  0x4C034780
        opword  0xB84D6981
        opword  MF_WORD(0x38)
        opword  0x3830F890
        opword  0xCC71FF00
        opword  MF_WORD(0x44)
        opword  0x64F8950E
    after1:
        mflr    r16
        lwz     r25, 0x8(r16)
        lwz     r24, 0x14(r16)
        stw     r25, end
        stw     r24, start
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    last--;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 107;
        hash += *(u16*)(last - i);
        i += 2;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0xF655BDAE
    after2:
        mflr    r30
        lwz     r14, 0x0(r30)
        stw     r14, expected
    }
    limit = hash << 15;
    hash += limit;
    limit = expected;
    limit = hash ^ limit;
    if (limit != 0) {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 anchor;
        volatile u32 key;

        asm {
            bl      after3
            opword  0xBCEC8D80
            opword  MF_WORD(0xE0)
        after3:
            mflr    r18
            lwz     r23, 0x4(r18)
            stw     r23, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0x104)
            opword  MF_WORD(0x108)
        after4:
            mflr    r15
            lwz     r20, 0x4(r15)
            stw     r20, key
            lwz     r20, 0x0(r15)
            stw     r15, anchor
            stw     r20, offset
        }
        offset = offset ^ 0xC7;
        response = offset ^ key;
        response = response + anchor;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    } else {
        return hel::common::FixedStringIN<char, 40>::FromFormat("%s%s", a, b);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION getConnectString__24_unnamed_Switch_prt_cpp_FPCcPCcPCc
hel::common::FixedString<40> getConnectString(const char* a, const char* b, const char* c) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 anchor;
    volatile u32 subtrahend;
    u32 word;
    u32 hash;
    u32 tail;

    asm {
        bl      after1
        opword  MF_WORD(0x30)
    after1:
        mflr    r29
        lwz     r24, 0x0(r29)
        add     r24, r24, r29
        stw     r24, start
        bl      after2
        opword  MF_WORD(0x48)
    after2:
        mflr    r29
        lwz     r15, 0x0(r29)
        add     r24, r24, r15
        stw     r24, end
    }
    tail = end;
    word = start;
    hash = 0;
    word -= 2;
    while (word != tail - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    asm {
        bl      after3
        opword  MF_WORD(0xAC)
        opword  0x649E840D
    after3:
        mflr    r22
        lwz     r19, 0x0(r22)
        stw     r19, expected
    }
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash = (expected & ~hash) | (hash & ~expected);
    hash -= hash >> 2;
    if (hash == 0) {
        return hel::common::FixedStringIN<char, 40>::FromFormat("%s%s%s", a, b, c);
    }
    asm {
        bl      after4
        opword  0x94AC6380
        opword  0x70471392
        opword  MF_WORD(0x14C)
    after4:
        mflr    r29
        lwz     r16, 0x8(r29)
        stw     r16, -0x4(r1)
        stw     r29, 0x0(r1)
        stw     r16, -0x4(r1)
        stw     r29, -0x8(r1)
        mtlr    r16
        bl      after5
        opword  MF_WORD(0x170)
        opword  0xC9068905
        opword  MF_WORD(0x178)
    after5:
        mflr    r28
        lwz     r24, 0x0(r28)
        lwz     r25, 0x8(r28)
        stw     r25, subtrahend
        stw     r24, offset
        stw     r28, anchor
    }
    response = offset - subtrahend;
    response = response + anchor;
    asm {
        lwz     r23, response
        mtlr    r23
        blr
    }
}
#undef MF_FUNCTION

}

namespace scn {
namespace step {
namespace gimmick {
namespace switch_n {

#define MF_FUNCTION __ct__Q53scn4step7gimmick8switch_n6SwitchFRCQ43scn4step3map18BinGmkGeneralEntryRQ33scn4step9ComponentPCc
Switch::Switch(const map::BinGmkGeneralEntry& entry, Component& component, const char* name)
    : mParam("step/gimmick/Switch")
    , mComponent(component)
    , mPos(entry._4.toMaproPos().toWorldPos())
    , _18(entry._1C)
    , mName(name)
    , mModel(component, "step/gimmick/Switch", getConnectString("TopL", mName), true, false)
    , mStop(component)
    , mEffect(component)
    , _5FC()
    , mOwner(component.objCollManager(), 2, component.mapMemManager().allocator())
    , mHit(component.objCollManager(), mOwner)
    , mSearchAttack(component.objCollManager(), mOwner)
    , _C68(false)
    , _C69(false)
    , _C6A(false)
    , _C6C()
    , _C74(0)
    , _C78(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x170)
        opword  0x0F7CF6D9
    after1:
        mflr    r19
        lwz     r20, 0x0(r19)
        stw     r20, expected
    }
    mModel.setTrans(mPos.toVector3());
    hash = 0xC5;
    mModel.setAnimByName(getConnectString("TopL", mName, "Wait"));
    asm {
        bl      after2
        opword  0x36BD8305
        opword  0xB1222E0F
        opword  MF_WORD(0x1CC)
        opword  MF_WORD(0x1D0)
    after2:
        mflr    r26
        lwz     r15, 0xc(r26)
        lwz     r30, 0x8(r26)
        stw     r30, start
        stw     r15, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
        i += 2;
    }
    mModel.start(expected == hash);
    mEffect.changeLayer(core::DRAW_LAYER_KIND_8);
    hitOn();
    searchAttackOff();
    mStop.add(mEffect);
    mStop.add(_5FC);
}
#undef MF_FUNCTION

Switch::~Switch() {
    mStop.remove(mEffect);
    mStop.remove(_5FC);
}

void Switch::registerToRoot(g3d::Root& root) {
    mModel.registerToRoot(root);
}

void Switch::updateFrame() {
    if (mStop.isObjStopped()) {
        return;
    }
    if (_C74 == 2 && mStop.isSuperStopped()) {
        return;
    }
    mModel.updateFrame();
    if (_C6A) {
        _C6C.advanceIfNotEnd();
    }
    switch (_C74) {
    case 0:
        if (isChangeToOn()) {
            _C74 = 1;
            mModel.setAnimByName(getConnectString("TopL", mName, "Push"));
            mModel.start(false);
            mEffect.requestP(static_cast<effect::Kind>(0x1F7), mPos.toVector3(), false);
            _5FC.start(0x172);
            onChangeOffToOn();
        }
        break;
    case 1:
        if (mModel.isAnimEnd()) {
            _C74 = 2;
            onChangeToOn();
        }
        break;
    case 2:
        if (isChangeToOff()) {
            _C74 = 3;
            mModel.setAnimByName(getConnectString("TopL", mName, "Up"));
            mModel.start(false);
            onChangeOnToOff();
        }
        break;
    case 3:
        if (mModel.isAnimEnd()) {
            _C74 = 0;
            mModel.setAnimByName(getConnectString("TopL", mName, "Wait"));
            mModel.start(true);
            onChangeToOff();
        }
        break;
    }
}

bool Switch::isChangeToOn() {
    return false;
}

void Switch::onChangeOffToOn() {}

void Switch::onChangeToOn() {}

bool Switch::isChangeToOff() {
    return false;
}

void Switch::onChangeOnToOff() {}

void Switch::onChangeToOff() {}

void Switch::objCollReact() {
    if (mStop.isSkipObjCollReact()) {
        return;
    }
    _C78 = false;
    if (_C68 && mHit.isCollide()) {
        if (mHit.getCollidedAttackTargetGimmick()) {
            _C78 = true;
        }
        switch (mHit.getCollidedAttackType()) {
        case 0:
        case 1:
        case 2:
        case 0xF:
        case 0x10:
        case 0x253:
            _C78 = true;
            break;
        }
    }
    if (_C69 && mSearchAttack.isCollide()) {
        u32 num = mSearchAttack.getCollidedNum();
        for (u32 i = 0; i < num; i++) {
            if (mSearchAttack.getCollidedAttackTargetGimmick(i)) {
                _C78 = true;
            }
            switch (mSearchAttack.getCollidedAttackType(i)) {
            case 0:
            case 1:
            case 2:
            case 0xF:
            case 0x10:
            case 0x253:
                _C78 = true;
                break;
            }
        }
    }
    {
        Vector2 offset(0.0f, 0.4f);
        util::ObjRefHandle<carryitem::CarryItem> carried =
            mComponent.carryItemManager().chkCollideSwitch(mPos + offset);
        if (carried.ptr() != 0 && carried->kind() != 0) {
            _C78 = true;
        }
    }
    for (u32 i = 0; i < mComponent.heroManager().getPlayerCount(); i++) {
        hero::Hero& hero = mComponent.heroManager().getPlayerByIndex(i);
        if (hero.stateChecker().is_59()) {
            if (t_distance(hero.location().pos().getXY(), mPos) < mParam->_18) {
                _C78 = true;
                break;
            }
        }
    }
    if (_C78) {
        mStop.onObjCollReactHit();
    }
}

bool Switch::checkHit() const {
    return _C78;
}

void Switch::sendSwitchOn() {
    mComponent.gimmickManager().switchReceiverManager().onSwitchOn(_18);
}

void Switch::sendSwitchOff() {
    mComponent.gimmickManager().switchReceiverManager().onSwitchOff(_18);
}

void Switch::sendSwitchToggle() {
    mComponent.gimmickManager().switchReceiverManager().onSwitchToggle(_18);
}

#define MF_FUNCTION hitOn__Q53scn4step7gimmick8switch_n6SwitchFv
void Switch::hitOn() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 tail;
    u32 word;
    u32 hash;

    ocoll::NodeDesc desc = mfGetOCNodeDesc(mParam->_10);
    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x48)
        opword  0x80F10780
        opword  MF_WORD(0x50)
        opword  0xA0B1010F
    after1:
        mflr    r20
        lwz     r16, 0x8(r20)
        lwz     r18, 0x0(r20)
        add     r18, r18, r20
        stw     r18, start
        add     r16, r16, r18
        stw     r16, end
    }
    mHit.addNode(desc);
    tail = end;
    word = start;
    word -= 2;
    while (word != tail - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x01000193;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xB8)
        opword  0x744D069B
    after2:
        mflr    r18
        lwz     r24, 0x0(r18)
        stw     r24, expected
    }
    _C68 = expected == hash;
}
#undef MF_FUNCTION

void Switch::hitOff() {
    mHit.clearNode();
    _C68 = false;
}

void Switch::searchAttackOn() {
    ocoll::NodeDesc desc = mfGetOCNodeDesc(mParam->_14);
    mSearchAttack.addNode(desc);
    _C69 = true;
}

#define MF_FUNCTION searchAttackOff__Q53scn4step7gimmick8switch_n6SwitchFv
void Switch::searchAttackOff() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash = 0x811C9DDB;

    asm {
        bl      after1
        opword  0x082E7680
        opword  0xB44F6190
        opword  MF_WORD(0x2C)
        opword  MF_WORD(0x30)
        opword  0xBC68C790
        opword  0x68DD7280
    after1:
        mflr    r26
        lwz     r23, 0x8(r26)
        lwz     r16, 0xc(r26)
        stw     r16, end
        stw     r23, start
        bl      after2
        opword  MF_WORD(0x54)
        opword  0x3687B755
    after2:
        mflr    r23
        lwz     r25, 0x0(r23)
        stw     r25, expected
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
        i += 2;
    }
    mSearchAttack.clearNode();
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    _C69 = expected != hash;
}
#undef MF_FUNCTION

bool Switch::isStartCount() const {
    return _C6A;
}

void Switch::startCount(u32 frame) {
    _C6A = true;
    _C6C.reset(frame);
}

void Switch::stopCount() {
    _C6A = false;
}

bool Switch::isCountEnd() const {
    bool isEnd = false;
    if (_C6A && _C6C.isEnd()) {
        isEnd = true;
    }
    return isEnd;
}

#define MF_FUNCTION mfGetOCNodeDesc__Q53scn4step7gimmick8switch_n6SwitchFf
ocoll::NodeDesc Switch::mfGetOCNodeDesc(f32 radius) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 hash;
    u32 size;
    u32 i;

    g3d::NodeAccessor node = mModel.model().nodeByName(getConnectString("TopL", mName));
    ocoll::NodeDesc desc;
    size = 0x811D0000;
    hash = size - 0x623B;
    asm {
        bl      after1
        opword  MF_WORD(0x7C)
        opword  0x104674BA
    after1:
        mflr    r18
        lwz     r16, 0x0(r18)
        stw     r16, expected
    }
    desc.mModel = reinterpret_cast<const NodeAccessorMembers&>(node).model;
    size = reinterpret_cast<const NodeAccessorMembers&>(node).index;
    desc._10 = size;
    desc._14 = radius;
    asm {
        bl      after2
        opword  0xDF90B106
        opword  0xA2D15203
        opword  MF_WORD(0xB4)
        opword  0xACCAB293
        opword  0x5CA7A307
        opword  MF_WORD(0xC0)
        opword  0x3C865980
    after2:
        mflr    r15
        lwz     r16, 0x8(r15)
        lwz     r20, 0x14(r15)
        stw     r20, end
        stw     r16, start
    }
    base = start;
    size = end - base;
    desc._18 = Vector2(mParam->_0);
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
    }
    hash += hash << 13;
    desc._20 = Vector2(mParam->_8);
    hash ^= hash >> 7;
    hash += hash << 3;
    desc._28 = false;
    hash ^= hash >> 17;
    hash += hash << 5;
    if ((hash ^ expected) != 0) {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 key;
        volatile u32 anchor;

        asm {
            bl      after3
            opword  0x409A4580
            opword  MF_WORD(0x1A4)
        after3:
            mflr    r23
            lwz     r18, 0x4(r23)
            stw     r18, -0x4(r1)
            stw     r23, 0x0(r1)
            stw     r18, -0x4(r1)
            stw     r23, -0x8(r1)
            mtlr    r18
            bl      after4
            opword  MF_WORD(0x1C8)
            opword  MF_WORD(0x1CC)
        after4:
            mflr    r22
            lwz     r23, 0x0(r22)
            lwz     r27, 0x4(r22)
            stw     r27, key
            stw     r23, offset
            stw     r22, anchor
        }
        offset = offset ^ 0x68;
        response = offset + key;
        response = response + anchor;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    } else {
        return desc;
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::gimmick::switch_n
