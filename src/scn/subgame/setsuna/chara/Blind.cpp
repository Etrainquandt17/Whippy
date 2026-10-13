#include "scn/subgame/setsuna/chara/Blind.h"

#include "lyt/LayoutContext.h"
#include "lyt/Utility.h"
#include "metafortress.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace chara {

namespace {

const char* FADE_IN_ANIM_NAME[Blind::TYPE_NUM] = {
    "FadeIn01", "FadeIn02", "FadeIn03", "FadeIn01", "FadeIn02",
};

const char* WAIT_ANIM_NAME[Blind::TYPE_NUM] = {
    "Wait01", "Wait02", "Wait03", "Wait01", "Wait02",
};

const char* FADE_OUT_ANIM_NAME[Blind::TYPE_NUM] = {
    "FadeOut01", "FadeOut02", "FadeOut03", "FadeOut01", "FadeOut02",
};

}

Blind::Blind()
    : mFog(new lyt::Layout(lyt::LayoutContext("subgame/setsuna/hide_fog/Main", "HideFog", lyt::LayoutContext::DefaultAllocator())))
    , mWood(new lyt::Layout(lyt::LayoutContext("subgame/setsuna/hide_fog/Main", "HideWood", lyt::LayoutContext::DefaultAllocator())))
    , mLayout(&*mFog)
    , mType(TYPE_NUM)
    , mState(0) {
    mFog->rootPane().setVisibility(false);
    mWood->rootPane().setVisibility(false);
}

Blind::~Blind() {
}

void Blind::updateMain() {
    switch (mState) {
    case 1:
        if (mLayout->isAnimEnd()) {
            mState = 2;
            mLayout->setAnimByName(WAIT_ANIM_NAME[mType]);
            mLayout->start(true);
        }
        break;
    case 3:
        if (mLayout->isAnimEnd()) {
            mState = 0;
            mLayout->rootPane().setVisibility(false);
        }
        break;
    }
    mLayout->updateFrame();
    mLayout->updateMatrix();
}

void Blind::updateDebug() {
}

void Blind::drawLayout() const {
    lyt::Utility::SetupGX();
    mLayout->draw();
}

void Blind::fadeIn(Type type) {
    mType = type;
    switch (mType) {
    case TYPE_FOG_1:
    case TYPE_FOG_2:
    case TYPE_FOG_3:
        mLayout = &*mFog;
        break;
    case TYPE_WOOD_1:
    case TYPE_WOOD_2:
        mLayout = &*mWood;
        break;
    }
    mLayout->rootPane().setVisibility(true);
    mLayout->setAnimByName(FADE_IN_ANIM_NAME[mType]);
    mLayout->start(false);
    mState = 1;
}

#define MF_FUNCTION fadeOut__Q53scn7subgame7setsuna5chara5BlindFv
void Blind::fadeOut() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xEC757D80
        opword  0xABB62101
        opword  MF_WORD(0x38)
        opword  0xBF096F08
        opword  0x60AB9280
    after1:
        mflr    r24
        lwz     r16, 0xc(r24)
        lwz     r18, 0x0(r24)
        stw     r18, end
        stw     r16, start
    }
    limit = end - start + 1;
    i = 1;
    first = start;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x01000193;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0xDF29BA03
    after2:
        mflr    r27
        lwz     r29, 0x0(r27)
        stw     r29, expected
    }
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || mState == 3 || mState == 0) {
        return;
    }
    while (hash - expected != 0) {
    }
    mLayout->setAnimByName(FADE_OUT_ANIM_NAME[mType]);
    mLayout->start(expected != hash);
    mState = 3;
}
#undef MF_FUNCTION

}
}
}
}
