#include "scn/step/core/PreLoadReq.h"

#include "app/Application.h"
#include "file/DNOption.h"
#include "file/FDGManager.h"
#include "hel/common/FixedString.h"
#include "metafortress.h"
#include "preload/PreLoadManager.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/gimmick/StepMoveInfo.h"
#include "scn/step/gimmick/lvmapdoor/Result.h"
#include "scn/step/gimmick/shipdoor/Result.h"
#include "scn/step/map/KindUtil.h"
#include "scn/subgame/Context.h"

namespace scn {
namespace step {
namespace core {

namespace {

#define MF_FUNCTION t_dnOption__Q43scn4step4core28_unnamed_PreLoadReq_prt_cpp_FRQ33scn4step9Component
file::DNOption t_dnOption(Component& component) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 subtrahend;
    volatile u32 response;
    u32 hash;
    u32 i;
    u32 size;
    u32 first;

    file::DNOption option;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x7124C709
        opword  0x50CC9280
        opword  MF_WORD(0x38)
        opword  0xC9333105
    after1:
        mflr    r23
        lwz     r15, 0xc(r23)
        stw     r15, start
        lwz     r20, 0x0(r23)
        stw     r20, end
    }
    first = start;
    size = end - first;
    hash = 0xC5;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(first + i - 1);
    }
    option._0 = component.context()._524.isExtraMode();
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0xC440B36C
    after2:
        mflr    r25
        lwz     r16, 0x0(r25)
        stw     r16, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected == 0) {
        return option;
    }
    asm {
        bl      after3
        opword  0x280A6792
        opword  MF_WORD(0x10C)
    after3:
        mflr    r22
        lwz     r28, 0x4(r22)
        stw     r28, -0x4(r1)
        stw     r22, 0x0(r1)
        stw     r28, -0x4(r1)
        stw     r22, -0x8(r1)
        mtlr    r28
        bl      after4
        opword  MF_WORD(0x130)
        opword  0x9C208A80
        opword  0x324E960E
        opword  MF_WORD(0x13C)
    after4:
        mflr    r16
        lwz     r20, 0x0(r16)
        lwz     r25, 0xc(r16)
        stw     r25, subtrahend
        stw     r20, offset
        stw     r16, base
    }
    offset = offset + 0x3B;
    response = offset - subtrahend;
    response = response + base;
    asm {
        lwz     r22, response
        mtlr    r22
        blr
    }
}
#undef MF_FUNCTION

}

PreLoadReq::PreLoadReq(Component& component)
    : mComponent(component)
    , mIsRequested(false) {}

#define MF_FUNCTION Request__Q43scn4step4core10PreLoadReqFRQ33scn4step9ComponentRCQ43scn4step7gimmick12StepMoveInfo
void PreLoadReq::Request(Component& component, const gimmick::StepMoveInfo& info) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 addend;
    volatile u32 offset;
    u32 i;
    u32 first;
    u32 hash;
    u32 limit;

    file::DNOption option = t_dnOption(component);
    file::FDGManager& fdg = hel::common::ExplicitSingleton<app::Application>::object_->fdgManager();
    asm {
        bl      after1
        opword  0x6827B093
        opword  0x44170881
        opword  MF_WORD(0x50)
        opword  0x28CEFA91
        opword  MF_WORD(0x58)
    after1:
        mflr    r23
        lwz     r16, 0x8(r23)
        lwz     r15, 0x10(r23)
        stw     r16, end
        stw     r15, start
        bl      after2
        opword  MF_WORD(0x74)
        opword  0x5A45C67F
    after2:
        mflr    r30
        lwz     r22, 0x0(r30)
        stw     r22, expected
    }
    i = 1;
    first = start;
    limit = end - first + 1;
    hash = 0;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 0x97;
        hash += *(u16*)(first + i - 1);
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0xDCC29093
            opword  MF_WORD(0xE8)
        after3:
            mflr    r22
            lwz     r23, 0x4(r22)
            stw     r23, -0x4(r1)
            stw     r22, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r22, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0x10C)
            opword  0x581FAC90
            opword  0x2AFF9D00
            opword  MF_WORD(0x118)
        after4:
            mflr    r22
            lwz     r23, 0x0(r22)
            lwz     r24, 0xc(r22)
            stw     r24, addend
            stw     r23, offset
            stw     r22, base
        }
        offset = offset + 1;
        response = offset ^ addend;
        response = response + base;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    } else {
        switch (info._8) {
        case 0:
            map::KindUtil::PreLoadRequest(static_cast<map::Kind>(info._0 + component.context().mapKind), option);
            break;
        case 1:
            fdg.preLoad(
                hel::common::FixedStringIN<char, 32>::FromFormat(
                    "GoalgameLv%lu.dn", map::KindUtil::ToLevelIndex(component.context().mapKind) + 1),
                option);
            break;
        case 2:
            fdg.preLoad("WMapCommon.dn", option);
            break;
        case 3:
            fdg.preLoad("Challengeresult.dn", option);
            break;
        }
    }
}
#undef MF_FUNCTION

void PreLoadReq::Request(Component& component, const gimmick::shipdoor::Result& result) {
    file::DNOption option = t_dnOption(component);
    if (result._10 != 2) {
        app::Application::Object().fdgManager().preLoad(
            subgame::Context::MenuDN(static_cast<subgame::Context::Kind>(result._10)), option);
    } else {
        map::KindUtil::PreLoadRequest(result._14, option);
    }
}

#define MF_FUNCTION request__Q43scn4step4core10PreLoadReqFRCQ43scn4step7gimmick12StepMoveInfo
void PreLoadReq::request(const gimmick::StepMoveInfo& info) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;
    u32 t;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x94A31B91
        opword  0x060DA206
        opword  MF_WORD(0x34)
    after1:
        mflr    r18
        lwz     r25, 0x0(r18)
        add     r25, r25, r18
        lwz     r15, 0xc(r18)
        stw     r25, start
        add     r15, r15, r25
        stw     r15, end
    }
    i = 1;
    first = start;
    t = end;
    t = t - first;
    limit = t + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x6C)
        opword  0x3BD85A64
    after2:
        mflr    r28
        lwz     r21, 0x0(r28)
        stw     r21, expected
    }
    hash = 0;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 61;
        t = first + i;
        t = *(u16*)(t - 1);
        hash += t;
        i += 2;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    hash -= limit;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0xF82B4280
            opword  0xB8783581
            opword  MF_WORD(0xD8)
        after3:
            mflr    r29
            lwz     r30, 0x8(r29)
            stw     r30, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r30, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r30
            bl      after4
            opword  MF_WORD(0xFC)
            opword  0x65490C0D
            opword  0xB41EDE80
            opword  MF_WORD(0x108)
        after4:
            mflr    r24
            lwz     r27, 0xc(r24)
            stw     r27, addend
            lwz     r27, 0x0(r24)
            stw     r24, base
            stw     r27, offset
        }
        response = offset ^ addend;
        response = response + base;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    } else if (!checkRequest()) {
        mIsRequested = true;
        if (!mComponent.context()._524.isArenaMode()) {
            hel::common::ExplicitSingleton<app::Application>::object_->preLoadManager().cancel();
            Request(mComponent, info);
        }
    }
}
#undef MF_FUNCTION

void PreLoadReq::request(const gimmick::lvmapdoor::Result& result) {
    if (!checkRequest()) {
        mIsRequested = true;
        hel::common::ExplicitSingleton<app::Application>::object_->preLoadManager().cancel();
        map::KindUtil::PreLoadRequest(map::KindUtil::ToKind(result._10, result._14), t_dnOption(mComponent));
    }
}

void PreLoadReq::request(const gimmick::shipdoor::Result& result) {
    if (!checkRequest()) {
        mIsRequested = true;
        if (result._10 != 2) {
            app::Application::Object().fdgManager().preLoad(
                subgame::Context::MenuDN(static_cast<subgame::Context::Kind>(result._10)), t_dnOption(mComponent));
        } else {
            map::KindUtil::PreLoadRequest(result._14, t_dnOption(mComponent));
        }
    }
}

void PreLoadReq::request(map::Kind kind) {
    if (!checkRequest()) {
        mIsRequested = true;
        map::KindUtil::PreLoadRequest(kind, t_dnOption(mComponent));
    }
}

bool PreLoadReq::isRequested() const {
    return mIsRequested;
}

#define MF_FUNCTION checkRequest__Q43scn4step4core10PreLoadReqFv
bool PreLoadReq::checkRequest() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 size;
    u32 i;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x68E4D180
        opword  MF_WORD(0x28)
        opword  0xBC03D691
    after1:
        mflr    r27
        lwz     r30, 0x0(r27)
        add     r30, r30, r27
        lwz     r15, 0x8(r27)
        stw     r30, start
        add     r15, r15, r30
        stw     r15, end
        bl      after2
        opword  MF_WORD(0x50)
        opword  0x405A1018
    after2:
        mflr    r30
        lwz     r18, 0x0(r30)
        stw     r18, expected
    }
    last = end;
    size = last - start;
    i = -1;
    last--;
    while (i != size - 1) {
        i += 2;
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0 && mIsRequested) {
        return true;
    }
    return expected != hash;
}
#undef MF_FUNCTION

}}}  // namespace scn::step::core
