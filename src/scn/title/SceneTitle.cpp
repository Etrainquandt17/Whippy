#include "scn/title/SceneTitle.h"

#include "app/Application.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/RuntimeTypeInfo.h"
#include "metafortress.h"
#include "nand/NandManager.h"
#include "scn/title/Main.h"

// TODO: hel/common/RuntimeTypeInfo.h does not define this yet; the unit holds its own copy.
namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::title::SceneTitle>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::IScene>(), RuntimeTypeInfo::NoName());
    return ti;
}

}
}

namespace scn {
namespace title {

namespace {

#define MF_FUNCTION tNANDManager__Q33scn5title28_unnamed_SceneTitle_prt_cpp_Fv
nand::NandManager& tNANDManager() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 key;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xE8434593
        opword  MF_WORD(0x2C)
        opword  0xF0135F80
        opword  0x444CB880
    after1:
        mflr    r29
        lwz     r24, 0x0(r29)
        lwz     r16, 0x8(r29)
        add     r24, r24, r29
        add     r16, r16, r24
        stw     r24, start
        stw     r16, end
        bl      after2
        opword  MF_WORD(0x58)
        opword  0xAA3D2052
    after2:
        mflr    r19
        lwz     r25, 0x0(r19)
        stw     r25, expected
    }
    last = end;
    word = start;
    for (; word != last; word += 2) {
        hash *= 61;
        hash += *(u16*)word;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash = expected ^ hash;
    hash += hash * 30;
    if (hash == 0) {
        return hel::common::ExplicitSingleton<app::Application>::object_->nandManager();
    }
    asm {
        bl      after3
        opword  MF_WORD(0xD0)
    after3:
        mflr    r28
        lwz     r30, 0x0(r28)
        stw     r30, -0x4(r1)
        stw     r28, 0x0(r1)
        stw     r30, -0x4(r1)
        stw     r28, -0x8(r1)
        mtlr    r30
        bl      after4
        opword  MF_WORD(0xF4)
        opword  0xEFDF9C0D
        opword  0x25B0430B
        opword  MF_WORD(0x100)
    after4:
        mflr    r20
        lwz     r26, 0x0(r20)
        lwz     r18, 0xC(r20)
        stw     r18, key
        stw     r26, offset
        stw     r20, base
    }
    offset = offset - 0xB9;
    response = offset ^ key;
    response = response + base;
    asm {
        lwz     r27, response
        mtlr    r27
        blr
    }
}
#undef MF_FUNCTION

}

SceneTitle::SceneTitle(const Recipe& recipe)
    : mState(0)
    , mMain() {
    mMain.reset(new Main(recipe._0));
    tNANDManager().loadData();
}

SceneTitle::~SceneTitle() {
}

#define MF_FUNCTION result__Q33scn5title10SceneTitleCFv
int SceneTitle::result() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 base;
    volatile u32 response;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x189D0492
    after1:
        mflr    r27
        lwz     r16, 0x0(r27)
        lwz     r29, 0x4(r27)
        stw     r29, end
        stw     r16, start
    }
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x58)
        opword  0x76994DEF
    after2:
        mflr    r26
        lwz     r22, 0x0(r26)
        stw     r22, expected
    }
    hash = 0x811C9E07;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
    }
    hash -= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xB8)
        after3:
            mflr    r29
            lwz     r19, 0x0(r29)
            stw     r19, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0xDC)
            opword  0xECEACE93
            opword  0x905BD791
            opword  MF_WORD(0xE8)
        after4:
            mflr    r17
            lwz     r28, 0x0(r17)
            stw     r17, base
            lwz     r18, 0xC(r17)
            stw     r28, offset
            stw     r18, key
        }
        response = offset + key;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        return mMain->result();
    }
}
#undef MF_FUNCTION

void SceneTitle::updateUseGPU() {
    mMain->updateUseGPU();
}

#define MF_FUNCTION updateMain__Q33scn5title10SceneTitleFv
void SceneTitle::updateMain() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  MF_WORD(0x20)
        opword  0x1BDDA908
    after1:
        mflr    r29
        lwz     r26, 0x0(r29)
        stw     r26, start
        lwz     r26, 0x4(r29)
        stw     r26, end
    }
    hash = 0x811C9E07;
    last = end;
    word = start;
    asm {
        bl      after2
        opword  MF_WORD(0x50)
        opword  0x0C5F25CC
    after2:
        mflr    r25
        lwz     r20, 0x0(r25)
        stw     r20, expected
    }
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x010001A7;
    }
    switch (mState) {
    case 0:
        if (hash - expected == 0 && !tNANDManager().isBusy() && !tNANDManager().isError()) {
            if (tNANDManager().getState() == 1) {
                tNANDManager().saveData();
            } else if (tNANDManager().isOK()) {
                mMain->start();
                mState = 1;
            }
        }
        break;
    case 1:
        break;
    }
    mMain->updateMain();
}
#undef MF_FUNCTION

void SceneTitle::updateDebug() {
    mMain->updateDebug();
}

void SceneTitle::draw(const DrawReqInfo& info) {
    mMain->draw();
}

bool SceneTitle::isSceneEnd() const {
    return mMain->isSceneEnd();
}

const hel::common::RuntimeTypeInfo& SceneTitle::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SceneTitle>();
}

}
}
