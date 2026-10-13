#include "scn/subgame/setsuna/info/Evaluation.h"

#include "lyt/LayoutContext.h"
#include "lyt/Utility.h"
#include "metafortress.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace info {

namespace {

const char* FILE_NAME = "subgame/setsuna/result/Main";

}

Evaluation::Evaluation()
    : mGoodLayout(new lyt::Layout(lyt::LayoutContext(FILE_NAME, "ResultHit", lyt::LayoutContext::DefaultAllocator())))
    , mBadLayout(new lyt::Layout(lyt::LayoutContext(FILE_NAME, "ContinuityBad", lyt::LayoutContext::DefaultAllocator()))) {
    mGoodLayout->rootPane().setVisibility(false);
    mBadLayout->rootPane().setVisibility(false);
}

Evaluation::~Evaluation() {
}

void Evaluation::showGood() {
    mGoodLayout->rootPane().setVisibility(true);
    mGoodLayout->play("In");
}

void Evaluation::showBad() {
    mBadLayout->rootPane().setVisibility(true);
    mBadLayout->play("In");
}

bool Evaluation::isAnimEnd() const {
    if (mGoodLayout->wasSetAnim()) {
        return mGoodLayout->isAnimEnd();
    }
    if (mBadLayout->wasSetAnim()) {
        return mBadLayout->isAnimEnd();
    }
    return true;
}

#define MF_FUNCTION close__Q53scn7subgame7setsuna4info10EvaluationFv
void Evaluation::close() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 hash;
    u32 size;
    u32 first;
    u32 i;
    u32 limit;

    mGoodLayout->rootPane().setVisibility(false);
    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x50)
        opword  0x42494808
        opword  MF_WORD(0x58)
    after1:
        mflr    r14
        lwz     r20, 0x0(r14)
        lwz     r21, 0x8(r14)
        add     r20, r20, r14
        add     r21, r21, r20
        stw     r20, start
        stw     r21, end
    }
    mGoodLayout->clearAnim();
    first = start;
    size = end;
    size -= first;
    limit = size + 1;
    base = end;
    i = -1;
    base -= 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(base - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xD0)
        opword  0xA3F31253
    after2:
        mflr    r24
        lwz     r23, 0x0(r24)
        stw     r23, expected
    }
    mBadLayout->rootPane().setVisibility(expected != hash);
    mBadLayout->clearAnim();
}
#undef MF_FUNCTION

void Evaluation::updateMain() {
    mGoodLayout->updateFrame();
    mGoodLayout->updateMatrix();
    mBadLayout->updateFrame();
    mBadLayout->updateMatrix();
}

void Evaluation::drawLayout() const {
    lyt::Utility::SetupGX();
    mGoodLayout->draw();
    mBadLayout->draw();
}

}}}}  // namespace scn::subgame::setsuna::info
