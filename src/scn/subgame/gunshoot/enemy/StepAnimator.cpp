#include "scn/subgame/gunshoot/enemy/StepAnimator.h"

#include "metafortress.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

#define MF_FUNCTION resumeStep__Q53scn7subgame8gunshoot5enemy12StepAnimatorFv
void StepAnimator::resumeStep() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xF45A0D91
        opword  0x54963080
        opword  MF_WORD(0x38)
    after1:
        mflr    r29
        lwz     r21, 0xc(r29)
        lwz     r22, 0x0(r29)
        add     r21, r22, r21
        stw     r21, end
        stw     r22, start
    }
    word = start;
    last = end;
    for (; word != last; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001A7;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x84)
        opword  0xB08F028B
    after2:
        mflr    r29
        lwz     r18, 0x0(r29)
        stw     r18, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || _64 != -1) {
        while (hash - expected != 0) {
        }
        currentAnimParam().getStepData(_58);
        const AnimParam::AnimData& anim = currentAnimParam().getAnimData(_64);
        _70 = _4->setAnim(0, anim._8);
        _78 = _8->setAnim(0, anim._8);
        _70.setFrame(_88);
        _78.setFrame(_88);
        _70.start(expected == hash);
        _78.start(expected == hash);
        _80.start(expected != hash);
        if (hash - expected == 0 && isCameraAnimEnable()) {
            _10->setFrameRate(1.0f);
        }
        if (hash - expected == 0 && hasPlayListSet() && _E0->isStarting() && _E0->isPause()) {
            _E0->unpause();
        }
        _6B = expected != hash;
    }
}
#undef MF_FUNCTION

}
}
}
}
