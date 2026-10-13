#define MEM_EXPLICITAUTODELETEARRAY_INLINE
#include "scn/wmap/MapModelRoute.h"

#include "g3d/CharaModelContext.h"
#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "g3d/ResFileRepository.h"
#include "g3d/Root.h"
#include "g3d/StdModelContext.h"
#include "mem/AutoHeapExp.h"
#include "metafortress.h"
#include "scn/wmap/Component.h"
#include "scn/wmap/UnlockKindUtil.h"
#include "scn/wmap/UnlockManager.h"
#include "scn/wmap/Util.h"
#include "scn/wmap/effect/Manager.h"
#include "std/tr1/reference_wrapper.h"

namespace scn {
namespace wmap {

namespace {

struct WaitAnim {
    bool exists;
    const char* name;
    bool doLoop;
};

struct WaitAnimInfo {
    WaitAnim _0;
    WaitAnim _C;
};

WaitAnimInfo WAIT_ANIM_INFO[] = {
    { { false, "", false }, { false, "", false } },
    { { true, "Unlock01", false }, { false, "", false } },
    { { true, "Unlock02", false }, { false, "", false } },
    { { true, "Unlock03", false }, { false, "", false } },
    { { true, "Unlock04", false }, { false, "", false } },
    { { true, "UnlockHal01", false }, { false, "", false } },
    { { true, "Wait", true }, { true, "Wait06", true } },
    { { true, "Wait", true }, { true, "Wait07", true } },
};

struct RouteUnlockAnim {
    MapKind mapKind;
    u32 count;
    const char* names[2];
};

RouteUnlockAnim ROUTE_UNLOCK_ANIM_TABLE[] = {
    { MAP_KIND_0, 1, { "Unlock01", "" } },
    { MAP_KIND_0, 1, { "Unlock02", "" } },
    { MAP_KIND_0, 1, { "Unlock03", "" } },
    { MAP_KIND_0, 1, { "Unlock04", "" } },
    { MAP_KIND_0, 2, { "Unlock05", "UnlockHal01" } },
    { MAP_KIND_1, 1, { "Unlock06", "" } },
    { MAP_KIND_1, 1, { "Unlock07", "" } },
};

struct ModelRouteInfo {
    int kind;
    bool flag;
};

ModelRouteInfo MODEL_ROUTE_INFO_TABLE[] = {
    { 0, false }, { 0, true }, { 1, false }, { 1, true }, { 2, false }, { 2, true }, { 3, false }, { 3, true }, { 4, false },
    { 4, true },  { 5, true }, { 5, false }, { 8, false }, { 8, false }, { 6, false }, { 6, true }, { 7, true }, { 7, false },
    { 8, false }, { 8, false }, { 8, false }, { 8, false }, { 8, false }, { 8, false }, { 8, false }, { 8, false }, { 8, false },
};

}

#define MF_FUNCTION __ct__Q33scn4wmap13MapModelRouteFRQ33scn4wmap9Component
// TODO: the original hands the g3d::ModelContext it builds straight to g3d::StdModel; g3d/StdModelContext.h has
// the two the other way round, hence the casts.
MapModelRoute::MapModelRoute(Component& component)
    : mComponent(component)
    , _4(component.resFileRepos().get("wmap/map/popstar/PopstarRoute", false))
    , _8(component.resFileRepos().get("wmap/map/halcandora/HalcandoraRoute", false))
    , _C(static_cast<const g3d::StdModelContext&>(
          g3d::ModelContext(g3d::ResModelContext(_4, "TopL"), g3d::CharaModelContext::DefaultModelBufferOption(), 0,
                            g3d::CharaModelContext::DefaultNumView(), mComponent.heap().obj(), true)))
    , _1B8(static_cast<const g3d::StdModelContext&>(
          g3d::ModelContext(g3d::ResModelContext(_8, "TopL"), g3d::CharaModelContext::DefaultModelBufferOption(), 0,
                            g3d::CharaModelContext::DefaultNumView(), mComponent.heap().obj(), true)))
    , mEffect(component.effectManager().native())
    , mMapKind(MAP_KIND_2)
    , _384(UNLOCK_KIND_0)
    , _388(static_cast<step::LevelKind>(7))
    , _38C(static_cast<step::LevelKind>(7))
    , _390(0)
    , mEffects(component.heap().obj())
    , _3BC(0) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    hash = 0;
    mEffect.changeGroup(component.effectManager().group(DRAW_LAYER_KIND_4));
    asm {
        bl      after1
        opword  MF_WORD(0x1C0)
        opword  0x133DEEB4
    after1:
        mflr    r22
        lwz     r21, 0x0(r22)
        stw     r21, expected
        bl      after2
        opword  MF_WORD(0x1D8)
        opword  MF_WORD(0x1DC)
        opword  0x6D5A150F
        opword  0x4234B601
    after2:
        mflr    r15
        lwz     r16, 0x0(r15)
        add     r16, r16, r15
        lwz     r28, 0x4(r15)
        stw     r16, start
        add     r28, r28, r16
        stw     r28, end
    }
    for (u32 n = 0; n < 8; n++) {
        mEffects.add(std::tr1::ref(mComponent), static_cast<MapModelRouteKind>(n));
    }
    i = 1;
    first = start;
    limit = end - first + 1;
    _384 = mComponent.unlockManager().getUnlockKind();
    for (; i != limit; i += 2) {
        hash *= 151;
        hash += *(u16*)(first + i - 1);
    }
    if (hash == expected) {
        mfStartWaitAnim(_384);
    } else {
        asm {
            bl      after3
            opword  0xEA457D0B
            opword  0x03EA0C09
            opword  0x94D10780
            opword  MF_WORD(0x2CC)
        after3:
            mflr    r19
            lwz     r15, 0xC(r19)
            stw     r15, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r15, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r15
            bl      after4
            opword  MF_WORD(0x2F0)
            opword  0x1466E292
            opword  0x6C770780
            opword  MF_WORD(0x2FC)
        after4:
            mflr    r28
            lwz     r18, 0x0(r28)
            lwz     r17, 0xC(r28)
            stw     r17, key
            stw     r18, offset
            stw     r28, base
        }
        offset = offset ^ 0xBE;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

MapModelRoute::~MapModelRoute() {
}

void MapModelRoute::procAnim() {
    mfGetModel().updateFrame();
    bool isAllEnd = true;
    for (u32 n = 0; n < 8; n++) {
        mEffects[n].procAnim();
        if (!mEffects[n].isAnimEnd()) {
            isAllEnd = false;
        }
    }
    if (isAllEnd) {
        for (u32 n = 0; n < 8; n++) {
            mEffects[n].restartIfAppear();
        }
    }
    if (_3BC == 1 && mfGetModel().isAnimEnd()) {
        if (mfIsEndAllUnlockAnim()) {
            mEffect.release();
            mfStartWaitAnim(UnlockKindUtil::GetUnlockKindFromLevelKind(_38C));
            _3BC = 0;
        } else {
            mfStartUnlockAnim();
        }
    }
}

void MapModelRoute::registerToRoot(g3d::Root& root) {
    mfGetModel().registerToRoot(root);
}

void MapModelRoute::setMapKind(MapKind kind) {
    mMapKind = kind;
}

#define MF_FUNCTION setWaitItem__Q33scn4wmap13MapModelRouteFQ33scn4wmap8ItemKind
void MapModelRoute::setWaitItem(ItemKind item) {
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
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
    after1:
        mflr    r15
        lwz     r25, 0x0(r15)
        stw     r25, end
        lwz     r25, 0x4(r15)
        stw     r25, start
    }
    i = 1;
    first = start;
    limit = end - first + 1;
    hash = 0x811C9DC5;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x01000181;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x8C)
        opword  0xC2AD0CCC
    after2:
        mflr    r26
        lwz     r15, 0x0(r26)
        stw     r15, expected
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
        asm {
            bl      after3
            opword  0x9D63C804
            opword  0x7036E780
            opword  MF_WORD(0xD4)
        after3:
            mflr    r21
            lwz     r23, 0x8(r21)
            stw     r23, -0x4(r1)
            stw     r21, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r21, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0xF8)
            opword  0x5087B692
            opword  0xFCE73392
            opword  MF_WORD(0x104)
        after4:
            mflr    r18
            lwz     r23, 0xC(r18)
            stw     r23, key
            lwz     r23, 0x0(r18)
            stw     r18, base
            stw     r23, offset
        }
        response = offset + key;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        for (u32 n = 0; n < 11; n++) {
            int route = Util::GetRoute(item, static_cast<ItemKind>(n));
            if (route != 27 && mComponent.unlockManager().canMove(static_cast<ItemKind>(n))) {
                const ModelRouteInfo info = MODEL_ROUTE_INFO_TABLE[route];
                if (info.kind != 8) {
                    mEffects[info.kind].appear(info.flag);
                }
            }
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION onMove__Q33scn4wmap13MapModelRouteFv
void MapModelRoute::onMove() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 key;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;

    hash = 0xC5;
    asm {
        bl      after1
        opword  0x48589493
        opword  MF_WORD(0x2C)
        opword  0x10280E81
        opword  0xCC87E990
        opword  MF_WORD(0x38)
    after1:
        mflr    r28
        lwz     r14, 0x10(r28)
        lwz     r22, 0x4(r28)
        add     r14, r22, r14
        stw     r14, end
        stw     r22, start
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x70)
        opword  0xA669057F
    after2:
        mflr    r17
        lwz     r21, 0x0(r17)
        stw     r21, expected
    }
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
    }
    if (hash - expected != 0) {
        asm {
            bl      after3
            opword  0xE4FFE790
            opword  0x1126830B
            opword  MF_WORD(0xCC)
        after3:
            mflr    r29
            lwz     r25, 0x8(r29)
            stw     r25, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r25, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0xF0)
            opword  0xF0A94480
            opword  MF_WORD(0xF8)
        after4:
            mflr    r29
            stw     r29, base
            lwz     r22, 0x0(r29)
            stw     r22, offset
            lwz     r23, 0x8(r29)
            stw     r23, key
        }
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    } else {
        for (u32 n = 0; n < 8; n++) {
            mEffects[n].disappear();
        }
    }
}
#undef MF_FUNCTION

void MapModelRoute::startUnlockAnim(step::LevelKind level) {
    _38C = level;
    mfStartUnlockAnim();
    _3BC = 1;
}

#define MF_FUNCTION isEndUnlockAnim__Q33scn4wmap13MapModelRouteCFv
bool MapModelRoute::isEndUnlockAnim() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 response;
    volatile u32 key;
    u32 i;
    u32 first;
    u32 hash;
    u32 limit;

    hash = 0xC5;
    asm {
        bl      after1
        opword  0x8EA10603
        opword  MF_WORD(0x2C)
    after1:
        mflr    r14
        lwz     r30, 0x4(r14)
        stw     r30, end
        bl      after2
        opword  0x0E52110C
        opword  MF_WORD(0x44)
    after2:
        mflr    r14
        lwz     r30, 0x4(r14)
        stw     r30, start
    }
    limit = end - start + 1;
    i = 1;
    first = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(first + i - 1);
        i += 2;
    }
    asm {
        bl      after3
        opword  MF_WORD(0x98)
        opword  0x9ED55860
    after3:
        mflr    r16
        lwz     r28, 0x0(r16)
        stw     r28, expected
    }
    if (hash != expected) {
        asm {
            stw     r25, -0x4(r1)
            bl      after4
            opword  MF_WORD(0xC0)
            opword  0x04F5C491
        after4:
            mflr    r25
            lwz     r18, 0x0(r25)
            stw     r18, 0x0(r1)
            stw     r25, 0x4(r1)
            mtlr    r18
            bl      after5
            opword  MF_WORD(0xE0)
            opword  0xD8480092
            opword  0xEB0B6606
            opword  MF_WORD(0xEC)
        after5:
            mflr    r16
            lwz     r24, 0x0(r16)
            stw     r16, base
            lwz     r19, 0xC(r16)
            stw     r24, offset
            stw     r19, key
        }
        offset = offset + 0x8D;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    } else {
        return _3BC != 1;
    }
}
#undef MF_FUNCTION

g3d::StdModel& MapModelRoute::mfGetModel() {
    return mfGetModel(mMapKind);
}

g3d::ResFileAccessor& MapModelRoute::mfGetResFile(MapKind kind) {
    switch (kind) {
    case MAP_KIND_0:
        return _4;
    case MAP_KIND_1:
        return _8;
    default:
        return _4;
    }
}

g3d::StdModel& MapModelRoute::mfGetModel(MapKind kind) {
    switch (kind) {
    case MAP_KIND_0:
        return _C;
    case MAP_KIND_1:
        return _1B8;
    default:
        return _C;
    }
}

bool MapModelRoute::mfIsEndAllUnlockAnim() {
    return _390 >= ROUTE_UNLOCK_ANIM_TABLE[_38C].count;
}

void MapModelRoute::mfStartUnlockAnim() {
    const RouteUnlockAnim info = ROUTE_UNLOCK_ANIM_TABLE[_38C];
    if (_390 < info.count) {
        mfGetModel(info.mapKind).model().setVisibility(true);
        mfGetModel(info.mapKind).setAnim(mfGetResFile(info.mapKind), info.names[_390]);
        mfGetModel(info.mapKind).start(false);
        mEffect.requestN(14, mfGetModel(info.mapKind).model().nodeByName("EffectL"));
        _390++;
    }
}

#define MF_FUNCTION mfStartWaitAnim__Q33scn4wmap13MapModelRouteFQ33scn4wmap10UnlockKind
void MapModelRoute::mfStartWaitAnim(UnlockKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;
    const WaitAnimInfo info = WAIT_ANIM_INFO[kind];

    hash = 0xC5;
    asm {
        bl      after1
        opword  0x24845881
        opword  MF_WORD(0x58)
        opword  MF_WORD(0x5C)
        opword  0xC4278780
        opword  0x5278E503
    after1:
        mflr    r14
        lwz     r25, 0x4(r14)
        stw     r25, start
        lwz     r18, 0x8(r14)
        add     r25, r25, r18
        stw     r25, end
    }
    if (info._0.exists) {
        _C.setAnim(_4, info._0.name);
        if (info._0.doLoop) {
            _C.start(true);
        } else {
            _C.setFrame(_C.totalFrame() - 1);
        }
    } else {
        _C.model().setVisibility(false);
    }
    asm {
        bl      after2
        opword  MF_WORD(0x114)
        opword  0x614E2A2B
    after2:
        mflr    r29
        lwz     r30, 0x0(r29)
        stw     r30, expected
    }
    word = start;
    last = end;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    if (hash - expected != 0 || info._C.exists) {
        _1B8.setAnim(_8, info._C.name);
        if (info._C.doLoop) {
            _1B8.start(true);
        } else {
            _1B8.setFrame(_1B8.totalFrame() - 1);
        }
    } else {
        _1B8.model().setVisibility(false);
    }
}
#undef MF_FUNCTION

}}  // namespace scn::wmap
