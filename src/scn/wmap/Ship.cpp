#include "scn/wmap/Ship.h"

#include "g3d/CharaModelContext.h"
#include "g3d/ModelBufferOption.h"
#include "g3d/ModelContext.h"
#include "g3d/ResFileRepository.h"
#include "g3d/ResModelContext.h"
#include "mem/AutoHeapExp.h"
#include "mem/IAllocator.h"
#include "metafortress.h"
#include "scn/wmap/Component.h"
#include "scn/wmap/MapModelBg.h"
#include "scn/wmap/RouteTrans.h"
#include "scn/wmap/UnlockManager.h"

namespace scn {
namespace wmap {

namespace {

const char* UNLOCKED_ACTION_NAME_TABLE[] = {
    "Parts0", "Parts0", "Parts1", "Parts2", "Parts3", "Parts4", "Wait", "Wait",
};

}

#define MF_FUNCTION __ct__Q33scn4wmap4ShipFRQ33scn4wmap9Component
// TODO: mem::HeapExp is a mem::IAllocator; its header does not say so yet.
Ship::Ship(Component& component)
    : mComponent(component)
    , mResFile(component.resFileRepos().get("wmap/chara/Roah", false))
    , mModel(g3d::ModelContext(g3d::ResModelContext(mResFile, "TopL"), g3d::CharaModelContext::DefaultModelBufferOption(), 0,
                               g3d::CharaModelContext::DefaultNumView(), reinterpret_cast<mem::IAllocator&>(component.heap().obj()), false))
    , mUnlockKind(UNLOCK_KIND_0) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0xAC)
        opword  0x7C0802A8
    after1:
        mflr    r27
        lwz     r14, 0x0(r27)
        stw     r14, expected
    }
    mUnlockKind = mComponent.unlockManager().getAfterDemoUnlockKind();
    asm {
        bl      after2
        opword  0xCA916001
        opword  MF_WORD(0xE0)
        opword  MF_WORD(0xE4)
        opword  0x3B182608
        opword  0x44257C93
    after2:
        mflr    r22
        lwz     r21, 0x8(r22)
        lwz     r15, 0x4(r22)
        add     r21, r15, r21
        stw     r21, end
        stw     r15, start
    }
    hash = 0x811C9DC5;
    mModel.setAnim(mResFile, UNLOCKED_ACTION_NAME_TABLE[mUnlockKind]);
    i = 1;
    last = end;
    limit = last - start + 1;
    last -= 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x01000181;
        i += 2;
    }
    mModel.start(expected == hash);
}
#undef MF_FUNCTION

// Decodes the address of the hidden object dcpl_0x1e71bd18 (docs/metafortress.md), reads it and hangs if it does
// not decode to zero. The fetch names r20 and moves it to `w20`, so the compiler gives `w20` that register.
#define MF_FUNCTION procFixPos__Q33scn4wmap4ShipFv
void Ship::procFixPos() {
    volatile u32 unused;
    volatile u32 unused2;
    volatile u32 unused3;
    volatile u32 unused4;
    register u32 w20;
    u32 x5;
    u32 x6;
    u32 x4;
    u32 x0;
    u32 x4_1;
    u32 x0_1;
    u32 x3;
    u32 x5_1;
    u32 x6_1;
    u32 x3_1;
    u32 x5_2;
    u32 x6_2;
    u32 x0_2;
    u32 x5_3;
    u32 x6_3;
    u32 x3_2;
    u32 x5_4;
    u32 x6_4;
    u32 x0_3;
    u32 x5_5;
    u32 x6_5;
    u32 x31;
    u32 x25;
    u32 x31_1;
    u32 x25_1;
    u32 x31_2;
    u32 x25_2;
    u32 x31_3;
    u32 x24;
    u32 x24_1;

    hel::math::Matrix34 mtx;

    asm {
        bl      after1
        opword  0x5B8BC005
        opword  MF_WORD(0x30)
        opword  0xD45FCA92
        opword  MF_WORD(0x38)
        opword  0xD8090081
        opword  0x1ABA5D03
    after1:
        mflr    r27
        lwz     r14, 0x4(r27)
        lwz     r26, 0xc(r27)
        stw     r14, unused
        stw     r26, unused2
    }
    if (mUnlockKind <= 5) {
        mtx = mComponent.mapModelBg().getShipMtx();
    } else {
        mtx = mComponent.routeTrans().getShipMtx();
    }
    asm {
        bl      after2
        opword  0x51FDFB09
        opword  0xE43E2481
        opword  MF_WORD(0xBC)
        opword  0x647A1580
        opword  0x30E57990
        opword  MF_WORD(0xC8)
        opword  0xE8D81981
    after2:
        mflr    r26
        lwz     r20, 0x8(r26)
        lwz     r19, 0x14(r26)
        stw     r19, unused4
        stw     r20, unused3
        mr      w20, r20
    }
    x5 = (w20 >> 1) | (w20 << 31);
    x6 = ((x5 >> 4) | (x5 << 28)) & 0xF0F0F0F0;
    x4 = x6 | (((x5 << 4) | (x5 >> 28)) & 0x0F0F0F0F);
    x0 = ((x4 >> 21) ^ (x4 >> 4)) & 0x7FF;
    x0 = x4 ^ ((x0 << 21) | (x0 << 4));
    x4_1 = x0 ^ 0x64EC0C81;
    x0_1 = ((x4_1 >> 23) ^ (x4_1 >> 4)) & 0x7;
    x3 = x4_1 ^ ((x0_1 << 23) | (x0_1 << 4));
    x3 += 0x35280000;
    x5_1 = x3 - 0x2404;
    x6_1 = ((x5_1 >> 8) | (x5_1 << 24)) & 0x26D926D9;
    x3_1 = x6_1 | (((x5_1 << 8) | (x5_1 >> 24)) & 0xD926D926);
    x3_1 += 0x7DEE0000;
    x5_2 = x3_1 + 0x3719;
    x6_2 = ((x5_2 >> 4) | (x5_2 << 28)) & 0xA5A5A5A5;
    x0_2 = x6_2 | (((x5_2 << 4) | (x5_2 >> 28)) & 0x5A5A5A5A);
    x5_3 = (x0_2 << 8) | (x0_2 >> 24);
    x6_3 = ((x5_3 >> 8) | (x5_3 << 24)) & 0x9D629D62;
    x3_2 = x6_3 | (((x5_3 << 8) | (x5_3 >> 24)) & 0x629D629D);
    x3_2 += 0x3A4A0000;
    x5_4 = x3_2 + 0x582E;
    x6_4 = ((x5_4 >> 4) | (x5_4 << 28)) & 0xE1E1E1E1;
    x0_3 = x6_4 | (((x5_4 << 4) | (x5_4 >> 28)) & 0x1E1E1E1E);
    x5_5 = x0_3 ^ 0xC09E126D;
    x6_5 = ((x5_5 >> 2) | (x5_5 << 30)) & 0x33333333;
    x31 = x6_5 | (((x5_5 << 2) | (x5_5 >> 30)) & 0xCCCCCCCC);
    mModel.setModelRTMtx(mtx);
    x31 = *(u32*)x31;
    x31 -= 0x59FA5761;
    x25 = ((x31 >> 17) ^ (x31 >> 3)) & 0x3FFF;
    x25 = x31 ^ ((x25 << 17) | (x25 << 3));
    x31_1 = (x25 << 20) | (x25 >> 12);
    x31_1 += 0x752FD369;
    x31_1 = (x31_1 << 5) | (x31_1 >> 27);
    x25_1 = ((x31_1 >> 14) ^ (x31_1 >> 4)) & 0x7F;
    x25_1 = x31_1 ^ ((x25_1 << 14) | (x25_1 << 4));
    x31_2 = x25_1 - 0x2E4BA1AC;
    x25_2 = ((x31_2 >> 20) ^ (x31_2 >> 14)) & 0x3F;
    x25_2 = x31_2 ^ ((x25_2 << 20) | (x25_2 << 14));
    x31_3 = x25_2 ^ 0x8F74F0D7;
    x31_3 = (x31_3 << 23) | (x31_3 >> 9);
    x31_3 ^= 0xF3ACA4A8;
    x31_3 = (x31_3 >> 3) | (x31_3 << 29);
    x24 = ((x31_3 >> 2) | (x31_3 << 30)) & 0x99999999;
    x31_3 = x24 | (((x31_3 << 2) | (x31_3 >> 30)) & 0x66666666);
    x31_3 ^= 0x7EFCEDA3;
    x24_1 = ((x31_3 >> 4) | (x31_3 << 28)) & 0x96969696;
    x25_2 = ((x31_3 << 4) | (x31_3 >> 28)) & 0x69696969;
    x31_3 = x24_1 | x25_2;
    if (x31_3 != 0) {
        volatile u32 offset;
        volatile u32 unused5;
        volatile u32 response;
        volatile u32 base;

        asm {
            bl      after3
            opword  MF_WORD(0x3E0)
            opword  0x9024D691
            opword  MF_WORD(0x3E8)
        after3:
            mflr    r23
            lwz     r28, 0x8(r23)
            stw     r28, unused5
            lwz     r28, 0x0(r23)
            stw     r23, base
            stw     r28, offset
        }
        offset = offset + 0x47;
        unused5 = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    }
    mModel.updateWorldMtx();
}
#undef MF_FUNCTION

}}  // namespace scn::wmap

// One of the hidden objects of the copy protection (docs/metafortress.md). Functions of other units reach it
// through an address they decode from inline data, so the linker would drop it as unused.
#pragma push
#pragma force_active on
u32 dcpl_0x4fcc3256_dcpl0_mfort6317_[6] = { 0xCDE0E677, 0x5E3FA849, 0x09D0B0E7, 0x5CFDF0C2, 0x1C15802D, 0x0B633F6D };
#pragma pop
