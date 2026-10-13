#include "scn/subgame/SceneSubgameTitle.h"

#include "app/Application.h"
#include "app/HIDErrorMenu.h"
#include "file/DNOption.h"
#include "file/FDGManager.h"
#include "file/Utility.h"
#include "hel/common/ArrayUtil.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/FixedString.h"
#include "hel/common/MutableArray.h"
#include "hel/common/Traits.h"
#include "metafortress.h"
#include "preload/PreLoadManager.h"
#include "scn/step/hero/AbilityKindUtil.h"
#include "scn/step/map/KindUtil.h"
#include "storage/StoryMode.h"

namespace scn {
namespace subgame {

namespace {

// TODO: stands in for an inline accessor of ExplicitSingleton, which its header does not have yet.
template <class T>
inline T& tInstance() {
    return *hel::common::ExplicitSingleton<T>::object_;
}

// TODO: stands in for Context, whose members from 0x34 on are a bool and three words. scn/subgame/Context.h
// has them as one array, which an assignment would copy as a block.
struct ContextMembers {
    Context::Kind mKind;
    Context::Entry _4[4];
    bool _34;
    u32 _38;
    u32 _3C;
    u32 _40;
};

}

#define MF_FUNCTION Create__Q43scn7subgame17SceneSubgameTitle6RecipeFRCQ33scn7subgame7ContextQ43scn7subgame6Result3Seq
SceneSubgameTitle::Recipe SceneSubgameTitle::Recipe::Create(const Context& context, Result::Seq seq) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 key;
    volatile u32 response;
    u32 i;
    u32 word;
    u32 hash;
    u32 limit;
    Recipe recipe;

    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x68F96280
        opword  0x171E5202
    after1:
        mflr    r27
        lwz     r18, 0x0(r27)
        stw     r18, end
        bl      after2
        opword  0x7DB2E007
        opword  0x4C931709
        opword  MF_WORD(0x50)
        opword  0xF858CA80
        opword  0x84307380
    after2:
        mflr    r27
        lwz     r18, 0x8(r27)
        stw     r18, start
    }
    hash = 0;
    *reinterpret_cast<ContextMembers*>(&recipe.mContext) = reinterpret_cast<const ContextMembers&>(context);
    limit = end - start + 1;
    i = 1;
    word = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(word + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    asm {
        bl      after3
        opword  MF_WORD(0x100)
        opword  0xAA211B63
    after3:
        mflr    r30
        lwz     r15, 0x0(r30)
        stw     r15, expected
    }
    hash += hash << 13;
    recipe.mSeq = seq;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if ((hash ^ expected) == 0) {
        goto intact;
    }
    asm {
        bl      after4
        opword  0x8DC2FB09
        opword  0xC80DCC80
        opword  0xEC093380
        opword  MF_WORD(0x160)
    after4:
        mflr    r16
        lwz     r26, 0xc(r16)
        stw     r26, -0x4(r1)
        stw     r16, 0x0(r1)
        stw     r26, -0x4(r1)
        stw     r16, -0x8(r1)
        mtlr    r26
        bl      after5
        opword  MF_WORD(0x184)
        opword  0x08425793
        opword  0x7221A50E
        opword  MF_WORD(0x190)
    after5:
        mflr    r14
        lwz     r21, 0xc(r14)
        stw     r21, key
        lwz     r21, 0x0(r14)
        stw     r14, base
        stw     r21, offset
    }
    offset = offset + 0x7D;
    response = offset + key;
    response = response + base;
    asm {
        lwz     r23, response
        mtlr    r23
        blr
    }
    goto done;
intact:
    return recipe;
done:;
}
#undef MF_FUNCTION

#define MF_FUNCTION __ct__Q33scn7subgame17SceneSubgameTitleFRCQ43scn7subgame17SceneSubgameTitle6Recipe
SceneSubgameTitle::SceneSubgameTitle(const Recipe& recipe)
    : mContext(recipe.mContext)
    , mDpdManager()
    , mMain(0) {
    static volatile int random_bit_of_obfuscation = 0x14;
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 word0;
    volatile u32 word1;
    u32 limit;
    u32 i;
    u32 hash;
    u32 base;
    register u32 addr;
    u32 t0;
    u32 t1;
    u32 t2;

    // Reads 0x80000060 and 0x80000064. The hidden object is written if either is zero.
    addr = random_bit_of_obfuscation + 0x8000004C;
    t0 = 0;
    if (addr - 0x8000004C != random_bit_of_obfuscation + ((u32*)addr)[random_bit_of_obfuscation & 0xB] &&
        (random_bit_of_obfuscation & 0xB) != ((u32*)addr)[(random_bit_of_obfuscation & 4) >> 2]) {
        t0 = 1;
    }
    if (t0 == 0) {
        asm {
            bl      after1
            opword  MF_WORD(0xE4)
            opword  0x20BB0B00
            opword  0x78934693
            opword  MF_WORD(0xF0)
            opword  0x6CCAC60A
            opword  0xF4CB4E81
        after1:
            mflr    r17
            lwz     r28, 0x0(r17)
            mr      addr, r28
            stw     r28, word0
            lwz     r28, 0xc(r17)
            stw     r28, word1
        }
        // The address of the hidden object. Only one operation per statement gives the registers.
        t2 = addr - 0x7A2F677F;
        addr = t2 << 24;
        t2 = t2 >> 8;
        t2 = addr | t2;
        t2 = t2 + 0x5C6B0000;
        t0 = t2 + 0x52F4;
        addr = t0 >> 2;
        t2 = t0 << 30;
        addr = addr | t2;
        t2 = 0x66666666;
        t1 = addr & t2;
        addr = t0 << 2;
        t2 = t0 >> 30;
        addr = addr | t2;
        t2 = 0x99999999;
        t2 = addr & t2;
        t0 = t1 | t2;
        addr = t0 >> 4;
        t2 = t0 << 28;
        addr = addr | t2;
        t2 = 0x96969696;
        t1 = addr & t2;
        addr = t0 << 4;
        t2 = t0 >> 28;
        addr = addr | t2;
        t2 = 0x69696969;
        t2 = addr & t2;
        t2 = t1 | t2;
        t2 = t2 + 0x7919D1BD;
        addr = t2 >> 16;
        t2 = t2 << 16;
        addr = addr | t2;
        t2 = 0xA71458EB;
        t1 = addr & t2;
        t2 = 0x58EBA714;
        t2 = addr & t2;
        t2 = t1 | t2;
        addr = t2 >> 14;
        t2 = t2 << 18;
        t2 = addr | t2;
        t0 = t2 ^ 0xA6B169F6;
        addr = t0 >> 13;
        t2 = t0 >> 2;
        t2 = addr ^ t2;
        t1 = t2 & 1;
        addr = t1 << 13;
        t2 = t1 << 2;
        t2 = addr | t2;
        t1 = t0 ^ t2;
        addr = t1 >> 16;
        t2 = t1 << 16;
        addr = addr | t2;
        t2 = 0xF7E2081D;
        t1 = addr & t2;
        t2 = 0x081DF7E2;
        t2 = addr & t2;
        t2 = t1 | t2;
        t2 = t2 + 0x7AE50000;
        t0 = t2 - 0xDC1;
        addr = t0 >> 2;
        t2 = t0 << 30;
        addr = addr | t2;
        t2 = 0xCCCCCCCC;
        t1 = addr & t2;
        addr = t0 << 2;
        t2 = t0 >> 30;
        addr = addr | t2;
        t2 = 0x33333333;
        t2 = addr & t2;
        t2 = t1 | t2;
        addr = t2 >> 15;
        t2 = t2 << 17;
        t2 = addr | t2;
        addr = t2 ^ 0xE9533AE0;
        t2 = 1;
        *(u32*)addr = t2;
    }
    {
        hel::common::MutableArray<hel::common::FixedString<64>, 24> paths;
        asm {
            bl      after2
            opword  MF_WORD(0x2B8)
            opword  0x9914F83A
        after2:
            mflr    r27
            lwz     r25, 0x0(r27)
            stw     r25, expected
        }
        paths.add(hel::common::FixedString<64>(Context::MenuDN(recipe.mContext.mKind)));
        asm {
            bl      after3
            opword  MF_WORD(0x368)
            opword  MF_WORD(0x36C)
        after3:
            mflr    r22
            lwz     r23, 0x4(r22)
            lwz     r20, 0x0(r22)
            add     r20, r20, r22
            stw     r20, start
            add     r23, r23, r20
            stw     r23, end
        }
        recipe.mContext.addStepDNIfNeccesary(paths);
        hash = 0xC1;
        file::Utility::DNProcess(paths, true);
        file::Utility::SetIsFileLoadWarningEnable(true);
    }
    limit = end - start + 1;
    i = 1;
    base = end;
    tInstance<app::Application>().hidErrorMenu().setup(app::HIDErrorMenu::DISCONNECT_MENU_MODE_0);
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base - 1 - i);
        i += 2;
    }
    tInstance<app::Application>().hidErrorMenu().setIsEnable(true);
    hash ^= hash >> 10;
    mMain.reset(new title::Main(recipe.mContext, recipe.mSeq));
    hash ^= hash << 20;
    file::DNOption option;
    if (hash - expected == 0 || (storage::StoryMode)recipe.mContext._34[3] == 2) {
        tInstance<app::Application>().fdgManager().preLoad("TitleMenuCommon.dn", option);
    } else {
        option._0 = (storage::StoryMode)recipe.mContext._34[3] == 1;
        step::map::KindUtil::PreLoadRequest(
            step::map::KindUtil::GoToShipInStage((storage::StoryMode)recipe.mContext._34[3], false), option);
        for (u32 n = 0; n < 4; n++) {
            const Context::Entry& entry = recipe.mContext._4[n];
            if (!*(const bool*)&entry._8 && (int)entry._0 != 7) {
                tInstance<app::Application>().fdgManager().preLoad(
                    step::hero::AbilityKindUtil::FDNName((step::hero::AbilityKind)entry._4), option);
            }
        }
    }
}
#undef MF_FUNCTION

}
}

namespace hel {
namespace common {

ScopedPtr<scn::subgame::title::Main>::~ScopedPtr() {
    scn::subgame::title::Main* ptr = mPtr;
    mPtr = 0;
    delete ptr;
}

}
}

namespace scn {
namespace subgame {

SceneSubgameTitle::~SceneSubgameTitle() {
}

Result SceneSubgameTitle::result() const {
    Context context = mContext;
    Result result = Result::Create(context);
    result.mSeq = mMain->isBack() ? Result::SEQ_8 : mMain->nextSeq();
    switch (result.mSeq) {
    case Result::SEQ_1:
        result.mContext._34[2] = mContext._34[2];
        break;
    case Result::SEQ_2:
        result.mContext._34[2] = 2;
        break;
    case Result::SEQ_4:
        result.mContext._34[2] = 0;
        break;
    case Result::SEQ_6:
        result.mContext._34[2] = 1;
        break;
    default:
        result.mContext._34[2] = 0;
        break;
    }
    return result;
}

void SceneSubgameTitle::updateUseGPU() {
    mMain->updateUseGPU();
}

#define MF_FUNCTION updateMain__Q33scn7subgame17SceneSubgameTitleFv
void SceneSubgameTitle::updateMain() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    u32 i;
    u32 hash;
    u32 word;
    u32 limit;

    hash = 0xB5;
    asm {
        bl      after1
        opword  0xE8961892
        opword  0xE2B2BC04
        opword  MF_WORD(0x30)
        opword  MF_WORD(0x34)
        opword  0x11DDD101
    after1:
        mflr    r24
        lwz     r30, 0xc(r24)
        lwz     r15, 0x8(r24)
        stw     r15, end
        stw     r30, start
    }
    word = start;
    limit = end - word + 1;
    mMain->updateMain();
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(word + i - 1);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    asm {
        bl      after2
        opword  MF_WORD(0xB4)
        opword  0x0ED329C2
    after2:
        mflr    r21
        lwz     r22, 0x0(r21)
        stw     r22, expected
    }
    if (hash == expected) {
        goto intact;
    }
    asm {
        bl      after3
        opword  0x07DD700B
        opword  MF_WORD(0xDC)
    after3:
        mflr    r30
        lwz     r18, 0x4(r30)
        stw     r18, -0x4(r1)
        stw     r30, 0x0(r1)
        stw     r18, -0x4(r1)
        stw     r30, -0x8(r1)
        mtlr    r18
        bl      after4
        opword  MF_WORD(0x100)
        opword  MF_WORD(0x104)
    after4:
        mflr    r19
        stw     r19, base
        lwz     r23, 0x0(r19)
        stw     r23, offset
        lwz     r26, 0x4(r19)
        stw     r26, key
    }
    key = 0;
    response = offset;
    response = response + base;
    asm {
        lwz     r27, response
        mtlr    r27
        blr
    }
    goto done;
intact:
    if (isSceneEnd() && mMain->nextSeq() != Result::SEQ_8) {
        tInstance<app::Application>().preLoadManager().cancel();
    }
done:;
}
#undef MF_FUNCTION

void SceneSubgameTitle::updateDebug() {
    mMain->updateDebug();
}

void SceneSubgameTitle::draw(const DrawReqInfo&) {
    mMain->draw();
}

bool SceneSubgameTitle::isSceneEnd() const {
    return mMain->isSceneEnd();
}

}
}
