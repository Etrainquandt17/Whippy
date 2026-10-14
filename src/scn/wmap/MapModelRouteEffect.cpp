#include "scn/wmap/MapModelRouteEffect.h"

#include "g3d/CharaModelContext.h"
#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "g3d/ResFileRepository.h"
#include "g3d/StdModelContext.h"
#include "mem/AutoHeapExp.h"
#include "metafortress.h"
#include "scn/wmap/Component.h"
#include "scn/wmap/effect/Manager.h"

using g3d::CharaModelContext;
using g3d::ModelContext;
using g3d::ResModelContext;
using g3d::StdModelContext;

namespace scn {
namespace wmap {

namespace {

const char* MODEL_NAME_TABLE[] = {
    "Lv1ToLv2TransL", "Lv2ToLv3TransL", "Lv3ToLv4TransL", "Lv4ToLv5TransL",
    "Lv5ToLv1TransL", "ShipToLv1TransL", "Lv6ToLv7TransL", "ShipToLv6TransL",
};

}

#define MF_FUNCTION __ct__Q33scn4wmap19MapModelRouteEffectFRQ33scn4wmap9ComponentQ33scn4wmap17MapModelRouteKind
// TODO: the original hands the g3d::ModelContext it builds straight to g3d::StdModel; g3d/StdModelContext.h has
// the two the other way round, hence the cast.
MapModelRouteEffect::MapModelRouteEffect(Component& component, MapModelRouteKind kind)
    : mComponent(component)
    , mKind(kind)
    , _8(false)
    , _9(false)
    , mResFile(component.resFileRepos().get(mfGetResFileName(), false))
    , mModel(static_cast<const StdModelContext&>(
          ModelContext(ResModelContext(mResFile, mfGetTopLName()), CharaModelContext::DefaultModelBufferOption(), 0,
                       CharaModelContext::DefaultNumView(), mComponent.heap().obj(), true)))
    , mEffect(component.effectManager().native()) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 response;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0xE8)
        opword  0xBE115C00
    after1:
        mflr    r16
        lwz     r15, 0x0(r16)
        stw     r15, expected
    }
    hash = 0x811C9E29;
    asm {
        bl      after2
        opword  MF_WORD(0x108)
        opword  0x203A9190
        opword  0x68BD6F90
    after2:
        mflr    r21
        lwz     r14, 0x0(r21)
        add     r14, r14, r21
        stw     r14, start
        bl      after3
        opword  0xF0D94D91
        opword  MF_WORD(0x12C)
    after3:
        mflr    r21
        lwz     r18, 0x4(r21)
        add     r14, r14, r18
        stw     r14, end
    }
    limit = end - start + 1;
    first = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001AB;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    hash ^= limit;
    if (hash == 0) {
        mEffect.changeGroup(component.effectManager().group(DRAW_LAYER_KIND_4));
    } else {
        asm {
            bl      after4
            opword  0x285F1781
            opword  MF_WORD(0x1D0)
        after4:
            mflr    r18
            lwz     r17, 0x4(r18)
            stw     r17, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r17, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r17
            bl      after5
            opword  MF_WORD(0x1F4)
            opword  0x3C606E81
            opword  0x3F1A840F
            opword  MF_WORD(0x200)
        after5:
            mflr    r20
            lwz     r15, 0xC(r20)
            stw     r15, key
            lwz     r15, 0x0(r20)
            stw     r20, base
            stw     r15, offset
        }
        key = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    }
}
#undef MF_FUNCTION

MapModelRouteEffect::~MapModelRouteEffect() {
}

void MapModelRouteEffect::procAnim() {
    mModel.updateFrame();
}

#define MF_FUNCTION appear__Q33scn4wmap19MapModelRouteEffectFb
void MapModelRouteEffect::appear(bool flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0x8E9D3E0D
        opword  MF_WORD(0x24)
        opword  0x38486190
        opword  MF_WORD(0x2C)
    after1:
        mflr    r24
        lwz     r16, 0xc(r24)
        lwz     r28, 0x4(r24)
        stw     r28, start
        stw     r16, end
    }
    last = end;
    word = start;
    asm {
        bl      after2
        opword  MF_WORD(0x50)
        opword  0xC9025684
    after2:
        mflr    r19
        lwz     r28, 0x0(r19)
        stw     r28, expected
    }
    hash = 0xB5;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    _9 = expected == hash;
    _8 = flag;
    mfStart();
}
#undef MF_FUNCTION

#define MF_FUNCTION disappear__Q33scn4wmap19MapModelRouteEffectFv
void MapModelRouteEffect::disappear() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 key;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xB5468C70
    after1:
        mflr    r25
        lwz     r23, 0x0(r25)
        stw     r23, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  MF_WORD(0x40)
    after2:
        mflr    r18
        lwz     r28, 0x0(r18)
        lwz     r24, 0x4(r18)
        stw     r28, start
        stw     r24, end
    }
    hash = 0;
    i = 1;
    first = start;
    limit = end - first + 1;
    for (; i != limit; i += 2) {
        hash += *(u16*)(first + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash != expected) {
        asm {
            bl      after3
            opword  MF_WORD(0xBC)
        after3:
            mflr    r22
            lwz     r24, 0x0(r22)
            stw     r24, -0x4(r1)
            stw     r22, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r22, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0xE0)
            opword  0xA0B2C493
            opword  0x30706081
            opword  MF_WORD(0xEC)
        after4:
            mflr    r14
            lwz     r23, 0xC(r14)
            stw     r23, key
            lwz     r23, 0x0(r14)
            stw     r14, base
            stw     r23, offset
        }
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        _9 = false;
    }
}
#undef MF_FUNCTION

bool MapModelRouteEffect::isAnimEnd() const {
    return mModel.isAnimEnd();
}

void MapModelRouteEffect::restartIfAppear() {
    if (_9 && mModel.isAnimEnd()) {
        mfStart();
    }
}

#define MF_FUNCTION mfGetResFileName__Q33scn4wmap19MapModelRouteEffectCFv
const char* MapModelRouteEffect::mfGetResFileName() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 key;
    volatile u32 offset;
    u32 word;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;

    hash = 0x811C9E29;
    asm {
        bl      after1
        opword  0x5CBDFE09
        opword  0x40D01793
        opword  MF_WORD(0x34)
        opword  0x08D56B92
    after1:
        mflr    r23
        lwz     r14, 0x8(r23)
        stw     r14, end
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0x69276C05
        opword  0x1D8D9409
    after2:
        mflr    r23
        lwz     r14, 0x0(r23)
        stw     r14, start
    }
    last = end;
    limit = last - start + 1;
    i = -1;
    word = last - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(word - i);
        hash *= 0x010001AB;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xA8)
        opword  0xE1E12B09
    after3:
        mflr    r25
        lwz     r30, 0x0(r25)
        stw     r30, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash != expected) {
        asm {
            stw     r24, -0x4(r1)
            bl      after4
            opword  MF_WORD(0xE8)
            opword  0x188D7181
        after4:
            mflr    r24
            lwz     r30, 0x0(r24)
            stw     r30, 0x0(r1)
            stw     r24, 0x4(r1)
            mtlr    r30
            bl      after5
            opword  MF_WORD(0x108)
            opword  0x9801FA90
            opword  MF_WORD(0x110)
        after5:
            mflr    r17
            stw     r17, base
            lwz     r20, 0x0(r17)
            stw     r20, offset
            lwz     r22, 0x8(r17)
            stw     r22, key
        }
        offset = offset ^ 0x5E;
        key = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        switch (mKind) {
        case MAP_MODEL_ROUTE_KIND_LV1_TO_LV2:
        case MAP_MODEL_ROUTE_KIND_LV2_TO_LV3:
        case MAP_MODEL_ROUTE_KIND_LV3_TO_LV4:
        case MAP_MODEL_ROUTE_KIND_LV4_TO_LV5:
        case MAP_MODEL_ROUTE_KIND_LV5_TO_LV1:
        case MAP_MODEL_ROUTE_KIND_SHIP_TO_LV1:
            return "wmap/map/popstar/PopstarRoute";
        case MAP_MODEL_ROUTE_KIND_LV6_TO_LV7:
        case MAP_MODEL_ROUTE_KIND_SHIP_TO_LV6:
            return "wmap/map/halcandora/HalcandoraRoute";
        default:
            return "";
        }
    }
}
#undef MF_FUNCTION

const char* MapModelRouteEffect::mfGetTopLName() const {
    return MODEL_NAME_TABLE[mKind];
}

#define MF_FUNCTION mfGetEffectKind__Q33scn4wmap19MapModelRouteEffectCFv
u32 MapModelRouteEffect::mfGetEffectKind() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xE9A9030A
        opword  0xDEE20C03
    after1:
        mflr    r28
        lwz     r26, 0x0(r28)
        add     r26, r26, r28
        stw     r26, start
        bl      after2
        opword  0x41E33C04
        opword  MF_WORD(0x48)
        opword  0xF8724191
    after2:
        mflr    r28
        lwz     r24, 0x4(r28)
        add     r26, r26, r24
        stw     r26, end
    }
    hash = 0xC1;
    i = 1;
    first = start;
    limit = end - first + 1;
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(first + i - 1);
    }
    asm {
        bl      after3
        opword  MF_WORD(0xA4)
        opword  0xA52288BE
    after3:
        mflr    r29
        lwz     r21, 0x0(r29)
        stw     r21, expected
    }
    limit = expected;
    hash ^= limit;
    if (hash == 0) {
        switch (mKind) {
        case MAP_MODEL_ROUTE_KIND_LV1_TO_LV2:
        case MAP_MODEL_ROUTE_KIND_LV2_TO_LV3:
        case MAP_MODEL_ROUTE_KIND_LV3_TO_LV4:
        case MAP_MODEL_ROUTE_KIND_LV4_TO_LV5:
        case MAP_MODEL_ROUTE_KIND_LV5_TO_LV1:
        case MAP_MODEL_ROUTE_KIND_SHIP_TO_LV1:
            return 15;
        case MAP_MODEL_ROUTE_KIND_LV6_TO_LV7:
        case MAP_MODEL_ROUTE_KIND_SHIP_TO_LV6:
            return 13;
        default:
            return 18;
        }
    }
    asm {
        bl      after4
        opword  0xE8F12581
        opword  0x10442492
        opword  MF_WORD(0x110)
    after4:
        mflr    r26
        lwz     r27, 0x8(r26)
        stw     r27, -0x4(r1)
        stw     r26, 0x0(r1)
        stw     r27, -0x4(r1)
        stw     r26, -0x8(r1)
        mtlr    r27
        bl      after5
        opword  MF_WORD(0x134)
        opword  0xF088D790
        opword  0x0464BF80
        opword  MF_WORD(0x140)
    after5:
        mflr    r30
        stw     r30, base
        lwz     r17, 0x0(r30)
        stw     r17, offset
        lwz     r19, 0xC(r30)
        stw     r19, key
    }
    offset = offset - 0xC0;
    key = 0;
    response = offset;
    response = response + base;
    asm {
        lwz     r26, response
        mtlr    r26
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION mfStart__Q33scn4wmap19MapModelRouteEffectFv
void MapModelRouteEffect::mfStart() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 key;
    u32 size;
    u32 i;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0xEC289580
        opword  0x5852BB80
        opword  MF_WORD(0x2C)
        opword  0xBB0E5E08
        opword  MF_WORD(0x34)
        opword  0xD0273A92
    after1:
        mflr    r26
        lwz     r15, 0x8(r26)
        lwz     r22, 0x10(r26)
        stw     r22, start
        stw     r15, end
    }
    hash = 0;
    mModel.setAnim(mResFile, mfGetTopLName());
    size = end - start;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x80)
        opword  0x1146C9FF
    after2:
        mflr    r20
        lwz     r28, 0x0(r20)
        stw     r28, expected
    }
    if (_8) {
        mModel.setFrame(static_cast<f32>(mModel.totalFrame() - 1));
        mModel.setFrameRate(-1.0f);
    }
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    mModel.start(false);
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash == expected) {
        mEffect.requestN(mfGetEffectKind(), mModel.model().nodeByName("TransL"));
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x198)
        after3:
            mflr    r21
            lwz     r27, 0x0(r21)
            stw     r27, -0x4(r1)
            stw     r21, 0x0(r1)
            stw     r27, -0x4(r1)
            stw     r21, -0x8(r1)
            mtlr    r27
            bl      after4
            opword  MF_WORD(0x1BC)
            opword  0x1BF9F102
            opword  MF_WORD(0x1C4)
        after4:
            mflr    r15
            lwz     r27, 0x0(r15)
            lwz     r21, 0x8(r15)
            stw     r21, key
            stw     r27, offset
            stw     r15, base
        }
        response = offset + key;
        response = response + base;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    }
}
#undef MF_FUNCTION

}}  // namespace scn::wmap
