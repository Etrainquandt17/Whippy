#include "scn/step/weapon/ModelDescUtil.h"

#include "g3d/ResModelContext.h"
#include "hel/common/FixedString.h"
#include "metafortress.h"

namespace scn {
namespace step {
namespace weapon {

// TODO: the casts stand for members that chara::ModelDesc, gobj::ModelDesc and gobj::ScriptDesc keep as words:
// the path at 0, the name (a FixedString<24>) at 0x18, the node names at 0x68 and 0x6C, the animation and
// script descriptions at 0x70 and 0x74.
#define MF_FUNCTION                                                                                                    \
    Set__Q43scn4step6weapon13ModelDescUtilFRQ43scn4step5chara9ModelDescRQ24gobj8AnimDescRQ24gobj10ScriptDescPCcPCcUlPPCcUlPCQ34gobj20G3DAnimDataReposDesc5EntryUlPCQ34gobj10ScriptDesc5Entry
void ModelDescUtil::Set(chara::ModelDesc& desc, gobj::AnimDesc& animDesc, gobj::ScriptDesc& scriptDesc, const char* path,
                        const char* name, u32 nodeNameCount, const char** nodeNames, u32 animEntryCount,
                        const gobj::G3DAnimDataReposDesc::Entry* animEntries, u32 scriptEntryCount,
                        const gobj::ScriptDesc::Entry* scriptEntries) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    desc._0 = reinterpret_cast<u32>(path);
    asm {
        bl      after1
        opword  MF_WORD(0x58)
        opword  0xB65AEE20
    after1:
        mflr    r21
        lwz     r22, 0x0(r21)
        stw     r22, expected
    }
    *reinterpret_cast<hel::common::FixedString<24>*>(&desc.mModel._0[0]) = hel::common::FixedString<24>(name);
    asm {
        bl      after2
        opword  MF_WORD(0xC0)
        opword  0x64EF2581
        opword  0xA54C7007
        opword  MF_WORD(0xCC)
        opword  0x2CFF3680
        opword  0x3C271E90
    after2:
        mflr    r30
        lwz     r24, 0x0(r30)
        add     r24, r24, r30
        stw     r24, start
        lwz     r18, 0xc(r30)
        add     r24, r24, r18
        stw     r24, end
    }
    desc.mModel._18 = hel::common::FixedString<40>(g3d::ResModelContext::DefaultEntryName());
    desc.mModel._44[0] = 0x800;
    hash = 0xBF;
    desc.mModel._44[3] = nodeNameCount;
    last = end;
    word = start;
    desc.mModel._44[4] = reinterpret_cast<u32>(nodeNames);
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
        word += 2;
    }
    animDesc._0 = 1;
    animDesc._4 = animEntryCount;
    hash += hash << 3;
    animDesc._8 = animEntries;
    hash ^= hash >> 11;
    desc._70[0] = reinterpret_cast<u32>(&animDesc);
    hash += hash << 15;
    scriptDesc._0[0] = reinterpret_cast<u32>("Scn.Step.Weapon");
    scriptDesc._0[1] = scriptEntryCount;
    scriptDesc._0[2] = reinterpret_cast<u32>(scriptEntries);
    if ((hash ^ expected) == 0) {
        desc._70[1] = reinterpret_cast<u32>(&scriptDesc);
    } else {
        volatile u32 offset;
        volatile u32 unused;
        volatile u32 base;
        volatile u32 response;

        asm {
            bl      after3
            opword  0x76475905
            opword  MF_WORD(0x1F8)
        after3:
            mflr    r30
            lwz     r16, 0x4(r30)
            stw     r16, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x21C)
            opword  MF_WORD(0x220)
        after4:
            mflr    r19
            lwz     r15, 0x0(r19)
            lwz     r24, 0x4(r19)
            stw     r24, unused
            stw     r15, offset
            stw     r19, base
        }
        offset = offset + 0xB0;
        unused = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    }
}
#undef MF_FUNCTION

}}}  // namespace scn::step::weapon
