#include "scn/challengeresult/SceneChallengeResult.h"

#include "metafortress.h"

namespace scn {
namespace challengeresult {

#define MF_FUNCTION updateMain__Q33scn15challengeresult20SceneChallengeResultFv
void SceneChallengeResult::updateMain() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x149CDE92
        opword  0x74589690
        opword  MF_WORD(0x30)
        opword  0xA39AD80E
        opword  0x70C11281
    after1:
        mflr    r17
        lwz     r29, 0x0(r17)
        add     r29, r29, r17
        stw     r29, start
        lwz     r25, 0xc(r17)
        add     r29, r29, r25
        stw     r29, end
    }
    hash = 0;
    last = end;
    word = start;
    mCounter.advanceIfNotEnd();
    for (; word != last; word += 2) {
        hash *= 61;
        hash += *(u16*)word;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x8C)
        opword  0x59B9132B
    after2:
        mflr    r19
        lwz     r22, 0x0(r19)
        stw     r22, expected
    }
    hash += hash << 13;
    mFade.update();
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    switch (mState) {
    case 0:
        if (hash - expected != 0 && mInfo->mResultLyt.isAnimEnd()) {
            _5C80 = mInfo->mResultLyt._52E8;
            _5C81 = mInfo->mResultLyt._52E9;
            GXColor color = {0, 0, 0, 255};
            mFade.setColor(color);
            mFade.setFadeOut(25);
            mCounter.reset(25);
            mState = 1;
        }
        break;
    case 1:
        if (hash - expected != 0 && mCounter.isEnd()) {
            mState = 2;
        }
        break;
    case 2:
        mState = 3;
        break;
    case 3:
        break;
    }
    mInfo->procAnim();
    mEffect.procAnim();
    mInfo->procReadyToRender();
    mEffect.procReadyToRender();
}
#undef MF_FUNCTION

}}  // namespace scn::challengeresult
