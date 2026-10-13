#define HEL_COMMON_SCOPEDPTR_CONSTRUCTOR_INLINE
#include "scn/subgame/gunshoot/info/Victory.h"

#include "lyt/LayoutContext.h"
#include "lyt/Utility.h"
#include "metafortress.h"

namespace {

const char* RESLUT_LAYOUT_FILE_NAME = "subgame/gunshoot/result/Main";
const char* VICTORY_LAYOUT_NAME = "ResultVictory";
const char* CLEAR0_ANIMNAME[] = {
    "Clear0",
    "Clear0",
    "Clear0Dedede",
};

}

namespace scn {
namespace subgame {
namespace gunshoot {
namespace info {

Victory::Victory(LevelKind level)
    : mLevel(level)
    , mLayout(new lyt::Layout(lyt::LayoutContext(RESLUT_LAYOUT_FILE_NAME, VICTORY_LAYOUT_NAME, lyt::LayoutContext::DefaultAllocator())))
    , _8(0)
    , mIsVisible(false) {
}

void Victory::updateMain() {
    switch (_8) {
    case 1:
        if (mLayout->isAnimEnd()) {
            _8 = 2;
        }
        break;
    case 3:
        if (mLayout->isAnimEnd()) {
            _8 = 4;
        }
        break;
    case 5:
        if (mLayout->isAnimEnd()) {
            mIsVisible = false;
            _8 = 6;
            mCounter.reset(20);
        }
        break;
    case 6:
        if (mCounter.isEnd()) {
            _8 = 7;
        } else {
            mCounter.advanceIfNotEnd();
        }
        break;
    }
    mLayout->updateFrame();
    mLayout->updateMatrix();
}

void Victory::draw() const {
    if (mIsVisible) {
        lyt::Utility::SetupGX();
        mLayout->draw();
    }
}

void Victory::startExplosion() {
    mIsVisible = true;
    mLayout->setAnimByName(CLEAR0_ANIMNAME[mLevel]);
    mLayout->start(false);
    _8 = 1;
}

#define MF_FUNCTION startClear__Q53scn7subgame8gunshoot4info7VictoryFv
void Victory::startClear() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 p;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0xB80AA392
        opword  MF_WORD(0x24)
        opword  0x4C1F2C90
    after1:
        mflr    r30
        lwz     r20, 0x8(r30)
        lwz     r16, 0x0(r30)
        add     r16, r16, r30
        stw     r16, start
        add     r20, r20, r16
        stw     r20, end
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0xD5A8074E
    after2:
        mflr    r19
        lwz     r20, 0x0(r19)
        stw     r20, expected
    }
    p = start;
    last = end;
    hash = 0xBF;
    for (; p != last; p += 2) {
        hash = *(u16*)p ^ ((hash << 4) ^ (hash >> 28));
    }
    hash += hash << 13;
    mLayout->setAnimByName("Clear1");
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    mLayout->start(expected != hash);
    _8 = 3;
}
#undef MF_FUNCTION

void Victory::exit() {
    mLayout->setAnimByName("Clear2");
    mLayout->start(false);
    _8 = 5;
}

bool Victory::isExitEnd() const {
    return _8 == 7;
}

}}}}  // namespace scn::subgame::gunshoot::info
