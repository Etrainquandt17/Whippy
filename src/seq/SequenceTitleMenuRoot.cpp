#include "seq/SequenceTitleMenuRoot.h"

#include "hel/common/RuntimeTypeInfo.h"
#include "metafortress.h"
#include "revolution/ipc.h"
#include "scn/movie/SceneMovie.h"
#include "scn/option/SceneOption.h"
#include "scn/soundroom/SceneSoundRoom.h"
#include "scn/subgame/Context.h"
#include "scn/theaterroom/SceneTheaterRoom.h"
#include "scn/titlemenunew/SceneTitleMenu.h"
#include "seq/SequenceArenaRoot.h"
#include "seq/SequenceCallScene.h"
#include "seq/SequenceOpeningRoot.h"
#include "seq/SequenceSimpleScene.h"
#include "seq/SequenceSubgame.h"
#include "seq/SequenceTheaterRoomRoot.h"

// TODO: hel/common/RuntimeTypeInfo.h does not define these yet; the unit holds its own copies.
namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceCallScene<scn::option::SceneOption> >() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<seq::ISequence>(), RuntimeTypeInfo::NoName());
    return ti;
}

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceSimpleScene<scn::soundroom::SceneSoundRoom> >() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<seq::ISequence>(), RuntimeTypeInfo::NoName());
    return ti;
}

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceSimpleScene<scn::theaterroom::SceneTheaterRoom> >() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<seq::ISequence>(), RuntimeTypeInfo::NoName());
    return ti;
}

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceTitleMenuRoot>();

}
}

namespace seq {

namespace {

// TODO: how the original made the two colours is not known. They are temporaries, each with a constant of its own.
inline GXColor t_preFadeColor() {
    GXColor color = {0, 0, 0, 0xFF};
    return color;
}

inline GXColor t_postFadeColor() {
    GXColor color = {0, 0, 0, 0xFF};
    return color;
}

}

#define MF_FUNCTION __ct__Q23seq21SequenceTitleMenuRootFv
SequenceTitleMenuRoot::SequenceTitleMenuRoot()
    : _4(2)
    , _8(false)
    , _28(0) {
    volatile u32 c;
    volatile u32 a;
    volatile u32 d;
    volatile u32 b;
    static const u32 n = 11;
    bool closed = true;
    {
        const u32 data[11] = {
            0x7A897D78, 0x3822885B, 0xA470B92B, 0x75FE9A27, 0xBC5F2B63, 0x5A52366D,
            0xA0DA8C1A, 0x2AB23540, 0xFA2C85F0, 0xEEA01427, 0x0E112680,
        };
        const u32 key[4] = {0x36ED081A, 0x12767FF9, 0x4EA773E8, 0x70E79500};
        u32 v[11];
        u32 y;
        u32 z;
        u32 sum;
        u32 p;
        u32 e;
        u32 q;
        u32 i;
        s32 fd;

        for (i = 0; i < n; i++) {
            v[i] = data[i];
        }
        q = 6 + 52 / n;
        sum = q * 0x9E3779B9;
        y = v[0];
        do {
            e = (sum >> 2) & 3;
            for (p = n - 1; p > 0; p--) {
                z = v[p - 1];
                y = v[p] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (z ^ key[(p & 3) ^ e]));
            }
            z = v[n - 1];
            y = v[0] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (z ^ key[(p & 3) ^ e]));
            sum -= 0x9E3779B9;
        } while (sum != 0);
        for (i = 0; i < n; i++) {
            ((char*)v)[i] = (char)v[i];
        }
        fd = IOS_Open((char*)v, 0);
        if (fd >= 0) {
            closed = false;
            IOS_Close(fd);
        }
    }
    if (!closed) {
        asm {
            bl      after1
            opword  MF_WORD(0x204)
            opword  0xECDBE090
            opword  0xB4B91380
            opword  MF_WORD(0x210)
        after1:
            mflr    r29
            stw     r29, c
            lwz     r15, 0x0(r29)
            stw     r15, b
            lwz     r14, 0xc(r29)
            stw     r14, a
        }
        b = b - 0x70;
        a = 0;
        d = b;
        d = d + c;
        asm {
            lwz     r15, d
            mtlr    r15
            blr
        }
    }
    mRecipe._0 = 0;
    mRecipe._8 = true;
    mRecipe.mEntryInfo = EntryInfo::Create();
}
#undef MF_FUNCTION

SequenceTitleMenuRoot::~SequenceTitleMenuRoot() {
}

#define MF_FUNCTION nextAction__Q23seq21SequenceTitleMenuRootCFv
int SequenceTitleMenuRoot::nextAction() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 base;
    volatile u32 addend;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;
    u32 tail;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x5CF34692
        opword  0x58E5B480
        opword  MF_WORD(0x30)
    after1:
        mflr    r24
        lwz     r21, 0xc(r24)
        lwz     r29, 0x0(r24)
        add     r21, r29, r21
        stw     r21, end
        stw     r29, start
    }
    hash = 0xC5;
    limit = end - start + 1;
    i = 1;
    tail = end;
    asm {
        bl      after2
        opword  MF_WORD(0x6C)
        opword  0x5ED50BD3
    after2:
        mflr    r19
        lwz     r18, 0x0(r19)
        stw     r18, expected
    }
    last = tail - 1;
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - i);
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    hash -= limit;
    if (hash == 0) {
        return _4;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xE0)
    after3:
        mflr    r26
        lwz     r15, 0x0(r26)
        stw     r15, -0x4(r1)
        stw     r26, 0x0(r1)
        stw     r15, -0x4(r1)
        stw     r26, -0x8(r1)
        mtlr    r15
        bl      after4
        opword  MF_WORD(0x104)
        opword  0x96CD0508
        opword  0x7CB78280
        opword  MF_WORD(0x110)
    after4:
        mflr    r15
        lwz     r14, 0x0(r15)
        lwz     r23, 0xc(r15)
        stw     r23, addend
        stw     r14, offset
        stw     r15, base
    }
    offset = offset ^ 0xF0;
    response = offset + addend;
    response = response + base;
    asm {
        lwz     r23, response
        mtlr    r23
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION createChildSequence__Q23seq21SequenceTitleMenuRootCFv
std::auto_ptr<ISequence> SequenceTitleMenuRoot::createChildSequence() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0x811C9E29;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0xC8F8EF93
        opword  MF_WORD(0x38)
        opword  0x16E57B03
    after1:
        mflr    r28
        lwz     r30, 0x8(r28)
        lwz     r18, 0x0(r28)
        add     r30, r18, r30
        stw     r30, end
        stw     r18, start
    }
    word = start;
    last = end;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x010001AB;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0xEE4F68E8
    after2:
        mflr    r20
        lwz     r22, 0x0(r20)
        stw     r22, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    switch (mRecipe._4) {
    case CHILD_OPENING_0:
    case CHILD_OPENING_1: {
        storage::StoryMode mode =
            (hash - expected != 0 || mRecipe._4 == CHILD_OPENING_0) ? storage::STORY_MODE_0 : storage::STORY_MODE_1;
        return std::auto_ptr<ISequence>(new SequenceOpeningRoot(mode, mRecipe.mEntryInfo));
    }
    case CHILD_SUBGAME_0:
    case CHILD_SUBGAME_1: {
        scn::subgame::Context context = scn::subgame::Context::Create();
        switch (mRecipe._4) {
        case CHILD_SUBGAME_0:
            context.mKind = scn::subgame::Context::KIND_SETSUNA;
            break;
        case CHILD_SUBGAME_1:
            context.mKind = scn::subgame::Context::KIND_1;
            break;
        default:
            while (hash - expected != 0) {
            }
            break;
        }
        for (int i = 0; i < 4; i++) {
            context._4[i]._0 = mRecipe.mEntryInfo._0[i];
        }
        return std::auto_ptr<ISequence>(new SequenceSubgame(SequenceSubgame::Recipe::Create(context)));
    }
    case CHILD_ARENA_0:
    case CHILD_ARENA_1: {
        storage::ArenaGameKind kind =
            (hash - expected != 0 || mRecipe._4 == CHILD_ARENA_0) ? storage::ARENA_GAME_KIND_0 : storage::ARENA_GAME_KIND_1;
        return std::auto_ptr<ISequence>(new SequenceArenaRoot(SequenceArenaRoot::Recipe::Create(kind, mRecipe.mEntryInfo)));
    }
    case CHILD_SOUND_ROOM:
        return std::auto_ptr<ISequence>(new SequenceSimpleScene<scn::soundroom::SceneSoundRoom>());
    case CHILD_THEATER_ROOM:
        return std::auto_ptr<ISequence>(new SequenceTheaterRoomRoot());
    case CHILD_OPTION:
        return std::auto_ptr<ISequence>(new SequenceCallScene<scn::option::SceneOption>());
    default:
        while (hash - expected != 0) {
        }
        return std::auto_ptr<ISequence>();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION onChildSequenceEnd__Q23seq21SequenceTitleMenuRootFRQ23seq9ISequence
void SequenceTitleMenuRoot::onChildSequenceEnd(ISequence& child) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    u16* word;
    u16* last;
    u32 hash;

    asm {
        bl      after1
        opword  0xD41A4880
        opword  MF_WORD(0x2C)
    after1:
        mflr    r23
        lwz     r29, 0x4(r23)
        stw     r29, start
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x74713B93
    after2:
        mflr    r23
        lwz     r14, 0x0(r23)
        add     r14, r14, r29
        stw     r14, end
    }
    hash = 0xB3;
    word = (u16*)start;
    last = (u16*)end;
    word--;
    for (;;) {
        word++;
        if (word == last) {
            break;
        }
        hash = *word ^ ((hash << 4) ^ (hash >> 28));
    }
    asm {
        bl      after3
        opword  MF_WORD(0x90)
        opword  0xB6838599
    after3:
        mflr    r21
        lwz     r22, 0x0(r21)
        stw     r22, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0) {
        SequenceOpeningRoot* opening = hel::common::DynamicCast<SequenceOpeningRoot*, ISequence>(&child);
        if (opening != 0) {
            mRecipe.mEntryInfo = opening->result().mEntryInfo;
            switch (opening->result()._0) {
            case 0:
                _4 = 2;
                _8 = false;
                mRecipe._0 = 1;
                mRecipe._8 = false;
                break;
            case 1:
                _4 = 0;
                _28 = 1;
                break;
            }
        } else {
            SequenceCallScene<scn::option::SceneOption>* option =
                hel::common::DynamicCast<SequenceCallScene<scn::option::SceneOption>*, ISequence>(&child);
            if (option != 0) {
                if (option->result()) {
                    _4 = 2;
                    _8 = false;
                    mRecipe._0 = 0;
                    mRecipe._8 = false;
                } else {
                    _4 = 2;
                    _8 = false;
                    mRecipe._0 = 1;
                    mRecipe._8 = false;
                }
            } else {
                SequenceSubgame* subgame = hel::common::DynamicCast<SequenceSubgame*, ISequence>(&child);
                if (subgame != 0) {
                    for (u32 i = 0; i < 4; i++) {
                        mRecipe.mEntryInfo._0[i] = subgame->result()._4[i]._0;
                    }
                    _4 = 2;
                    _8 = false;
                    mRecipe._0 = 1;
                    mRecipe._8 = false;
                } else {
                    SequenceArenaRoot* arena = hel::common::DynamicCast<SequenceArenaRoot*, ISequence>(&child);
                    if (arena != 0) {
                        mRecipe.mEntryInfo = arena->result().mPlayer.getEntryInfo();
                        _4 = 2;
                        _8 = false;
                        mRecipe._0 = 1;
                        mRecipe._8 = false;
                    } else {
                        _4 = 2;
                        _8 = false;
                        mRecipe._0 = 1;
                        mRecipe._8 = false;
                    }
                }
            }
        }
    } else {
        asm {
            bl      after4
            opword  MF_WORD(0x360)
        after4:
            mflr    r19
            lwz     r21, 0x0(r19)
            stw     r21, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r21
            bl      after5
            opword  MF_WORD(0x384)
            opword  0x580BF280
            opword  MF_WORD(0x38C)
        after5:
            mflr    r16
            lwz     r18, 0x0(r16)
            stw     r16, base
            lwz     r19, 0x8(r16)
            stw     r18, offset
            stw     r19, addend
        }
        response = offset - addend;
        response = response + base;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    }
}
#undef MF_FUNCTION

std::auto_ptr<scn::IScene> SequenceTitleMenuRoot::createScene() const {
    if (_8) {
        scn::movie::SceneMovie::Recipe recipe = scn::movie::SceneMovie::Recipe::Create(
            scn::movie::SceneMovie::MODE_0, static_cast<mov::MovieKind>(13), t_preFadeColor(), t_postFadeColor(), true,
            scn::movie::SceneMovie::UNLOCK_MODE_0);
        return std::auto_ptr<scn::IScene>(new scn::movie::SceneMovie(recipe));
    } else {
        return std::auto_ptr<scn::IScene>(new scn::titlemenunew::SceneTitleMenu(mRecipe));
    }
}

#define MF_FUNCTION onSceneEnd__Q23seq21SequenceTitleMenuRootFRQ23scn6IScene
void SequenceTitleMenuRoot::onSceneEnd(scn::IScene& scene) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 addend;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x68947280
        opword  0x909BAE93
        opword  MF_WORD(0x30)
        opword  0xB217D300
        opword  0x5C0B9590
        opword  MF_WORD(0x3C)
        opword  0xB4753080
        opword  0x5D1A2F07
    after1:
        mflr    r23
        lwz     r17, 0x14(r23)
        stw     r17, start
        lwz     r16, 0x8(r23)
        stw     r16, end
    }
    i = 1;
    first = start;
    limit = end - first + 1;
    hash = 0;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 61;
        hash += *(u16*)(first + i - 1);
        i += 2;
    }
    limit = hash << 3;
    hash += limit;
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0xD6362221
    after2:
        mflr    r20
        lwz     r28, 0x0(r20)
        stw     r28, expected
    }
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    if (hash == limit) {
        if (hel::common::DynamicCast<scn::titlemenunew::SceneTitleMenu*, scn::IScene>(&scene) != 0) {
            scn::titlemenunew::SceneTitleMenu& menu =
                hel::common::DynamicCastToRef<scn::titlemenunew::SceneTitleMenu, scn::IScene>(&scene);
            if (menu.result()._C) {
                mRecipe.mEntryInfo = EntryInfo::Create();
            }
            switch (menu.result()._0) {
            case 0:
                _4 = 0;
                _28 = 0;
                break;
            case 1:
                _4 = 1;
                mRecipe._4 = menu.result()._8;
                break;
            case 2:
                _4 = 2;
                _8 = true;
                mRecipe._0 = 2;
                mRecipe._4 = menu.result()._8;
                mRecipe._8 = false;
                break;
            }
        } else {
            _4 = 2;
            _8 = false;
        }
    } else {
        asm {
            bl      after3
            opword  0xA0CFB890
            opword  0xB872FE92
            opword  MF_WORD(0x1D0)
        after3:
            mflr    r14
            lwz     r24, 0x8(r14)
            stw     r24, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0x1F4)
            opword  0xDCB07E80
            opword  0x989E9F80
            opword  MF_WORD(0x200)
        after4:
            mflr    r28
            lwz     r18, 0x0(r28)
            lwz     r15, 0xc(r28)
            stw     r15, addend
            stw     r18, offset
            stw     r28, base
        }
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    }
}
#undef MF_FUNCTION

const hel::common::RuntimeTypeInfo& SequenceTitleMenuRoot::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SequenceTitleMenuRoot>();
}

}
