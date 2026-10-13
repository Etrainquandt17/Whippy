#include "scn/step/StorageAccessor.h"

#include "metafortress.h"
#include "storage/StoryData.h"

namespace scn {
namespace step {

namespace {

storage::StoryData& t_storyData(Component& component);
storage::StoryData::StageData& t_backupStageData(Component& component, StageKind stage);

}

#define MF_FUNCTION GetIsSphereGet__Q33scn4step15StorageAccessorFRQ33scn4step9ComponentQ33scn4step9StageKindUl
bool StorageAccessor::GetIsSphereGet(Component& component, StageKind stage, u32 index) {
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
        opword  0x209C0493
        opword  0xD82CA380
        opword  MF_WORD(0x30)
        opword  0xBC574580
        opword  MF_WORD(0x38)
    after1:
        mflr    r21
        lwz     r16, 0x10(r21)
        stw     r16, start
        lwz     r20, 0x8(r21)
        stw     r20, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    asm {
        bl      after2
        opword  MF_WORD(0x6C)
        opword  0x3675EE80
    after2:
        mflr    r28
        lwz     r29, 0x0(r28)
        stw     r29, expected
    }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 193;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    while (hash - expected != 0) {
    }
    return t_backupStageData(component, stage).isSphereGet[index];
}
#undef MF_FUNCTION

#define MF_FUNCTION SetSphereUnlockExecutedDemo__Q33scn4step15StorageAccessorFRQ33scn4step9ComponentQ33scn4step16SphereUnlockKindb
void StorageAccessor::SetSphereUnlockExecutedDemo(Component& component, SphereUnlockKind kind, bool executed) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 hash;
    u32 last;

    hash = 0xBF;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0xB034FD0D
        opword  MF_WORD(0x38)
        opword  0x94AC0181
    after1:
        mflr    r24
        lwz     r21, 0x0(r24)
        lwz     r16, 0x8(r24)
        stw     r21, start
        stw     r16, end
    }
    last = end;
    word = start;
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
        word += 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x84)
        opword  0x1A1E9F92
    after2:
        mflr    r29
        lwz     r21, 0x0(r29)
        stw     r21, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || executed != t_storyData(component).sphereUnlockData[kind].executedDemo) {
        BookingSave_AtCtrl();
    }
    t_storyData(component).sphereUnlockData[kind].executedDemo = executed;
}
#undef MF_FUNCTION

}
}
