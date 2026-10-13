#include "seq/SequenceWMapRoot.h"

#include "app/Application.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/RuntimeTypeInfo.h"
#include "hid/HIDManager.h"
#include "hid/SimpleWRHID.h"
#include "metafortress.h"
#include "scn/wmap/SceneWMap.h"
#include "seq/SequenceLvMapRoot.h"
#include "seq/SequenceShipMapRoot.h"
#include "storage/BackupFileData.h"
#include "storage/StorageManager.h"
#include "storage/StoryData.h"

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceWMapRoot>();

}
}

namespace seq {

namespace {

// TODO: storage::StoryData has no member for its level data yet, which starts at 0xF4.
inline const storage::StoryData::LevelData& t_levelData(const storage::StoryData& data, u32 level) {
    return reinterpret_cast<const storage::StoryData::LevelData*>(&data._F2[2])[level];
}

inline scn::wmap::ItemKind t_shipItemKind(storage::BackupFileData& file, storage::StoryMode mode) {
    return file.storyData(mode)._0[3] ? scn::wmap::ITEM_KIND_9 : scn::wmap::ITEM_KIND_5;
}

inline u32 t_latestLevel(storage::StoryMode mode) {
    for (u32 i = 0; i < 7; i++) {
        u32 level = 6 - i;
        if (t_levelData(hel::common::ExplicitSingleton<app::Application>::object_->storageManager().selectedBackupFileData().storyData(mode), level)._4) {
            return level;
        }
    }
    return 7;
}

inline int t_levelValue(scn::step::LevelKind level) {
    switch (level) {
    case scn::step::LEVEL_KIND_0:
        return 0;
    case scn::step::LEVEL_KIND_1:
        return 1;
    case scn::step::LEVEL_KIND_2:
        return 2;
    case scn::step::LEVEL_KIND_3:
        return 3;
    case scn::step::LEVEL_KIND_4:
        return 4;
    default:
        return 0;
    }
}

}

SequenceWMapRoot::Recipe SequenceWMapRoot::Recipe::Create(const ContextStory& context, ItemKind item, InterruptKind interrupt,
                                                          bool flag) {
    Recipe recipe = {};
    recipe.mContext = context;
    recipe.mItemKind = item;
    recipe.mInterruptKind = interrupt;
    recipe._488 = flag;
    return recipe;
}

SequenceWMapRoot::SequenceWMapRoot(const Recipe& recipe)
    : _8(recipe.mItemKind)
    , mInterruptKind(recipe.mInterruptKind)
    , mContext(recipe.mContext)
    , mContextMode(scn::step::ContextMode::Create())
    , mLevelKind(scn::step::LEVEL_KIND_0) {
    mItemKind = t_shipItemKind(hel::common::ExplicitSingleton<app::Application>::object_->storageManager().selectedBackupFileData(),
                               recipe.mContext.mStoryMode);
    _4AC = false;
    mMode = MODE_WMAP;
    for (u32 i = 0; i < 4; i++) {
        if (i != 0 && mContext.mHero.getIndivi(i)._0 != 0 && mContext.mHero.getIndivi(i)._0 != 1 &&
            !hel::common::ExplicitSingleton<hid::HIDManager>::object_->gameWR(i).isConnected()) {
            mContext.mHero.mIndivi[i]._0 = 1;
        }
    }
    for (u32 i = 0; i < 4; i++) {
        if (i != 0 && mContext.mHero.getIndivi(i)._0 == 2) {
            mContext.mHero._4--;
        }
    }
    if (mInterruptKind == INTERRUPT_KIND_1) {
        mLevelKind = static_cast<scn::step::LevelKind>(t_latestLevel(mContext.mStoryMode));
        mfSetupClearDemo();
    } else {
        mMode = MODE_WMAP;
    }
    mContextMode._C = mContext.mStoryMode;
}

SequenceWMapRoot::~SequenceWMapRoot() {
}

// TODO: the loop was C in the original (see docs/decompiling.md). In that form
// this and hash do not get r30 and r31 in any order of the declarations.
#define MF_FUNCTION nextAction__Q23seq16SequenceWMapRootCFv
int SequenceWMapRoot::nextAction() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    register u32 hash;

    asm {
        bl      after1
        opword  0xB49DA093
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0xDCA97C80
        opword  0xC06FAA80
    after1:
        mflr    r28
        lwz     r22, 0x8(r28)
        lwz     r25, 0x4(r28)
        stw     r25, end
        stw     r22, start
        lwz     r27, end
        lwz     r24, start
        subf    r26, r24, r27
        lis     r24, 0x811D
        subi    hash, r24, 0x623B
        li      r23, -1
        subi    r24, r27, 1
        lis     r29, 0x100
        addi    r27, r29, 0x181
        subi    r29, r26, 1
        b       test
    next:
        addi    r23, r23, 2
        subf    r26, r23, r24
        lhz     r26, 0x0(r26)
        xor     hash, hash, r26
        mullw   hash, hash, r27
    test:
        cmplw   cr4, r23, r29
        bne     cr4, next
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x34C468CC
    after2:
        mflr    r20
        lwz     r22, 0x0(r20)
        stw     r22, expected
    }
    switch (mMode) {
    case MODE_WMAP:
        return 2;
    case MODE_LVMAP:
        return 1;
    case MODE_SHIPMAP:
        return 1;
    case MODE_3:
        return 0;
    default:
        while (hash - expected != 0) {
        }
        return 0;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION createChildSequence__Q23seq16SequenceWMapRootCFv
std::auto_ptr<ISequence> SequenceWMapRoot::createChildSequence() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u16* word;
    u16* last;

    std::auto_ptr<ISequence> result;
    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x5C13620A
        opword  0x0CDB0A93
        opword  MF_WORD(0x38)
        opword  0xEF28800E
    after1:
        mflr    r16
        lwz     r25, 0x0(r16)
        add     r25, r25, r16
        lwz     r21, 0xc(r16)
        stw     r25, start
        add     r21, r21, r25
        stw     r21, end
    }
    word = (u16*)start;
    last = (u16*)end;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0xFA547161
    after2:
        mflr    r20
        lwz     r27, 0x0(r20)
        stw     r27, expected
    }
    for (; word != last; word++) {
        hash += *word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    switch (mMode) {
    case MODE_LVMAP:
        result.reset(new SequenceLvMapRoot(SequenceLvMapRoot::Recipe::Create(mLevelKind, mContext)));
        break;
    case MODE_SHIPMAP:
        result.reset(new SequenceShipMapRoot(
            SequenceShipMapRoot::Recipe::Create(mContext, mContextMode, mItemKind == scn::wmap::ITEM_KIND_9, _4AC)));
        break;
    default:
        while (hash - expected != 0) {
        }
        break;
    }
    return result;
}
#undef MF_FUNCTION

#define MF_FUNCTION onChildSequenceEnd__Q23seq16SequenceWMapRootFRQ23seq9ISequence
void SequenceWMapRoot::onChildSequenceEnd(ISequence& child) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 hash;
    u32 i;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0xCC288893
        opword  MF_WORD(0x28)
    after1:
        mflr    r22
        lwz     r15, 0x8(r22)
        lwz     r27, 0x0(r22)
        stw     r27, end
        stw     r15, start
        bl      after2
        opword  MF_WORD(0x44)
        opword  0x01159526
    after2:
        mflr    r19
        lwz     r26, 0x0(r19)
        stw     r26, expected
    }
    hash = 0xC1;
    i = 1;
    last = end;
    limit = last - start + 1;
    last--;
    for (; i != limit; i += 2) {
        hash = (hash << 4) ^ (hash >> 28);
        hash ^= *(u16*)(last - i);
    }
    switch (mMode) {
    case MODE_LVMAP:
        onChildSequenceEndForLvMap(child);
        break;
    case MODE_SHIPMAP:
        onChildSequenceEndForShipMap(child);
        break;
    default:
        while (hash - expected != 0) {
        }
        break;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION createScene__Q23seq16SequenceWMapRootCFv
std::auto_ptr<scn::IScene> SequenceWMapRoot::createScene() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  0x6CD37280
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
    after1:
        mflr    r28
        lwz     r30, 0x8(r28)
        stw     r30, start
        lwz     r21, 0x4(r28)
        stw     r21, end
        bl      after2
        opword  MF_WORD(0x48)
        opword  0x7EC86FCE
    after2:
        mflr    r28
        lwz     r29, 0x0(r28)
        stw     r29, expected
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    switch (mMode) {
    case MODE_WMAP:
        return std::auto_ptr<scn::IScene>(new scn::wmap::SceneWMap(
            scn::wmap::SceneWMap::Recipe::Create(mContext.mStoryMode, mContext.mHero, mItemKind)));
    default:
        while (hash - expected != 0) {
        }
        return std::auto_ptr<scn::IScene>();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION onSceneEnd__Q23seq16SequenceWMapRootFRQ23scn6IScene
void SequenceWMapRoot::onSceneEnd(scn::IScene& scene) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u16* word;
    u16* last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x774F91BF
    after1:
        mflr    r24
        lwz     r17, 0x0(r24)
        stw     r17, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  0x24E14480
        opword  MF_WORD(0x40)
        opword  MF_WORD(0x44)
        opword  0x6C985592
        opword  0xE8AC6B92
    after2:
        mflr    r21
        lwz     r23, 0x8(r21)
        lwz     r17, 0x4(r21)
        add     r23, r17, r23
        stw     r23, end
        stw     r17, start
    }
    word = (u16*)start;
    last = (u16*)end;
    word--;
    for (;;) {
        word++;
        if (word == last) {
            break;
        }
        hash += *word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    switch (mMode) {
    case MODE_WMAP:
        onSceneEndForWMap(scene);
        break;
    default:
        while (hash - expected != 0) {
        }
        break;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION onSceneEndForWMap__Q23seq16SequenceWMapRootFRQ23scn6IScene
void SequenceWMapRoot::onSceneEndForWMap(scn::IScene& scene) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 addend;
    volatile u32 base;
    u32 word;
    u32 last;
    u32 hash;

    scn::wmap::SceneWMap::Result result = hel::common::DynamicCastToRef<scn::wmap::SceneWMap, scn::IScene>(&scene).result();
    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0xA4)
    after1:
        mflr    r18
        lwz     r22, 0x0(r18)
        add     r22, r22, r18
        stw     r22, start
        bl      after2
        opword  MF_WORD(0xBC)
        opword  0x0C863480
        opword  0x97C6EF04
    after2:
        mflr    r18
        lwz     r19, 0x0(r18)
        add     r22, r22, r19
        stw     r22, end
    }
    mContext.mStoryMode = result.mStoryMode;
    asm {
        bl      after3
        opword  MF_WORD(0xE4)
        opword  0xD8498C1E
    after3:
        mflr    r15
        lwz     r30, 0x0(r15)
        stw     r30, expected
    }
    word = start;
    last = end;
    mContext.mHero = result.mHero;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x01000181;
    }
    hash += hash << 3;
    mItemKind = result.mItemKind;
    hash ^= hash >> 11;
    hash += hash << 15;
    if ((hash ^ expected) != 0) {
        asm {
            bl      after4
            opword  0xEB2FE60E
            opword  0x29D23009
            opword  MF_WORD(0x1B4)
        after4:
            mflr    r26
            lwz     r24, 0x8(r26)
            stw     r24, -0x4(r1)
            stw     r26, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r26, -0x8(r1)
            mtlr    r24
            bl      after5
            opword  MF_WORD(0x1D8)
            opword  0x12099B06
            opword  MF_WORD(0x1E0)
        after5:
            mflr    r24
            lwz     r16, 0x8(r24)
            stw     r16, addend
            lwz     r16, 0x0(r24)
            stw     r24, base
            stw     r16, offset
        }
        offset = offset - 0xA8;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        switch (result._0) {
        case 0:
            mResult._0 = 0;
            mResult.mContext = mContext;
            mMode = MODE_3;
            break;
        case 1:
            mLevelKind = result.mLevelKind;
            mMode = MODE_LVMAP;
            break;
        case 2:
            mMode = MODE_SHIPMAP;
            break;
        }
    }
}
#undef MF_FUNCTION

SequenceWMapRoot::Result SequenceWMapRoot::result() const {
    return mResult;
}

void SequenceWMapRoot::onChildSequenceEndForLvMap(ISequence& child) {
    SequenceLvMapRoot::Result result = hel::common::DynamicCastToRef<SequenceLvMapRoot, ISequence>(&child).result();
    mContext = result.mContext;
    hel::common::ExplicitSingleton<app::Application>::object_->storageManager().selectedBackupFileData().storyData(mContext.mStoryMode);
    if (result._480 == 3) {
        mfSetupClearDemo();
    } else {
        switch (result._480) {
        case 0:
            mMode = MODE_WMAP;
            break;
        case 1:
            mResult._0 = 0;
            mResult.mContext = mContext;
            mMode = MODE_3;
            break;
        case 2:
            mResult._0 = 1;
            mResult.mContext = mContext;
            mMode = MODE_3;
            break;
        }
    }
}

#define MF_FUNCTION onChildSequenceEndForShipMap__Q23seq16SequenceWMapRootFRQ23seq9ISequence
void SequenceWMapRoot::onChildSequenceEndForShipMap(ISequence& child) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 size;
    u32 hash;

    SequenceShipMapRoot::Result result = hel::common::DynamicCastToRef<SequenceShipMapRoot, ISequence>(&child).result();
    asm {
        bl      after1
        opword  MF_WORD(0x94)
    after1:
        mflr    r30
        lwz     r16, 0x0(r30)
        add     r16, r16, r30
        stw     r16, start
        bl      after2
        opword  0xE0EB3D80
        opword  MF_WORD(0xB0)
    after2:
        mflr    r30
        lwz     r24, 0x4(r30)
        add     r16, r16, r24
        stw     r16, end
        bl      after3
        opword  MF_WORD(0xC8)
        opword  0xA4F154B9
    after3:
        mflr    r17
        lwz     r15, 0x0(r17)
        stw     r15, expected
    }
    mContext = result.mContext;
    hash = 0xB3;
    size = end - start;
    base = start;
    _4AC = false;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    switch (result._480) {
    case 1:
        mResult._0 = 0;
        mResult.mContext = mContext;
        mMode = MODE_3;
        break;
    case 0:
        mContextMode._0 = 0;
        mMode = MODE_WMAP;
        break;
    default:
        while (hash - expected != 0) {
        }
        break;
    }
}
#undef MF_FUNCTION

void SequenceWMapRoot::mfSetupClearDemo() {
    switch (mLevelKind) {
    case scn::step::LEVEL_KIND_0:
    case scn::step::LEVEL_KIND_1:
    case scn::step::LEVEL_KIND_2:
    case scn::step::LEVEL_KIND_3:
    case scn::step::LEVEL_KIND_4:
        mfSetupClearDemoConnectToRepair();
        mMode = MODE_SHIPMAP;
        break;
    case scn::step::LEVEL_KIND_5:
        mfSetupClearDemoConnectToLandiaInfo();
        mMode = MODE_SHIPMAP;
        break;
    }
}

void SequenceWMapRoot::mfSetupClearDemoConnectToRepair() {
    storage::StoryData& data = hel::common::ExplicitSingleton<app::Application>::object_->storageManager().selectedBackupFileData().storyData(mContext.mStoryMode);
    mContextMode._0 = 1;
    mContextMode._10 = mLevelKind;
    mContext.mHero._C = 13;
    mContext.mHero.mIndivi[0]._8[2] = 10;
    mContext.mHero.mIndivi[0]._8[3] = t_levelValue(mLevelKind);
    mContext.mHero._0 = 2;
    if (mLevelKind != scn::step::LEVEL_KIND_4) {
        mItemKind = scn::wmap::ITEM_KIND_5;
    } else {
        mItemKind = scn::wmap::ITEM_KIND_9;
    }
    _4AC = false;
    if (mLevelKind < 6) {
        data.levelData(static_cast<scn::step::LevelKind>(mLevelKind + 1))._0 = 1;
    }
}

void SequenceWMapRoot::mfSetupClearDemoConnectToLandiaInfo() {
    storage::StoryData& data = hel::common::ExplicitSingleton<app::Application>::object_->storageManager().selectedBackupFileData().storyData(mContext.mStoryMode);
    mContextMode = scn::step::ContextMode::Create();
    mContextMode._C = mContext.mStoryMode;
    mContextMode._10 = mLevelKind;
    mContext.mHero._C = 15;
    mContext.mHero._0 = 2;
    mItemKind = scn::wmap::ITEM_KIND_9;
    _4AC = true;
    if (mLevelKind < 6) {
        data.levelData(static_cast<scn::step::LevelKind>(mLevelKind + 1))._0 = 1;
    }
}

const hel::common::RuntimeTypeInfo& SequenceWMapRoot::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SequenceWMapRoot>();
}

}
