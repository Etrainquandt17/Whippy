#include "seq/SequenceStep.h"

#include "app/Application.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/RuntimeTypeInfo.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "metafortress.h"
#include "scn/step/ContextHeroIndivi.h"
#include "scn/step/SceneStep.h"
#include "storage/StorageManager.h"
#include "storage/VolatileData.h"

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceStep>();

}
}

namespace seq {

#define MF_FUNCTION Create__Q33seq12SequenceStep6RecipeFRCQ33scn4step7Context
SequenceStep::Recipe SequenceStep::Recipe::Create(const scn::step::Context& context) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 addend;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    Recipe recipe = {};
    asm {
        bl      after1
        opword  0x700A2B80
        opword  MF_WORD(0x4C)
        opword  0x2E7F3903
        opword  0xB203080D
    after1:
        mflr    r20
        lwz     r15, 0x4(r20)
        stw     r15, end
        bl      after2
        opword  MF_WORD(0x68)
        opword  0xB6D30204
    after2:
        mflr    r20
        lwz     r15, 0x0(r20)
        stw     r15, start
    }
    hash = 0xC1;
    limit = end - start + 1;
    first = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(first + i - 1);
    }
    recipe.mContext = context;
    asm {
        bl      after3
        opword  MF_WORD(0xD0)
        opword  0x7CE60B0C
    after3:
        mflr    r18
        lwz     r29, 0x0(r18)
        stw     r29, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0) {
        return recipe;
    }
    asm {
        bl      after4
        opword  0x4CD07281
        opword  0xE8985591
        opword  MF_WORD(0x138)
    after4:
        mflr    r17
        lwz     r19, 0x8(r17)
        stw     r19, -0x4(r1)
        stw     r17, 0x0(r1)
        stw     r19, -0x4(r1)
        stw     r17, -0x8(r1)
        mtlr    r19
        bl      after5
        opword  MF_WORD(0x15C)
        opword  0x547AEA80
        opword  0x105AF080
        opword  MF_WORD(0x168)
    after5:
        mflr    r28
        stw     r28, base
        lwz     r18, 0x0(r28)
        stw     r18, offset
        lwz     r30, 0xc(r28)
        stw     r30, addend
    }
    offset = offset ^ 0x5A;
    response = offset ^ addend;
    response = response + base;
    asm {
        lwz     r19, response
        mtlr    r19
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION __ct__Q23seq12SequenceStepFRCQ33seq12SequenceStep6Recipe
SequenceStep::SequenceStep(const Recipe& recipe)
    : mContext(recipe.mContext)
    , _FC8(true) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 response;
    u32 tail;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    hash = 0x811C9DDB;
    hel::common::ExplicitSingleton<app::Application>::object_->storageManager().volatileData().onEnterStage();
    asm {
        bl      after1
        opword  MF_WORD(0x70)
        opword  0x70C7B291
        opword  MF_WORD(0x78)
        opword  0xA86CE693
        opword  0xAF41D002
    after1:
        mflr    r30
        lwz     r15, 0x0(r30)
        add     r15, r15, r30
        stw     r15, start
        lwz     r21, 0x8(r30)
        add     r15, r15, r21
        stw     r15, end
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0xB0541ACA
    after2:
        mflr    r16
        lwz     r30, 0x0(r16)
        stw     r30, expected
    }
    i = 1;
    tail = end;
    limit = tail - start + 1;
    scn::step::ContextHeroIndivi::Unk38 zero = {};
    last = tail - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x01000193;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash != expected) {
        asm {
            bl      after3
            opword  0xB4257790
            opword  0xCCB3F480
            opword  MF_WORD(0x12C)
        after3:
            mflr    r29
            lwz     r21, 0x8(r29)
            stw     r21, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r21
            bl      after4
            opword  MF_WORD(0x150)
            opword  MF_WORD(0x154)
        after4:
            mflr    r17
            stw     r17, base
            lwz     r19, 0x0(r17)
            stw     r19, offset
            lwz     r22, 0x4(r17)
            stw     r22, addend
        }
        offset = offset + 4;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        for (u32 n = 0; n < 4; n++) {
            mContext.mHero.mIndivi[n]._38 = zero;
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION nextAction__Q23seq12SequenceStepCFv
int SequenceStep::nextAction() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    register u32 limit;
    register u32 i;
    register u32 base;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x3A559204
        opword  0x941D8780
    after1:
        mflr    r14
        lwz     r16, 0x0(r14)
        add     r16, r16, r14
        stw     r16, start
        bl      after2
        opword  0x2CBA5191
        opword  MF_WORD(0x44)
        opword  0x565E1706
        opword  0x004F4B90
    after2:
        mflr    r14
        lwz     r19, 0x4(r14)
        add     r16, r16, r19
        stw     r16, end
        li      i, 1
        lwz     base, start
        lwz     limit, end
        subf    limit, base, limit
        addi    limit, limit, 1
        bl      after3
        opword  MF_WORD(0x78)
        opword  0x2AA779B0
    after3:
        mflr    r30
        lwz     r23, 0x0(r30)
        stw     r23, expected
    }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 61;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    return (hash - expected != 0 || _FC8) ? 2 : 0;
}
#undef MF_FUNCTION
std::auto_ptr<ISequence> SequenceStep::createChildSequence() const {
    return std::auto_ptr<ISequence>();
}

void SequenceStep::onChildSequenceEnd(ISequence&) {
}

#define MF_FUNCTION createScene__Q23seq12SequenceStepCFv
std::auto_ptr<scn::IScene> SequenceStep::createScene() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0xF4A27E80
        opword  MF_WORD(0x24)
        opword  0x081A2281
        opword  MF_WORD(0x2C)
    after1:
        mflr    r18
        lwz     r25, 0xc(r18)
        lwz     r26, 0x4(r18)
        stw     r26, end
        stw     r25, start
        bl      after2
        opword  MF_WORD(0x48)
        opword  0xC0274A87
    after2:
        mflr    r30
        lwz     r29, 0x0(r30)
        stw     r29, expected
    }
    hash = 0x811C9E07;
    i = 1;
    last = end;
    limit = last - start + 1;
    last--;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001A7;
        i += 2;
    }
    while (hash - expected != 0) {
    }
    return std::auto_ptr<scn::IScene>(
        new scn::step::SceneStep(scn::step::SceneStep::Recipe::Create(mContext)));
}
#undef MF_FUNCTION
void SequenceStep::onSceneEnd(scn::IScene& scene) {
    mResult = hel::common::DynamicCastToRef<scn::step::SceneStep, scn::IScene>(&scene).result();
    _FC8 = mResult._0 == 1;
    if (_FC8) {
        mContext = mResult.mContext;
    }
}

#define MF_FUNCTION result__Q23seq12SequenceStepCFv
scn::step::SceneStep::Result SequenceStep::result() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 addend;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xF8C7E590
        opword  0xF7902003
        opword  MF_WORD(0x38)
        opword  0x0CBE1991
    after1:
        mflr    r30
        lwz     r21, 0xc(r30)
        lwz     r29, 0x0(r30)
        add     r21, r29, r21
        stw     r21, end
        stw     r29, start
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (; i != limit; i += 2) {
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    limit = hash << 3;
    hash += limit;
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0xE213B244
    after2:
        mflr    r15
        lwz     r19, 0x0(r15)
        stw     r19, expected
    }
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    i = limit & ~hash;
    limit = expected;
    limit = hash & ~limit;
    hash = i | limit;
    limit = hash << 10;
    hash = hash | limit;
    if (hash == 0) {
        return mResult;
    }
    asm {
        bl      after3
        opword  0x08F11581
        opword  0x803FF193
        opword  MF_WORD(0x120)
    after3:
        mflr    r30
        lwz     r18, 0x8(r30)
        stw     r18, -0x4(r1)
        stw     r30, 0x0(r1)
        stw     r18, -0x4(r1)
        stw     r30, -0x8(r1)
        mtlr    r18
        bl      after4
        opword  MF_WORD(0x144)
        opword  0x5CF53F93
        opword  0x38861604
        opword  MF_WORD(0x150)
    after4:
        mflr    r26
        stw     r26, base
        lwz     r21, 0x0(r26)
        stw     r21, offset
        lwz     r14, 0xc(r26)
        stw     r14, addend
    }
    offset = offset - 0xBB;
    response = offset ^ addend;
    response = response + base;
    asm {
        lwz     r27, response
        mtlr    r27
        blr
    }
}
#undef MF_FUNCTION

const hel::common::RuntimeTypeInfo& SequenceStep::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SequenceStep>();
}

SequenceStep::~SequenceStep() {
}

}
