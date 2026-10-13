#include "scn/step/carryitem/CarryItem.h"

#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/Desc.h"
#include "scn/step/carryitem/IndiviUtil.h"
#include "scn/step/carryitem/Manager.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/ogen/Generator.h"

namespace scn {
namespace step {
namespace carryitem {

#define MF_FUNCTION __dt__Q43scn4step9carryitem9CarryItemFv
CarryItem::~CarryItem() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 hash;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0xACEF0B91
        opword  MF_WORD(0x38)
    after1:
        mflr    r18
        lwz     r28, 0x0(r18)
        add     r28, r28, r18
        stw     r28, start
        lwz     r22, 0x8(r18)
        add     r28, r28, r22
        stw     r28, end
    }
    mStateChanger->reset();
    hash = 0x811C9DC5;
    i = 1;
    base = start;
    limit = end - base + 1;
    mVacuumReceiver->setIsValid(false);
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xBC)
        opword  0x988E62E7
    after2:
        mflr    r22
        lwz     r30, 0x0(r22)
        stw     r30, expected
    }
    if (hash - expected == 0 && hasObjGenerator()) {
        mObjGenerator->decCount();
        mObjGenerator = 0;
    }
    mHandleOwner.unset();
}
#undef MF_FUNCTION

#define MF_FUNCTION getThrowPowerRate__Q43scn4step9carryitem9CarryItemCFv
f32 CarryItem::getThrowPowerRate() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    f32 rate;
    u32 hash;
    u32 tail;
    u32 i;
    u32 limit;

    rate = (1.0f / 60.0f) * mThrowPower;
    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x5C)
        opword  MF_WORD(0x60)
        opword  0x18623F81
        opword  0xF6D1DC01
    after1:
        mflr    r23
        lwz     r20, 0x0(r23)
        lwz     r29, 0x4(r23)
        stw     r20, end
        stw     r29, start
    }
    i = 1;
    tail = end;
    limit = tail - start + 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(tail - 1 - i);
        hash *= 0x01000181;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xC4)
        opword  0x0672FC78
    after2:
        mflr    r16
        lwz     r28, 0x0(r16)
        stw     r28, expected
    }
    if (hash - expected != 0 || 1.0f < rate) {
        rate = 1.0f;
    }
    return rate;
}
#undef MF_FUNCTION

#define MF_FUNCTION put__Q43scn4step9carryitem9CarryItemFRCQ43scn4step9carryitem4Desc
void CarryItem::put(const Desc& desc) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 value;
    u32 i;
    u32 limit;

    hash = 0xB3;
    reset();
    asm {
        bl      after1
        opword  MF_WORD(0x28)
    after1:
        mflr    r27
        lwz     r23, 0x0(r27)
        add     r23, r23, r27
        stw     r23, start
        bl      after2
        opword  0xA0EDF803
        opword  0x1C576990
        opword  MF_WORD(0x48)
    after2:
        mflr    r27
        lwz     r26, 0x8(r27)
        add     r23, r23, r26
        stw     r23, end
    }
    mUseCount = desc.useCount;
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        value = (hash << 4) ^ (hash >> 28);
        hash = value ^ *(u16*)(last - i);
        i += 2;
    }
    setNextStateDefault();
    asm {
        bl      after3
        opword  MF_WORD(0xB4)
        opword  0xDAAC6C0F
    after3:
        mflr    r21
        lwz     r23, 0x0(r21)
        stw     r23, expected
    }
    hash += hash << 3;
    mStateChanger->changeStateIfPossible();
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected == 0 && isDisableReputItem()) {
        deadProcReleaseEffect();
    } else if (hash - expected == 0 && IndiviUtil::IsUniqueItem(mKind) &&
               mComponent.carryItemManager().isExistObj(mKind, _18)) {
        deadProcReleaseEffect();
    }
}
#undef MF_FUNCTION

}}}  // namespace scn::step::carryitem
