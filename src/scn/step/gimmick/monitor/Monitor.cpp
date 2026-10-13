#include "scn/step/gimmick/monitor/Monitor.h"

#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/StorageAccessor.h"
#include "scn/step/map/BinGmkGeneralEntry.h"

namespace scn {
namespace step {
namespace gimmick {
namespace monitor {

namespace {

// TODO: name the maps. 0x15F is the first of the seven that have a monitor.
const char* t_getResName(map::Kind kind) {
    const char* names[] = {
        "step/gimmick/Monitor00",
        "step/gimmick/Monitor01",
        "step/gimmick/Monitor02",
        "step/gimmick/Monitor03",
        "step/gimmick/Monitor04",
        "step/gimmick/Monitor05",
        "step/gimmick/Monitor05",
    };
    return names[kind - 0x15F];
}

#define MF_FUNCTION t_getShowScreenName__Q53scn4step7gimmick7monitor25_unnamed_Monitor_prt_cpp_FUl
const char* t_getShowScreenName(u32 screen) {
    const char* names[] = {
        "screen00",
        "screen01",
        "screen02",
        "screen03",
    };
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x4C)
        opword  0x648EED90
        opword  MF_WORD(0x54)
    after1:
        mflr    r28
        lwz     r20, 0x0(r28)
        add     r20, r20, r28
        lwz     r25, 0x8(r28)
        stw     r20, start
        add     r25, r25, r20
        stw     r25, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    hash = 0x811C9DC5;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x1000181;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    asm {
        bl      after2
        opword  MF_WORD(0xCC)
        opword  0xF11273D3
    after2:
        mflr    r23
        lwz     r24, 0x0(r23)
        stw     r24, expected
    }
    limit = hash << 15;
    hash += limit;
    limit = expected;
    hash -= limit;
    if (hash != 0) {
        volatile u32 addend;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 anchor;

        asm {
            bl      after3
            opword  0x9C0FFC06
            opword  0xFC21F493
            opword  0x14DD3D81
            opword  MF_WORD(0x108)
        after3:
            mflr    r15
            lwz     r17, 0xc(r15)
            stw     r17, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r17, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r17
            bl      after4
            opword  MF_WORD(0x12C)
            opword  0xB4ABC992
            opword  MF_WORD(0x134)
        after4:
            mflr    r30
            lwz     r18, 0x0(r30)
            lwz     r28, 0x8(r30)
            stw     r28, addend
            stw     r18, offset
            stw     r30, anchor
        }
        response = offset + addend;
        response = response + anchor;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        return names[screen];
    }
}
#undef MF_FUNCTION

}

Monitor::Monitor(const map::BinGmkGeneralEntry& entry, Component& component)
    : mComponent(component)
    , mPos(entry._4.toMaproPos().toWorldPos())
    , mModel(mComponent, t_getResName(mComponent.context().mapKind), "TopL", false, false)
    , mSE() {
    mModel.setTrans(hel::math::Vector3(mPos.x, mPos.y, 0.0f));
    LevelKind level = StorageAccessor::GetLevelLastCleared(component);
    switch (level) {
    case LEVEL_KIND_0:
    case LEVEL_KIND_1:
    case LEVEL_KIND_2:
    case LEVEL_KIND_3:
        viewNoise();
        break;
    case LEVEL_KIND_4:
        if (!StorageAccessor::GetLevelDemoFinished(mComponent, level)) {
            viewShip();
        } else {
            viewCaution();
        }
        break;
    case LEVEL_KIND_5:
    case LEVEL_KIND_6:
        viewCaution();
        break;
    default:
        viewNoise();
        break;
    }
}

Monitor::~Monitor() {}

void Monitor::seReq() {
    mSE.start(0x1FC);
}

#define MF_FUNCTION viewNoise__Q53scn4step7gimmick7monitor7MonitorFv
void Monitor::viewNoise() {
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
        opword  MF_WORD(0x20)
        opword  0x20872393
        opword  0xAC002C80
    after1:
        mflr    r16
        lwz     r26, 0x4(r16)
        lwz     r27, 0x0(r16)
        add     r27, r27, r16
        stw     r27, start
        add     r26, r26, r27
        stw     r26, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    mModel.setAnimByName(t_getShowScreenName(0));
    hash = 0xBF;
    asm {
        bl      after2
        opword  MF_WORD(0x78)
        opword  0xA2BCF20B
    after2:
        mflr    r20
        lwz     r27, 0x0(r20)
        stw     r27, expected
    }
    for (; i != limit; i += 2) {
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(base + i - 1);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    mModel.start(expected == hash);
}
#undef MF_FUNCTION

void Monitor::viewCaution() {
    mModel.setAnimByName(t_getShowScreenName(1));
    mModel.start(true);
}

void Monitor::viewMap() {
    mModel.setAnimByName(t_getShowScreenName(2));
    mModel.start(true);
}

#define MF_FUNCTION viewShip__Q53scn4step7gimmick7monitor7MonitorFv
void Monitor::viewShip() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 t;
    u32 base;
    u32 i;
    u32 limit;

    t = 0x811D0000;
    hash = t - 0x623B;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x5F2AC003
        opword  0x30285980
        opword  MF_WORD(0x38)
        opword  0xA674DF01
        opword  0x74670190
    after1:
        mflr    r27
        lwz     r18, 0x0(r27)
        stw     r18, end
        lwz     r18, 0xc(r27)
        stw     r18, start
    }
    limit = end - start + 1;
    i = 1;
    base = end - 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base - i);
        hash *= 0x1000181;
    }
    mModel.setAnimByName(t_getShowScreenName(3));
    t = hash << 13;
    hash += t;
    asm {
        bl      after2
        opword  MF_WORD(0xBC)
        opword  0x9E24A7C8
    after2:
        mflr    r21
        lwz     r28, 0x0(r21)
        stw     r28, expected
    }
    t = hash >> 7;
    hash ^= t;
    t = hash << 3;
    hash += t;
    t = hash >> 17;
    hash ^= t;
    t = hash << 5;
    hash += t;
    t = expected;
    t = hash & ~t;
    word = expected;
    word = word & ~hash;
    word = t | word;
    hash = __cntlzw(word);
    word = hash >> 5;
    hash = word >> 2;
    hash = word - hash;
    if (hash == 0) {
        volatile u32 anchor;
        volatile u32 response;
        volatile u32 subtrahend;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0xC8542981
            opword  0x50A67680
            opword  0xB139E008
            opword  MF_WORD(0x12C)
        after3:
            mflr    r24
            lwz     r27, 0xc(r24)
            stw     r27, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r27, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r27
            bl      after4
            opword  MF_WORD(0x150)
            opword  0xF8F69600
            opword  0x8CB25F80
            opword  MF_WORD(0x15C)
        after4:
            mflr    r20
            lwz     r22, 0x0(r20)
            lwz     r27, 0xc(r20)
            stw     r27, subtrahend
            stw     r22, offset
            stw     r20, anchor
        }
        offset = offset + 0xC9;
        response = offset - subtrahend;
        response = response + anchor;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    } else {
        mModel.start(true);
    }
}
#undef MF_FUNCTION

}
}
}
}
