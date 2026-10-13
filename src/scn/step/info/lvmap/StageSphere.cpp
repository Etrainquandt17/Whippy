#include "scn/step/info/lvmap/StageSphere.h"

#include "hel/common/ExplicitSingleton.h"
#include "hel/math/Vector2.h"
#include "hid/HIDManager.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/ContextSphere.h"
#include "scn/step/StageKindUtil.h"
#include "scn/step/camera/CameraAccessor.h"
#include "util/ObjList.h"

namespace {

#define MF_FUNCTION isGetDemoDebug__29_unnamed_StageSphere_prt_cpp_Fv
bool isGetDemoDebug() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 key;
    u32 hash;
    u32 hold;
    u32 i;
    u32 limit;
    u32 last;

    hold = hel::common::ExplicitSingleton<hid::HIDManager>::Object().debugGC(3).button().hold()
        | (hel::common::ExplicitSingleton<hid::HIDManager>::Object().debugGC(2).button().hold()
            | (hel::common::ExplicitSingleton<hid::HIDManager>::Object().debugGC(0).button().hold()
                | hel::common::ExplicitSingleton<hid::HIDManager>::Object().debugGC(1).button().hold()));
    hash = 0xC5;
    asm {
        bl      after1
        opword  MF_WORD(0xB8)
        opword  0x3BE98C72
    after1:
        mflr    r29
        lwz     r26, 0x0(r29)
        stw     r26, expected
        bl      after2
        opword  MF_WORD(0xD0)
        opword  0xCC01E591
        opword  0xB88F1180
        opword  MF_WORD(0xDC)
        opword  0xBC4B1F92
        opword  0x345A3393
    after2:
        mflr    r21
        lwz     r20, 0x0(r21)
        lwz     r17, 0xc(r21)
        add     r20, r20, r21
        add     r17, r17, r20
        stw     r20, start
        stw     r17, end
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - i);
        i += 2;
    }
    limit = hash << 13;
    hash += limit;
    limit = hash >> 7;
    hash ^= limit;
    limit = hash << 3;
    hash += limit;
    limit = hash >> 17;
    hash ^= limit;
    limit = hash << 5;
    hash += limit;
    limit = expected;
    limit = hash - limit;
    if (limit != 0) {
        asm {
            bl      after3
            opword  0x6B54A205
            opword  0x0C8AB880
            opword  MF_WORD(0x18C)
        after3:
            mflr    r21
            lwz     r28, 0x8(r21)
            stw     r28, -0x4(r1)
            stw     r21, 0x0(r1)
            stw     r28, -0x4(r1)
            stw     r21, -0x8(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0x1B0)
            opword  MF_WORD(0x1B4)
        after4:
            mflr    r21
            stw     r21, mfBase
            lwz     r18, 0x0(r21)
            stw     r18, offset
            lwz     r22, 0x4(r21)
            stw     r22, key
        }
        response = offset ^ key;
        response = response + mfBase;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        return (hold & 0x400) != 0;
    }
}
#undef MF_FUNCTION

}

namespace scn {
namespace step {
namespace info {
namespace lvmap {

#define MF_FUNCTION __ct__Q53scn4step4info5lvmap11StageSphereFRQ23mem10IAllocatorRCQ23lyt12PaneAccessorRQ33scn4step9Component
StageSphere::StageSphere(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Component& component)
    : mComponent(component)
    , _4(3)
    , _8(0x27)
    , _14(0)
    , _18(false)
    , _90(lyt::LayoutContext("step/lvmap/Main", "SphereBg", allocator))
    , _220(allocator, _90.pane("SphereBaseN"), component, false, true)
    , _3D8(lyt::LayoutContext("step/lvmap/Main", "SphereLBg", allocator))
    , _568(allocator, _3D8.pane("SphereBaseN"), component, true, true) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0xC1;
    _90.setParent(parent);
    asm {
        bl      after1
        opword  MF_WORD(0x130)
        opword  0xF0110513
    after1:
        mflr    r28
        lwz     r24, 0x0(r28)
        stw     r24, expected
        bl      after2
        opword  MF_WORD(0x148)
        opword  MF_WORD(0x14C)
    after2:
        mflr    r19
        lwz     r26, 0x0(r19)
        lwz     r21, 0x4(r19)
        stw     r26, end
        stw     r21, start
    }
    _3D8.setParent(parent);
    i = 1;
    base = start;
    limit = end - base + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(base + i - 1);
        i += 2;
    }
    normalPanelVisible(false);
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    bossPanelVisible(expected != hash);
}
#undef MF_FUNCTION

void StageSphere::updateFrame() {
    _90.updateFrame();
    _220.updateFrame();
    _3D8.updateFrame();
    _568.updateFrame();
    switch (_4) {
    case 0:
        stateAppear();
        break;
    case 1:
        stateSphereGetWait();
        break;
    case 2:
        stateSphereGet();
        break;
    }
}

void StageSphere::bgStartAnim(const hel::math::Vector3& pos, StageKind stage, bool isStart) {
    if (stage == 0x20 || stage == 0x24) {
        return;
    }
    if (isGetDemoDebug() && !StageKindUtil::IsBossStage(stage)) {
        getDemo(pos, stage);
        return;
    }
    _720 = pos;
    _18 = StageKindUtil::IsBossStage(stage);
    if (!_18) {
        normalPanelVisible(true);
        bossPanelVisible(false);
        _220.updateSphereStateForLvMap(stage);
        adjustBgSize();
        centerBase();
        if (isStart) {
            _90.play("Start", "Wait");
        } else {
            _90.play("Wait");
        }
    } else {
        normalPanelVisible(false);
        bossPanelVisible(true);
        _568.updateSphereStateForLvMap(stage);
        _568.setOffset(hel::math::Vector3(-_568.width() / 2.0f, 0.0f, 0.0f));
        if (isStart) {
            _3D8.play("Start", "Wait");
        } else {
            _3D8.play("Wait");
        }
    }
    _4 = 3;
}

void StageSphere::appear(const hel::math::Vector3& pos, StageKind stage) {
    bgStartAnim(pos, stage, true);
}

void StageSphere::wait(const hel::math::Vector3& pos, StageKind stage) {
    bgStartAnim(pos, stage, false);
}

void StageSphere::disappear() {
    if (!_18) {
        _90.play("End");
    } else {
        _3D8.play("End");
    }
    _4 = 3;
}

void StageSphere::getDemo(const hel::math::Vector3& pos, StageKind stage) {
    if (StageKindUtil::IsBossStage(stage)) {
        appear(pos, stage);
    } else {
        _720 = pos;
        _8 = stage;
        normalPanelVisible(true);
        bossPanelVisible(false);
        _220.updateSphereStateForGetDemo(stage);
        adjustBgSize();
        centerBase();
        if (getNextFlashSphere(0) != 0xFFFFFFFF) {
            _4 = 0;
            _90.play("Start");
        } else {
            _4 = 3;
            _90.play("Start", "Wait");
        }
    }
}

bool StageSphere::isDemoEnd() const {
    return _4 == 3;
}

void StageSphere::constraintPos() {
    hel::math::Vector2 pos = mComponent.cameraAccessor().toLayoutPos(camera::KIND_0, _720);
    hel::math::Vector3 trans = pos.toVector3() + hel::math::Vector3(0.0f, 120.0f, 0.0f);
    _90.rootPane().setTrans(trans);
    _3D8.rootPane().setTrans(trans);
}

#define MF_FUNCTION stateAppear__Q53scn4step4info5lvmap11StageSphereFv
void StageSphere::stateAppear() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash = 0x811C9E07;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
    after1:
        mflr    r27
        lwz     r16, 0x0(r27)
        add     r16, r16, r27
        stw     r16, start
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x48678D91
        opword  0x1815E380
    after2:
        mflr    r27
        lwz     r17, 0x0(r27)
        add     r16, r16, r17
        stw     r16, end
        bl      after3
        opword  MF_WORD(0x5C)
        opword  0x269FB4EC
    after3:
        mflr    r19
        lwz     r28, 0x0(r19)
        stw     r28, expected
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001A7;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0 && _90.isAnimEnd()) {
        _4 = 1;
        _14 = 0;
        _C.reset(20);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION stateSphereGetWait__Q53scn4step4info5lvmap11StageSphereFv
void StageSphere::stateSphereGetWait() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 size;
    u32 tail;
    u32 hash = 0x811C9DC5;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x682B662F
    after1:
        mflr    r26
        lwz     r24, 0x0(r26)
        stw     r24, expected
        bl      after2
        opword  0x274EFF08
        opword  MF_WORD(0x40)
        opword  0x85770E0B
        opword  0xE49BAC93
        opword  MF_WORD(0x4C)
        opword  0x84C75280
        opword  0x9C187481
    after2:
        mflr    r15
        lwz     r17, 0x10(r15)
        lwz     r28, 0x4(r15)
        stw     r28, end
        stw     r17, start
    }
    _C.advance();
    tail = end;
    size = tail - start;
    i = -1;
    last = tail - 1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(last - i);
        hash *= 0x01000181;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 || _C.isEnd()) {
        _14 = getNextFlashSphere(_14);
        if (_14 != 0xFFFFFFFF) {
            _4 = 2;
        } else {
            _4 = 3;
            _90.play("Wait");
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION stateSphereGet__Q53scn4step4info5lvmap11StageSphereFv
void StageSphere::stateSphereGet() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 key;
    volatile u32 offset;
    u32 t2;
    u32 hash;
    u32 t1;
    u32 p;
    u32 stop;

    asm {
        bl      after1
        opword  0x2866E591
        opword  MF_WORD(0x28)
        opword  0xFF122F05
        opword  MF_WORD(0x30)
        opword  0x34FD4B81
    after1:
        mflr    r15
        lwz     r27, 0x4(r15)
        stw     r27, end
        lwz     r27, 0xc(r15)
        stw     r27, start
    }
    _220.startGetAnim(_14);
    hash = 0x811C9E29;
    _14++;
    p = start;
    stop = end;
    for (; p != stop; p += 2) {
        hash ^= *(u16*)p;
        hash *= 0x010001AB;
    }
    _1C.start(0x4B9);
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0x6BFE2FEA
    after2:
        mflr    r29
        lwz     r14, 0x0(r29)
        stw     r14, expected
    }
    _C.reset(5);
    t1 = expected;
    t1 = t1 & ~hash;
    t2 = expected;
    t2 = hash & ~t2;
    hash = t1 | t2;
    t2 = hash << 8;
    hash = hash | t2;
    if (hash == 0) {
        _4 = 1;
        return;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xFC)
    after3:
        mflr    r25
        lwz     r20, 0x0(r25)
        stw     r20, -0x4(r1)
        stw     r25, 0x0(r1)
        stw     r20, -0x4(r1)
        stw     r25, -0x8(r1)
        mtlr    r20
        bl      after4
        opword  MF_WORD(0x120)
        opword  MF_WORD(0x124)
    after4:
        mflr    r26
        lwz     r23, 0x0(r26)
        lwz     r27, 0x4(r26)
        stw     r27, key
        stw     r23, offset
        stw     r26, mfBase
    }
    offset = offset ^ 0x6F;
    response = offset ^ key;
    response = response + mfBase;
    asm {
        lwz     r23, response
        mtlr    r23
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION normalPanelVisible__Q53scn4step4info5lvmap11StageSphereFb
void StageSphere::normalPanelVisible(bool visible) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 mfBase;
    volatile u32 response;
    volatile u32 offset;
    u32 p;
    u32 stop;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
    after1:
        mflr    r29
        lwz     r25, 0x0(r29)
        add     r25, r25, r29
        stw     r25, start
        bl      after2
        opword  MF_WORD(0x40)
        opword  0xE4BB5E80
    after2:
        mflr    r29
        lwz     r20, 0x0(r29)
        add     r25, r25, r20
        stw     r25, end
    }
    hash = 0;
    p = start;
    stop = end;
    asm {
        bl      after3
        opword  MF_WORD(0x68)
        opword  0x9817DE8A
    after3:
        mflr    r20
        lwz     r28, 0x0(r20)
        stw     r28, expected
    }
    for (; p != stop; p += 2) {
        hash += *(u16*)p;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    _90.rootPane().setVisibility(visible);
    stop = hash << 13;
    hash += stop;
    stop = hash >> 7;
    hash ^= stop;
    stop = hash << 3;
    hash += stop;
    stop = hash >> 17;
    hash ^= stop;
    stop = hash << 5;
    hash += stop;
    stop = expected;
    hash ^= stop;
    if (hash != 0) {
        asm {
            bl      after4
            opword  MF_WORD(0x104)
            opword  0xEC537591
        after4:
            mflr    r15
            addi    r25, r15, 0x14
            mtlr    r25
            lwz     r18, 0x0(r15)
            stw     r18, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r15, 0x4(r1)
            blrl
            bl      after5
            opword  MF_WORD(0x130)
            opword  0x48049480
            opword  MF_WORD(0x138)
        after5:
            mflr    r21
            lwz     r25, 0x0(r21)
            lwz     r20, 0x8(r21)
            stw     r20, key
            stw     r25, offset
            stw     r21, mfBase
        }
        response = offset ^ key;
        response = response + mfBase;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        _220.setVisibility(visible);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION bossPanelVisible__Q53scn4step4info5lvmap11StageSphereFb
void StageSphere::bossPanelVisible(bool visible) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 subtrahend;
    volatile u32 response;
    volatile u32 mfBase;
    u32 hash;
    u32 p;
    u32 stop;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
    after1:
        mflr    r24
        lwz     r16, 0x0(r24)
        add     r16, r16, r24
        lwz     r23, 0x4(r24)
        stw     r16, start
        add     r23, r23, r16
        stw     r23, end
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x54)
        opword  0xE6F6DB33
    after2:
        mflr    r17
        lwz     r30, 0x0(r17)
        stw     r30, expected
    }
    stop = end;
    p = start;
    for (; p != stop; p += 2) {
        hash += *(u16*)p;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    _3D8.rootPane().setVisibility(visible);
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash -= expected;
    if (hash == 0) {
        _568.setVisibility(visible);
        return;
    }
    asm {
        bl      after3
        opword  0x24434781
        opword  0xD59B220B
        opword  0x7CC4DC0C
        opword  MF_WORD(0x114)
    after3:
        mflr    r30
        lwz     r20, 0xc(r30)
        stw     r20, -0x4(r1)
        stw     r30, 0x0(r1)
        stw     r20, -0x4(r1)
        stw     r30, -0x8(r1)
        mtlr    r20
        bl      after4
        opword  MF_WORD(0x138)
        opword  0xF8C2B480
        opword  0xCA170606
        opword  MF_WORD(0x144)
    after4:
        mflr    r22
        lwz     r17, 0x0(r22)
        stw     r22, mfBase
        lwz     r30, 0xc(r22)
        stw     r17, offset
        stw     r30, subtrahend
    }
    offset = offset - 0x1B;
    response = offset - subtrahend;
    response = response + mfBase;
    asm {
        lwz     r19, response
        mtlr    r19
        blr
    }
}
#undef MF_FUNCTION

void StageSphere::adjustBgSize() {
    f32 width = (_220.baseWidth() - _90.pane("WakuCenter").size().x) / 2.0f;
    hel::math::Vector2 sizeL = _90.pane("WakuL").size();
    sizeL.x = width;
    _90.pane("WakuL").setSize(sizeL);
    _90.pane("WakuLSh").setSize(sizeL);
    hel::math::Vector2 sizeR = _90.pane("WakuR").size();
    sizeR.x = width;
    _90.pane("WakuR").setSize(sizeR);
    // The right shadow gets the left frame's size.
    _90.pane("WakuRSh").setSize(sizeL);
}

void StageSphere::centerBase() {
    _220.setOffset(hel::math::Vector3(-_220.width() / 2.0f, 0.0f, 0.0f));
}

#define MF_FUNCTION getNextFlashSphere__Q53scn4step4info5lvmap11StageSphereCFUl
u32 StageSphere::getNextFlashSphere(u32 index) const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 subtrahend;
    u32 hash;
    u32 stop;
    u32 p;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x803CDE80
        opword  MF_WORD(0x30)
    after1:
        mflr    r15
        lwz     r20, 0x0(r15)
        stw     r20, start
        lwz     r20, 0x8(r15)
        stw     r20, end
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0x0826DF9A
    after2:
        mflr    r23
        lwz     r16, 0x0(r23)
        stw     r16, expected
    }
    stop = end;
    p = start;
    hash = 0;
    p -= 2;
    while (p != stop - 2) {
        p += 2;
        hash += *(u16*)p;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash = __cntlzw(expected ^ hash);
    hash = (hash >> 5) | ((hash >> 5) << 8);
    if (hash == 0) {
        asm {
            bl      after3
            opword  0xC4817A06
            opword  0xAFC6DA09
            opword  0x00304980
            opword  MF_WORD(0xE4)
        after3:
            mflr    r14
            lwz     r26, 0xc(r14)
            stw     r26, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x108)
            opword  0x50FE6381
            opword  0xC71AC80C
            opword  MF_WORD(0x114)
        after4:
            mflr    r26
            stw     r26, mfBase
            lwz     r15, 0x0(r26)
            stw     r15, offset
            lwz     r16, 0xc(r26)
            stw     r16, subtrahend
        }
        response = offset - subtrahend;
        response = response + mfBase;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        if (isGetDemoDebug()) {
            if (index < StageKindUtil::SphereTotalNum(static_cast<StageKind>(_8))) {
                return index;
            } else {
                return 0xFFFFFFFF;
            }
        }
        for (; index < StageKindUtil::SphereTotalNum(static_cast<StageKind>(_8)); index++) {
            if (reinterpret_cast<const ContextSphere&>(mComponent.context()._50C[3]).getIsGetCurrent(index)) {
                return index;
            }
        }
        return 0xFFFFFFFF;
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::info::lvmap
