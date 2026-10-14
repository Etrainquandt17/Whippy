#include "scn/challengeresult/info/ResultLyt.h"

#include "hel/common/ExplicitSingleton.h"
#include "hid/HIDManager.h"
#include "metafortress.h"

using hel::common::ExplicitSingleton;

namespace scn {
namespace challengeresult {
namespace info {

#define MF_FUNCTION updateFrame__Q43scn15challengeresult4info9ResultLytFv
void ResultLyt::updateFrame() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;
    bool bonus;

    hash = 0;
    asm {
        bl      after1
        opword  0x410B1202
        opword  0x0BCE3909
        opword  MF_WORD(0x28)
        opword  0x4CA8DB90
    after1:
        mflr    r23
        lwz     r30, 0x8(r23)
        stw     r30, start
        bl      after2
        opword  MF_WORD(0x40)
        opword  0xA0E69004
    after2:
        mflr    r23
        lwz     r15, 0x0(r23)
        add     r15, r15, r30
        stw     r15, end
    }
    word = start;
    last = end;
    asm {
        bl      after3
        opword  MF_WORD(0x64)
        opword  0xF7EDFFD9
    after3:
        mflr    r20
        lwz     r23, 0x0(r20)
        stw     r23, expected
    }
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 ||
        (mState != 0 && mState <= 5 && ExplicitSingleton<hid::HIDManager>::object_->gameWR(0).button().isTrigger(0x100))) {
        _52EA = true;
        while (mState == 1) {
            _18.setFrameToTail();
            stateStart();
        }
        while (mState == 2) {
            _660.skip();
            stateCountUp();
        }
        while (mState == 3) {
            _10.setEndIfNotEnd();
            stateCountWait();
        }
        while (mState == 4) {
            _660.skip();
            _660.updateFrame();
            stateTimeBonus();
        }
        bonus = false;
        while (mState == 5) {
            _660.skip();
            _660.updateFrame();
            stateBonus();
            bonus = true;
        }
        if (bonus) {
            _660.bonusSkipEffect();
        }
        _52EA = false;
    }
    updateFrame1();
}
#undef MF_FUNCTION

}}}  // namespace scn::challengeresult::info
